#include "ast.hpp"
#include "../asm/asm.hpp"

void Ast::emitAsm(spt<AsmProg> prog) {
	spt<AsmPrimitiveCode> primitiveCode = sptOf(new AsmPrimitiveCode());
	for (auto declPair : env->declarations) {
		// std::cerr << "===== Emit for\n";
		// declPair.second->show(std::cerr);
		// std::cerr << "\n";
		declPair.second->emitAsm(prog, primitiveCode);
	}
	prog->add(primitiveCode);
}
spt<AsmArg> Expr::getAsmType() {
	if (this->forceStore()) {
		return regArg(rbx);
	}
	else {
		return intArg(getType()->typeId);
	}
}

spt<AsmArg> Ident::getAsmTypeRef(spt<AsmLoc> loc) {
	if (getType()->isKnown()) {
		return sptOf(new AsmInt(getType()->typeId));
	}
	else {
		return loc->withOffset(1);
	}
}

void ensureType(spt<AsmProg> prog, spt<AsmFunc> func, std::vector<int> typeIds, spt<Expr> expr,
	std::string message = "", std::vector<spt<AsmArg>> args = {}) {
	if (!expr || !expr->getType()->isKnown()) {
		if (expr && message == "") {
			message = "Wrong type, line %d, characters %d-%d";
			args = { intArg(expr->loc.first_line),
				intArg(expr->loc.first_column),
				intArg(expr->loc.last_column) };
		}
		else if (message == "") {
			message = "Wrong type";
		}

		auto labelIsOk = sptOf(new AsmIns(asmNop, {}));
		for (int v : typeIds) {
			func->add(asmCmp, { intArg(v), regArg(rbx) });
			func->add(asmJumpIf, { flagArg("e"), labelArg(labelIsOk->getLabel(prog)) });
		}
		func->abort(prog, message, args);
		func->add(labelIsOk);
	}
}

void allocateVar(spt<AsmProg> prog, spt<AsmFunc> func, spt<Ident> ident) {
	if (!ident->setAt->asmLoc) {
		// if (func->isMain) {
		if (!ident->env->from) {
			auto loc = sptOf(new AsmGlobalVar(ident->val, false));
			prog->storeVar(loc);
			ident->setAt->asmLoc = loc;
			prog->storeVar(sptOf(new AsmGlobalVar(ident->val, true)));
		}
		else {
			func->rbpOffset -= 2;
			ident->setAt->asmLoc = sptOf(new AsmOffset(func->rbpOffset));
		}
		ident->setAt->_forceStoreType = true;
		func->localVars.push_back(ident->setAt->asmLoc);
	}
}

void ensureVarIsSet(spt<AsmProg> prog, spt<AsmFunc> func, spt<Ident> ident) {
	allocateVar(prog, func, ident);

	if (ident->setAt->_forceStoreType) { // We don't need to check if function arguments are set
		auto labelIsSet = sptOf(new AsmIns(asmNop, {}));
		func->add(asmCmp, { intArg(-1), ident->setAt->asmLoc->withOffset(1) });
		func->add(asmJumpIf, { flagArg("ne"), labelArg(labelIsSet->getLabel(prog)) });
		func->abort(prog, "Variable used before beeing assigned, line %d, characters %d-%d",
			{ intArg(ident->loc.first_line),
				intArg(ident->loc.first_column),
				intArg(ident->loc.last_column) });
		func->add(labelIsSet);
	}
}

std::pair<int, spt<Type>> getStructMember(spt<DotOp> op) {
	int offset = 0, iMember = 0;
	while (op->structType->members[iMember]->name->val != op->member->val) {
		offset += op->structType->members[iMember]->argType->isKnown() ? 1 : 2;
		iMember++;
	}
	return { offset,
		op->structType->members[iMember]->argType };
}

std::string FuncDispacher::getAsmName(int nbArgs) {
	return "dispatch_" + std::to_string(nbArgs) + "args_" + asmName;
}

/*
	Emit ASM
*/

