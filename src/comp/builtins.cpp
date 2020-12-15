#include "builtins.hpp"

void BuiltinFunc::show(std::ostream& os) const {
	os << "BuiltinFunc " << name->val;
}
void BuiltinFunc::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	env->add(name, shared_as<BuiltinFunc>());
}
void BuiltinFunc::refIdents() {}
void BuiltinFunc::setTypes() {}

void BuiltinFunc::checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) {
	if (!matchArgs(callTypes)) {
		throw JError(atLoc, typesToSig(callTypes) + " doesn't match the function signature " + getSignature());
	}
}
void BuiltinFunc::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	// Do nothing because not a real declaration
}
void BuiltinFunc::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	throw UsageError("Not implemented yet [BuiltinFunc::emitAsmCall]");
}

/*
	Builtin functions
*/

// Print function

std::string BuiltinPrint::getSignature() {
	return "print(...)";
}
bool BuiltinPrint::matchArgs(std::vector<spt<Type>>&) {
	return true;
}
std::string BuiltinPrintLn::getSignature() {
	return "println(...)";
}
void BuiltinPrint::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	prog->addString("str_print_true", "true");
	prog->addString("str_print_false", "false");
	prog->addString("str_print_int", "%lld");
	prog->addString("str_print_ln", "\n");
	prog->addString("str_print_nothing", "nothing");
	prog->addString("str_print_string", "%s");

	// Generate print_Any
	auto labelFunc = sptOf(new AsmIns(asmNop, {}, "print_Any"));
	func->add(labelFunc);

	std::vector<std::string> types;
	for (auto declPair : env->declarations) {
		spt<Type> declType = std::dynamic_pointer_cast<Type>(declPair.second);
		if (declType) {
			if (declType->typeId >= (int)types.size()) {
				types.resize(declType->typeId + 1);
			}
			types[declType->typeId] = declType->name->val;
		}
	}
	// Be cause I like when its ordered
	for (int iType = 0; iType < (int)types.size(); iType++) {
		if (types[iType] != "Any") {
			func->add(asmCmp, { intArg(iType), regArg(rbx) });
			func->add(asmJumpIf, { flagArg("e"), labelArg("print_" + types[iType]) });
		}
	}
}
void BuiltinPrint::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	for (spt<Expr> arg : args->expressions) {
		arg->emitAsm(prog, func);
		func->add(asmCall, { labelArg("print_" + arg->getType()->name->val) });
	}
}


void  BuiltinPrintLn::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	// nothing
}
void BuiltinPrintLn::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	// call parent + print newline [TODO]
	BuiltinPrint::emitAsmCall(prog, func, args);
	func->add(asmLoadAddr, { labelArg("str_print_ln"), regArg(rax) });
	func->add(asmCall, { labelArg("print_String") });
}

// Div function
std::string BuiltinDiv::getSignature() {
	return "div(::Int64, ::Int64)";
}
bool BuiltinDiv::matchArgs(std::vector<spt<Type>>& callTypes) {
	auto intType = env->getType("Int64");
	return callTypes.size() == 2 &&
		typesMatch(callTypes[0], intType) && typesMatch(callTypes[1], intType);
}
void BuiltinDiv::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	args->expressions[0]->emitAsm(prog, func);
	asmCheckArgType(prog, func, args->expressions[0], env->getType("Int64"));
	func->add(asmPushq, { regArg(rax) });
	args->expressions[1]->emitAsm(prog, func);
	asmCheckArgType(prog, func, args->expressions[1], env->getType("Int64"));

	auto op1 = sptOf(new AsmIns(asmMov, { regArg(rax), regArg(rcx) }));
	func->add(asmCmp, { intArg(0), regArg(rax) });
	func->add(asmJumpIf, { flagArg("ne"), labelArg(op1->getLabel(prog)) });
	func->abort(prog, "Division by 0, line %d, characters %d-%d",
		{ intArg(loc.first_line),
				intArg(loc.first_column),
				intArg(loc.last_column) });

	func->add(op1);
	func->add(asmPopq, { regArg(rax) });
	func->add(asmCqto, {});
	func->add(asmIdivq, { regArg(rcx) });
}
