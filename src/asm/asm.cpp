#include "asm.hpp"
#include <cstdio>

std::ostream& operator<<(std::ostream& os, const spt<AsmProg>& prog) {
	os << *prog;
	return os;
}
std::ostream& operator<<(std::ostream& os, const AsmProg& prog) {
	os << "\t.text\n";
	if (targetMacos) os << "\t.globl _main\n";
	else os << "\t.globl main\n";
	for (auto& f : prog.functions) {
		f->emit(os);
	}
#include "asm_footcode"
	os << "\n\t.data\n";
	for (auto& p : prog.stringConsts) {
		os << p.first << ": .string \"" << p.second << "\"\n";
	}
	for (spt<AsmGlobalVar> var : prog.globalVars) {
		os << var->getLabel() << ": .quad 0\n";
	}
	return os;
}

std::string regNameCode(RegName reg) {
	switch (reg) {
	case rax: return "%rax";
	case rbx: return "%rbx";
	case rcx: return "%rcx";
	case rdx: return "%rdx";
	case rsi: return "%rsi";
	case rdi: return "%rdi";
	case rbp: return "%rbp";
	case rsp: return "%rsp";
	case r8: return "%r8";
	case r9: return "%r9";
	case r10: return "%r10";
	case r11: return "%r11";
	case r12: return "%r12";
	case r12b: return "%r12b";
	case r13: return "%r13";
	case r14: return "%r14";
	case r15: return "%r15";
	}
	return "";
}

/*
	prog
*/