void ExprBlock::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	for (auto child : expressions) {
		child->emitAsm(prog, func);
	}
}
void BaseType::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {}
void Ident::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	ensureVarIsSet(prog, func, shared_as<Ident>());
	if (getType()->name->val != "Nothing") {
		func->add(asmMov, { setAt->asmLoc, regArg(rax) });
	}
	else {
		func->add(asmMov, { intArg(0), regArg(rax) });
	}
	if (setAt->forceStore()) {
		func->add(asmMov, { setAt->asmLoc->withOffset(1), regArg(rbx) });
	}
}
void IntConst::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	func->add(asmMov, { intArg(this->value), regArg(rax) });
}
void Assignment::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	auto leftIdent = std::dynamic_pointer_cast<Ident>(lvalue);
	auto leftDotOpt = std::dynamic_pointer_cast<DotOp>(lvalue);

	spt<AsmLoc> loc;
	bool storeType = false;
	spt<Type> dotOptType;
	if (leftIdent) {
		allocateVar(prog, func, leftIdent);
		loc = leftIdent->setAt->asmLoc;
		storeType = leftIdent->setAt->forceStore();
	}
	else {
		leftDotOpt->object->emitAsm(prog, func);
		ensureType(prog, func, { leftDotOpt->structType->typeId }, leftDotOpt->object);

		func->add(asmPushq, { regArg(rax) });
		auto offsetAndType = getStructMember(leftDotOpt);
		loc = sptOf(new AsmOffset(offsetAndType.first, rcx));
		dotOptType = offsetAndType.second;
		storeType = !dotOptType->isKnown();
	}

	rvalue->emitAsm(prog, func);
	if (leftDotOpt) {
		if (dotOptType->isKnown()) {
			ensureType(prog, func, { dotOptType->typeId }, rvalue);
		}
		func->add(asmPopq, { regArg(rcx) });
	}

	func->add(asmMov, { regArg(rax), loc });
	if (storeType) {
		func->add(asmMov, { rvalue->getAsmType(), loc->withOffset(1) });
	}
}
void StrConst::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	std::string label = prog->store(this->value);
	func->add(asmLoadAddr, { labelArg(label), regArg(rax) });
}
void BoolConst::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	func->add(asmMov, { intArg(value), regArg(rax) });
}

void BinOp::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	auto opJumpAfter = sptOf(new AsmIns(asmNop, {}));
	// LEFT PART
	left->emitAsm(prog, func);

	// type check
	if (op == OpLower || op == OpLowerEq || op == OpGreater || op == OpGreaterEq)
		ensureType(prog, func, { env->getType("Int64")->typeId, env->getType("Bool")->typeId }, left);
	if (op == OpPlus || op == OpMinus || op == OpTimes || op == OpMod || op == OpPower)
		ensureType(prog, func, { env->getType("Int64")->typeId }, left);
	if (op == OpAnd || op == OpOr)
		ensureType(prog, func, { env->getType("Bool")->typeId }, left);

	// Booleans
	if (op == OpAnd || op == OpOr) {
		func->add(asmCmp, { intArg(0), regArg(rax) });
		if (op == OpAnd)
			func->add(asmJumpIf, { flagArg("e"), labelArg(opJumpAfter->getLabel(prog)) });
		if (op == OpOr)
			func->add(asmJumpIf, { flagArg("ne"), labelArg(opJumpAfter->getLabel(prog)) });
	}
	else { // Store in stack
		if (!left->getType()->isKnown()) {
			func->add(asmPushq, { regArg(rbx) });
		}
		func->add(asmPushq, { regArg(rax) });
	}

	// RIGHT PART
	right->emitAsm(prog, func);

	// Type check
	spt<AsmArg> typeLeft = left->getType()->isKnown() ? (spt<AsmArg>)intArg(left->getType()->typeId)
		: sptOf(new AsmOffset(1, rsp));

	bool leftKnown = left->getType()->isKnown();
	if (op == OpAnd || op == OpOr) {
		typeLeft = intArg(env->getType("Bool")->typeId);
		leftKnown = true;
	}
	spt<AsmArg> typeRight = right->getType()->isKnown() ? (spt<AsmArg>)intArg(right->getType()->typeId)
		: regArg(rbx);
	if (!leftKnown || !right->getType()->isKnown()) {
		auto labelIsOk = sptOf(new AsmIns(asmNop, {}));
		if (right->getType()->isKnown()) {
			func->add(asmCmp, { typeRight, typeLeft });
		}
		else {
			func->add(asmCmp, { typeLeft, typeRight });
		}
		func->add(asmJumpIf, { flagArg("e"), labelArg(labelIsOk->getLabel(prog)) });
		if (op == OpEq || op == OpNotEq) {
			if (op == OpEq) func->add(asmMov, { intArg(0), regArg(rax) });
			if (op == OpNotEq) func->add(asmMov, { intArg(1), regArg(rax) });
			func->add(asmJump, { labelArg(opJumpAfter->getLabel(prog)) });
		}
		else {
			func->abort(prog, "Different types for operation %s, line %d, characters %d-%d",
				{ prog->storeArg(asStr(op)),
				intArg(loc.first_line),
				intArg(loc.first_column),
				intArg(loc.last_column) });
		}
		func->add(labelIsOk);
	}

	// Compute result

	// TODO : == and != for structs !!!!!

	auto valLeft = sptOf(new AsmOffset(0, rsp));
	auto valRight = regArg(rax);
	bool depopEnd = true; // Don't work for some operations
	if (op == OpEq || op == OpNotEq || op == OpLower || op == OpLowerEq || op == OpGreater || op == OpGreaterEq) {
		func->add(asmCmp, { valLeft, valRight });

		if (op == OpEq) func->add(asmSet, { flagArg("e"), regArg(r10b) });
		if (op == OpNotEq) func->add(asmSet, { flagArg("ne"), regArg(r10b) });
		if (op == OpLower) func->add(asmSet, { flagArg("g"), regArg(r10b) });
		if (op == OpLowerEq) func->add(asmSet, { flagArg("ge"), regArg(r10b) });
		if (op == OpGreater) func->add(asmSet, { flagArg("l"), regArg(r10b) });
		if (op == OpGreaterEq) func->add(asmSet, { flagArg("le"), regArg(r10b) });

		func->add(asmMov, { regArg(r10), regArg(rax) });
	}
	if (op == OpPlus) func->add(asmAdd, { valLeft, valRight });
	if (op == OpMinus) {
		func->add(asmSub, { valRight, valLeft });
		func->add(asmPopq, { regArg(rax) });
		depopEnd = false;
	}
	if (op == OpTimes) func->add(asmMult, { valLeft, valRight });
	if (op == OpMod) {
		auto op1 = sptOf(new AsmIns(asmMov, { regArg(rax), regArg(rcx) }));
		func->add(asmCmp, { intArg(0), regArg(rax) });
		func->add(asmJumpIf, { flagArg("ne"), labelArg(op1->getLabel(prog)) });
		func->abort(prog, "Modulo by 0, line %d, characters %d-%d",
			{ intArg(loc.first_line),
				intArg(loc.first_column),
				intArg(loc.last_column) });

		func->add(op1);
		func->add(asmPopq, { regArg(rax) });
		func->add(asmCqto, {});
		func->add(asmIdivq, { regArg(rcx) });
		func->add(asmMov, { regArg(rdx), regArg(rax) }); // Remainder to rax
		depopEnd = false;
	}
	if (op == OpPower) {
		func->add(asmMov, { regArg(rax), regArg(rsi) });
		func->add(asmPopq, { regArg(rdi) });
		func->add(asmCall, { labelArg("_for_gondor") });
		depopEnd = false;
	}


	func->add(opJumpAfter);
	if (op != OpAnd && op != OpOr) {
		if (depopEnd) {
			func->add(asmPopq, { regArg(r10) });
		}
		if (!left->getType()->isKnown()) func->add(asmPopq, { regArg(r10) });
	}
}

void UnaryOp::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	expr->emitAsm(prog, func);

	// type check
	if (op == UnaryMinus) {
		ensureType(prog, func, { env->getType("Int64")->typeId }, expr);
		func->add(asmNeg, { regArg(rax) });
	}
	if (op == UnaryNot) {
		ensureType(prog, func, { env->getType("Bool")->typeId }, expr);
		func->add(asmBitXor, { intArg(1), regArg(rax) });
	}
}
void DotOp::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	object->emitAsm(prog, func);
	ensureType(prog, func, { structType->typeId }, object);

	auto offsetAndType = getStructMember(shared_as<DotOp>());
	auto loc = sptOf(new AsmOffset(offsetAndType.first, rax));

	if (!offsetAndType.second->isKnown()) {
		func->add(asmMov, { loc->withOffset(1), regArg(rbx) });
	}
	func->add(asmMov, { loc, regArg(rax) });
}