void AsmProg::add(spt<AsmFunc> func) {
	functions.push_back(func);
}
const std::string randCharset("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
const int labelSize = 10;
std::string AsmProg::randomLabel() { // do not use '_' !!!
	std::string s;
	for (int i = labelSize; i; i--) {
		s.push_back(randCharset[rand() % randCharset.size()]);
	}
	if (usedLabels.count(s)) {
		return randomLabel();
	}
	else {
		usedLabels.insert(s);
	}
	return s;
}
std::string AsmProg::addString(std::string label, std::string content) {
	if (label.empty()) {
		label = "strconst_" + randomLabel();
	}
	std::string realContent = "";
	for (char c : content) {
		if (c == '\n') {
			realContent.push_back('\\');
			realContent.push_back('n');
		}
		else if (c == '\t') {
			realContent.push_back('\\');
			realContent.push_back('t');
		}
		else if (c == '\\') {
			realContent.push_back('\\');
			realContent.push_back('\\');
		}
		else if (c == '"') {
			realContent.push_back('\\');
			realContent.push_back('"');
		}
		else {
			realContent.push_back(c);
		}
	}
	stringConsts[label] = realContent;
	stringToLabel[content] = label;
	return label;
}
std::string AsmProg::store(std::string content) {
	if (stringToLabel.count(content)) {
		return stringToLabel[content];
	}
	return addString("", content);
}
spt<AsmLabelRef> AsmProg::storeArg(std::string content) {
	if (targetMacos) {
		return labelArg(store(content) + "@GOTPCREL(%rip)");
	}
	return labelArg("$" + store(content));
}

void AsmProg::storeVar(spt<AsmGlobalVar> var) {
	globalVars.push_back(var);
}

/*
	Functions
*/

AsmFunc::AsmFunc(std::string name, bool isMain)
	:name(name), isMain(isMain) {
	rbpOffset = 0;
	argOffset = 2;
	needReturnType = false;
	footerOp = sptOf(new AsmIns(asmNop, {}, "end_" + name));
}
void AsmFunc::emit(std::ostream& os) {
	os << name << ":\n";
	os << "\tpushq %rbp\n";
	os << "\tmovq %rsp, %rbp\n";
	if (rbpOffset)
		os << "\tsub $" << -(rbpOffset * 8) << ", %rsp\n";

	// Set variables as uninitialized
	for (spt<AsmLoc> varLoc : localVars) {
		auto ins = AsmIns(asmMov, { intArg(-1), varLoc->withOffset(1) });
		ins.emit(os);
	}
	for (auto& ins : instructions) {
		ins->emit(os);
	}

	if (rbpOffset)
		os << "\tadd $" << -(rbpOffset * 8) << ", %rsp\n";
	os << "\tpopq %rbp\n";
	os << "\tret\n";
}

spt<AsmIns> AsmFunc::add(AsmInsName insName, std::vector<spt<AsmArg>> args) {
	return add(sptOf(new AsmIns(insName, args)));
}
spt<AsmIns> AsmFunc::add(spt<AsmIns> ins) {
	instructions.push_back(ins);
	return instructions.back();
}
void AsmFunc::alignStack(spt<AsmProg> prog) {
	auto jumpAfterPush = sptOf(new AsmIns(asmNop, {}));
	add(asmTest, { intArg(15), regArg(rsp) });
	add(asmJumpIf, { flagArg("e"), labelArg(jumpAfterPush->getLabel(prog)) });
	add(asmPushq, { regArg(rsp) });
	add(jumpAfterPush);
}
void AsmFunc::abort(spt<AsmProg> prog, std::string message, std::vector<spt<AsmArg>> args) {
	if (message.size()) {
		message = "\e[31m" + message + "\e[0m\n";
		std::string label = prog->store(message);
		add(asmLoadAddr, { labelArg(label), regArg(rdi) });
		if (args.size() >= 1) add(asmMov, { args[0], regArg(rsi) });
		if (args.size() >= 2) add(asmMov, { args[1], regArg(rdx) });
		if (args.size() >= 3) add(asmMov, { args[2], regArg(rcx) });
		if (args.size() >= 4) add(asmMov, { args[3], regArg(r8) });
		if (args.size() >= 5) add(asmMov, { args[4], regArg(r9) });
		add(asmCall, { labelArg("_fail_with") });
	}
	else {
		add(asmCall, { labelArg("_fail_abort_call") });
	}
}

AsmPrimitiveCode::AsmPrimitiveCode() : AsmFunc("", false) {}
void AsmPrimitiveCode::emit(std::ostream& os) {
	for (auto& ins : instructions) {
		ins->emit(os);
	}
}

/*
	ASM arguments
*/

void AsmOffset::emit(std::ostream& os) {
	os << (qOffset * 8) << "(";
	os << regNameCode(reg);
	os << ")";
}
spt<AsmLoc> AsmOffset::withOffset(int offset) {
	return sptOf(new AsmOffset(qOffset + offset, reg));
}

void AsmRegArg::emit(std::ostream& os) {
	os << regNameCode(reg);
}
spt<AsmLoc> AsmRegArg::withOffset(int offset) {
	if (reg == rax && offset == 1) {
		return sptOf(new AsmRegArg(rbx));
	}
	throw UsageError("Cant offset register [INTERNAL]");
}

void AsmGlobalVar::emit(std::ostream& os) {
	os << getLabel() << "(%rip)";
}
std::string AsmGlobalVar::getLabel() {
	if (isTypeVar) {
		return "gtype_" + varName;
	}
	return "gvar_" + varName;
}
spt<AsmLoc> AsmGlobalVar::withOffset(int offset) {
	if (!isTypeVar && offset == 1) {
		return sptOf(new AsmGlobalVar(varName, true));
	}
	throw UsageError("Cant offset global variable [INTERNAL]");
}

void AsmInt::emit(std::ostream& os) {
	os << "$" << value;
}
void AsmLabelRef::emit(std::ostream& os) {
	os << label;
}
void AsmFlag::emit(std::ostream& os) {
	os << flag;
}


/*
	ASM instructions
*/

AsmIns::AsmIns(AsmInsName ins, std::vector<spt<AsmArg>> insArgs, std::string setLabel)
	: labelName(setLabel), hasLabel(!setLabel.empty()), ins(ins), args(insArgs) {
	if ((int)args.size() != AsmIns::nbArgs(ins)) {
		throw PJuliaError("Wrong number of arguments for asm instruction '"
			+ AsmIns::codeOf(ins) + "' [INTERNAL]");
	}
}

int AsmIns::nbArgs(AsmInsName insName) {
	switch (insName) {
	case asmMov: return 2;
	case asmPushq: return 1;
	case asmPopq: return 1;
	case asmLoadAddr: return 2;
	case asmAdd: return 2;
	case asmSub: return 2;
	case asmBitNot: return 1;
	case asmBitAnd: return 2;
	case asmBitOr: return 2;
	case asmBitXor: return 2;
	case asmRet: return 0;
	case asmCall: return 1;
	case asmNop: return 0;
	case asmCmp: return 2;
	case asmTest: return 2;
	case asmJumpIf: return 2;
	case asmSet: return 2;
	case asmMult: return 2;
	case asmJump: return 1;
	case asmCqto: return 0;
	case asmIdivq: return 1;
	case asmNeg: return 1;
	case asmInc: return 1;
	}
	return 0;
}
std::string AsmIns::codeOf(AsmInsName insName) {
	switch (insName) {
	case asmMov: return "movq";
	case asmPushq: return "pushq";
	case asmPopq: return "popq";
	case asmLoadAddr: return "leaq";
	case asmAdd: return "addq";
	case asmSub: return "subq";
	case asmBitNot: return "notq";
	case asmBitAnd: return "andq";
	case asmBitOr: return "orq";
	case asmBitXor: return "xorq";
	case asmRet: return "ret";
	case asmCall: return "call";
	case asmNop: return "";
	case asmCmp: return "cmpq";
	case asmTest: return "testq";
	case asmJumpIf: return "j";
	case asmSet: return "set";
	case asmMult: return "imulq";
	case asmJump: return "jmp";
	case asmCqto: return "cqto";
	case asmIdivq: return "idivq";
	case asmNeg: return "negq";
	case asmInc: return "incq";
	}
	return "";
}
void AsmIns::emit(std::ostream& os) {
	if (hasLabel) {
		os << labelName << ":\n";
	}

	if (ins == asmNop) {
		return;
	}
	int iArgInit = 0;
	if (targetMacos && ins == asmLoadAddr) os << "\t" << AsmIns::codeOf(asmMov);
	else os << "\t" << AsmIns::codeOf(ins);
	if (ins == asmJumpIf || ins == asmSet) {
		args[0]->emit(os);
		iArgInit++;
	}
	for (int iArg = iArgInit; iArg < (int)args.size(); iArg++) {
		if (iArg > iArgInit) {
			os << ',';
		}
		os << ' ';
		args[iArg]->emit(os);
		if (iArg == 0 && targetMacos && ins == asmLoadAddr) {
			os << "@GOTPCREL(%rip)";
		}
	}
	os << "\n";
}
std::string AsmIns::getLabel(spt<AsmProg> prog) {
	if (!hasLabel) {
		hasLabel = true;
		labelName = "lab_" + prog->randomLabel();
	}
	return labelName;
}