void CallParamList::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	throw UsageError("Should not be called [CallParamList]");
}

void DefStruct::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	int structSize = 0;
	for (auto m : members) {
		structSize += m->argType->isKnown() ? 1 : 2;
	}
	int nbArgs = args->expressions.size();
	func->add(asmMov, { intArg(structSize * 8), regArg(rdi) });
	func->add(asmCall, { labelArg("malloc") });
	func->add(asmPushq, { regArg(rax) });

	int offset = 0;
	for (int iArg = 0; iArg < nbArgs; iArg++) {
		auto& arg = args->expressions[iArg];
		auto& argType = members[iArg]->argType;

		arg->emitAsm(prog, func);
		if (argType->isKnown()) {
			ensureType(prog, func, { argType->typeId }, arg);
		}
		func->add(asmMov, { sptOf(new AsmOffset(0, rsp)), regArg(rcx) });
		auto loc = sptOf(new AsmOffset(offset, rcx));

		func->add(asmMov, { regArg(rax), loc });
		if (!argType->isKnown()) {
			func->add(asmMov, { arg->getAsmType()	, loc->withOffset(1) });
			offset += 1;
		}
		offset += 1;
	}
	func->add(asmPopq, { regArg(rax) });
}
void DefFunc::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> argsValues) {
	for (int iArg = argsValues->expressions.size() - 1; iArg >= 0; iArg--) {
		auto expr = argsValues->expressions[iArg];
		expr->emitAsm(prog, func);
		if (args[iArg]->argType->isKnown()) {
			ensureType(prog, func, { args[iArg]->argType->typeId }, expr);
		}
		func->add(asmPushq, { expr->getAsmType() });
		func->add(asmPushq, { regArg(rax) });
	}
	func->add(asmCall, { labelArg(asmName) });

	int argStackSize = argsValues->expressions.size() * 2;
	if (argStackSize) {
		func->add(asmAdd, { intArg(argStackSize * 8), regArg(rsp) });
	}
}
void FuncDispacher::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	for (int iArg = args->expressions.size() - 1; iArg >= 0; iArg--) {
		auto expr = args->expressions[iArg];
		expr->emitAsm(prog, func);
		func->add(asmPushq, { expr->getAsmType() });
		func->add(asmPushq, { regArg(rax) });
	}
	func->add(asmCall, { labelArg(getAsmName(args->expressions.size())) });

	int argStackSize = args->expressions.size() * 2;
	if (argStackSize) {
		func->add(asmAdd, { intArg(argStackSize * 8), regArg(rsp) });
	}
}
void CallFunction::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	funcPt->emitAsmCall(prog, func, args);
}
void ReturnVal::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	value->emitAsm(prog, func);
	// if (value->getType()->isKnown() && func->needReturnType) {
	func->add(asmMov, { value->getAsmType(), regArg(rbx) });
	// }
	func->add(asmJump, { labelArg(func->footerOp->getLabel(prog)) });
}
void FlowFor::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	auto labelBegin = sptOf(new AsmIns(asmNop, {}));
	auto labelEnd = sptOf(new AsmIns(asmNop, {}));


	startAt->emitAsm(prog, func);
	ensureType(prog, func, { env->getType("Int64")->typeId }, startAt);

	allocateVar(prog, func, counter);
	auto varLoc = counter->setAt->asmLoc;
	func->add(asmMov, { regArg(rax), varLoc });
	func->add(asmMov, { intArg(env->getType("Int64")->typeId), varLoc->withOffset(1) });

	endAt->emitAsm(prog, func);
	ensureType(prog, func, { env->getType("Int64")->typeId }, endAt);
	func->add(asmPushq, { regArg(rax) });

	// func->add(asmCmp, { sptOf(new AsmOffset(0, rsp)), regArg(rax) });
	func->add(asmCmp, { regArg(rax), varLoc });
	func->add(asmJumpIf, { flagArg("g"), labelArg(labelEnd->getLabel(prog)) });

	func->add(labelBegin);
	body->emitAsm(prog, func);

	func->add(asmMov, { varLoc, regArg(rcx) });
	func->add(asmInc, { varLoc });
	func->add(asmCmp, { regArg(rcx), sptOf(new AsmOffset(0, rsp)) });
	func->add(asmJumpIf, { flagArg("ne"), labelArg(labelBegin->getLabel(prog)) });
	func->add(labelEnd);
	func->add(asmPopq, { regArg(r10) });
}
void FlowWhile::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	auto labelBegin = sptOf(new AsmIns(asmNop, {}));
	auto labelEnd = sptOf(new AsmIns(asmNop, {}));

	func->add(labelBegin);
	condition->emitAsm(prog, func);
	ensureType(prog, func, { env->getType("Bool")->typeId }, condition);

	func->add(asmTest, { intArg(1), regArg(rax) });
	func->add(asmJumpIf, { flagArg("e"), labelArg(labelEnd->getLabel(prog)) });
	body->emitAsm(prog, func);
	func->add(asmJump, { labelArg(labelBegin->getLabel(prog)) });
	func->add(labelEnd);
}
void FlowIfElse::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	condition->emitAsm(prog, func);
	ensureType(prog, func, { env->getType("Bool")->typeId }, condition);

	auto labelElse = sptOf(new AsmIns(asmNop, {}));
	auto labelEnd = sptOf(new AsmIns(asmNop, {}));
	func->add(asmTest, { intArg(1), regArg(rax) });
	func->add(asmJumpIf, { flagArg("e"), labelArg(labelElse->getLabel(prog)) });

	ifTrue->emitAsm(prog, func);
	if (!type->isKnown() && ifTrue->getType()->isKnown()) {
		func->add(asmMov, { intArg(ifTrue->getType()->typeId), regArg(rbx) });
	}
	func->add(asmJump, { labelArg(labelEnd->getLabel(prog)) });

	func->add(labelElse);
	ifFalse->emitAsm(prog, func);
	if (!type->isKnown() && ifFalse->getType()->isKnown()) {
		func->add(asmMov, { intArg(ifFalse->getType()->typeId), regArg(rbx) });
	}
	func->add(labelEnd);
}

void Argument::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	name->asmLoc = sptOf(new AsmOffset(func->argOffset));
	func->argOffset += 2;
}
void DefStruct::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	auto opPush = sptOf(new AsmIns(asmPushq, { regArg(rax) }, "print_" + name->val));
	func->add(opPush);

	std::string openStr = prog->store(name->val + "(");
	std::string commaStr = prog->store(", ");
	std::string closeStr = prog->store(")");

	func->add(asmLoadAddr, { labelArg(openStr), regArg(rdi) });
	func->add(asmCall, { labelArg("printf_call") });
	int offset = 0;
	for (int iMember = 0; iMember < (int)members.size(); iMember++) {
		if (iMember) {
			func->add(asmLoadAddr, { labelArg(commaStr), regArg(rdi) });
			func->add(asmCall, { labelArg("printf_call") });
		}
		func->add(asmMov, { sptOf(new AsmOffset(0, rsp)), regArg(rcx) });
		auto loc = sptOf(new AsmOffset(offset, rcx));
		func->add(asmMov, { loc, regArg(rax) });

		if (!members[iMember]->argType->isKnown()) {
			func->add(asmMov, { loc->withOffset(1), regArg(rbx) });
			offset += 1;
		}
		func->add(asmCall, { labelArg("print_" + members[iMember]->argType->name->val) });
		offset += 1;
	}

	func->add(asmLoadAddr, { labelArg(closeStr), regArg(rdi) });
	func->add(asmCall, { labelArg("printf_call") });
	func->add(asmPopq, { regArg(r10) });
	func->add(asmRet, { });
}
void DefFunc::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
	func = sptOf(new AsmFunc(asmName, isMain));
	if (isMain) {
		func->add(asmMov, { intArg(0), regArg(r12) }); // Ensure boolean comparisons return 0 or 1
	}
	else if (!returnType->isKnown()) {
		func->needReturnType = true;
	}

	prog->add(func);
	for (auto arg : args) {
		arg->emitAsm(prog, func);
	}
	body->emitAsm(prog, func);

	if (isMain) {
		func->add(asmBitXor, { regArg(rax), regArg(rax) });
	}
	else if (body->type->isKnown() && func->needReturnType) {
		func->add(asmMov, { body->getAsmType(), regArg(rbx) });
	}
	func->add(func->footerOp);
	if (returnType->isKnown()) {
		ensureType(prog, func, { returnType->typeId }, nullptr,
			"Wrong default return type for %s, defined line %d",
			{ prog->storeArg(name->val), intArg(loc.first_line) });
	}
}
void FuncDispacher::emitAsm(spt<AsmProg> prog, spt<AsmFunc> asmFunc) {
	for (auto& f : functions) {
		f->emitAsm(prog, asmFunc);
	}
	asmFunc = sptOf(new AsmPrimitiveCode());
	prog->add(asmFunc);

	auto errorLabel = sptOf(new AsmIns(asmNop, {}, "dispatchError_" + asmName));
	std::vector<std::vector<spt<DefFunc>>> funcsByNArgs;
	for (spt<DefFunc>& func : functions) {
		if (funcsByNArgs.size() <= func->args.size()) {
			funcsByNArgs.resize(func->args.size() + 1);
		}
		funcsByNArgs[func->args.size()].push_back(func);
	}
	for (int nArgs = 0; nArgs < (int)funcsByNArgs.size(); nArgs++) {
		if (funcsByNArgs[nArgs].size()) {
			auto dispatchLabel = sptOf(new AsmIns(asmNop, {}, getAsmName(nArgs)));
			asmFunc->add(dispatchLabel);
			dynamicDispatch(prog, asmFunc, errorLabel, 0, funcsByNArgs[nArgs]);
		}
	}

	asmFunc->add(errorLabel);
	asmFunc->abort(prog, "No definition of " + asmName + " matches these arguments (line %d, characters %d-%d)",
		{ intArg(loc.first_line),
				intArg(loc.first_column),
				intArg(loc.last_column) });
}

void FuncDispacher::dynamicDispatch(spt<AsmProg> prog, spt<AsmFunc> asmFunc, spt<AsmIns> errorLabel, int iArg, std::vector<spt<DefFunc>> funcs) {
	if (funcs.size() == 0) {
		asmFunc->add(asmJump, { labelArg(errorLabel->getLabel(prog)) });
		return;
	}
	if (iArg >= (int)funcs[0]->args.size()) {
		if (funcs.size() == 1) {
			asmFunc->add(asmJump, { labelArg(funcs[0]->asmName) });
		}
		else {
			asmFunc->add(asmJump, { labelArg(errorLabel->getLabel(prog)) });
		}
		return;
	}

	std::vector<spt<DefFunc>> funcsAny;
	std::map<int, std::vector<spt<DefFunc>>> funcsTyped;

	for (auto f : funcs) {
		if (f->args[iArg]->argType->isKnown()) {
			int iType = f->args[iArg]->argType->typeId;
			if (funcsTyped.count(iType) == 0) {
				funcsTyped[iType] = {};
			}
			funcsTyped[iType].push_back(f);
		}
		else {
			funcsAny.push_back(f);
		}
	}
	spt<AsmIns> nextLabel(nullptr);
	for (auto& typeFuncsPair : funcsTyped) {
		std::vector<spt<DefFunc>> funcsGroup = typeFuncsPair.second;
		funcsGroup.insert(funcsGroup.end(), funcsAny.begin(), funcsAny.end());

		if (nextLabel) asmFunc->add(nextLabel);
		nextLabel = sptOf(new AsmIns(asmNop, {}));
		asmFunc->add(asmCmp, { intArg(typeFuncsPair.first),
			sptOf(new AsmOffset(2 * (iArg + 1), rsp)) });
		asmFunc->add(asmJumpIf, { flagArg("ne"), labelArg(nextLabel->getLabel(prog)) });
		dynamicDispatch(prog, asmFunc, errorLabel, iArg + 1, funcsGroup);
	}
	if (nextLabel) asmFunc->add(nextLabel);
	dynamicDispatch(prog, asmFunc, errorLabel, iArg + 1, funcsAny);
}
