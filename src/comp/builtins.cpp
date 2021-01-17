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
void BuiltinFunc::emitAsm(spt<AsmProg>, spt<AsmFunc>) {
	// Do nothing because not a real declaration
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
	// Because I like when its ordered
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


void  BuiltinPrintLn::emitAsm(spt<AsmProg>, spt<AsmFunc>) {
	// nothing
}
void BuiltinPrintLn::emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) {
	// call parent + print newline
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

// /*
// 	Abstracts : code that can't be directly called by the user but will be some other way
// */

// std::string AbstractBuiltin::getSignature() {
// 	throw UsageError("[INTERNAL] AbstractBuiltin");
// }
// bool AbstractBuiltin::matchArgs(std::vector<spt<Type>>&) {
// 	throw UsageError("[INTERNAL] AbstractBuiltin");
// }
// void AbstractBuiltin::emitAsmCall(spt<AsmProg>, spt<AsmFunc>, spt<CallParamList>) {
// 	throw UsageError("[INTERNAL] AbstractBuiltin");
// }


// // Eq function function


// void BuiltinEqual::emitAsm(spt<AsmProg> prog, spt<AsmFunc> func) {
// 	// Generate eq_any_struct
// 	auto labelFunc = sptOf(new AsmIns(asmNop, {}, "eq_any_struct"));
// 	func->add(labelFunc);

// 	std::vector<spt<DefStruct>> structs;
// 	for (auto declPair : env->declarations) {
// 		spt<DefStruct> declStr = std::dynamic_pointer_cast<DefStruct>(declPair.second);
// 		if (declStr) {
// 			structs.push_back(declStr);
// 		}
// 	}
// 	for (spt<DefStruct>& str : structs) {
// 		func->add(asmCmp, { intArg(str->typeId), regArg(rbx) });
// 		func->add(asmJumpIf, { flagArg("e"), labelArg("eq_struct_" + str->name->val) });
// 	}
// 	func->add(asmRet, {});

// 	// Generate eq_struct_<name>
// 	for (spt<DefStruct>& str : structs) {
// 		auto labelFuncComp = sptOf(new AsmIns(asmNop, {}, "eq_struct_" + str->name->val));
// 		auto labelCompFail = sptOf(new AsmIns(asmNop, {}, "eq_fail_" + str->name->val));
// 		func->add(labelFuncComp);

// 		int offset = 0;
// 		for (int iMember = 0; iMember < (int)str->members.size(); iMember++) {
// 			auto argType = str->members[iMember]->argType;
// 			auto loc1 = sptOf(new AsmOffset(offset, rax));
// 			auto loc2 = sptOf(new AsmOffset(offset, rdi));
// 			func->add(asmMov, { loc2, regArg(r13) });

// 			/*
// 			auto labelSimpleComp = sptOf(new AsmIns(asmNop, {}));
// 			auto labelSkipComp = sptOf(new AsmIns(asmNop, {}));

// 			if (!argType->isKnown()) { // If we don't know the type during compilation
// 				// Comparer les types
// 				func->add(asmMov, { loc2->withOffset(1), regArg(rbx) });
// 				func->add(asmCmp, { loc1->withOffset(1), regArg(rbx) });
// 				func->add(asmJumpIf, { flagArg("ne"), labelArg(labelCompFail->getLabel(prog)) });

// 				// Check if it is a base type
// 				func->add(asmCmp, { intArg(5), regArg(rbx) }); // 5 = First custom type id
// 				func->add(asmJumpIf, { flagArg("l"), labelArg(labelSimpleComp->getLabel(prog)) });
// 			}
// 			if (!argType->isKnown() || argType->isStruct()) {
// 				// In case this is a substructure
// 				func->add(asmPushq, { regArg(rax) });
// 				func->add(asmPushq, { regArg(rdi) });

// 				func->add(asmMov, { loc1, regArg(rax) });
// 				func->add(asmMov, { loc2, regArg(rdi) });

// 				if (argType->isStruct()) {
// 					func->add(asmCall, { labelArg("eq_struct_" + argType->name->val) });
// 				}
// 				else {
// 					func->add(asmCall, { labelArg("eq_any_struct") });
// 				}

// 				func->add(asmPopq, { regArg(rdi) });
// 				func->add(asmPopq, { regArg(r13) });
// 				func->add(asmCmp, { intArg(0), regArg(rax) });
// 				func->add(asmJumpIf, { flagArg("e"), labelArg(labelCompFail->getLabel(prog)) });


// 				func->add(asmMov, { regArg(r13), regArg(rax) });
// 				func->add(asmJump, { labelArg(labelSkipComp->getLabel(prog)) });
// 			}

// 			// Comparaison simple
// 			if (!argType->isStruct()) {
// 			func->add(labelSimpleComp);*/
// 			func->add(asmCmp, { loc1, regArg(r13) });
// 			func->add(asmJumpIf, { flagArg("ne"), labelArg(labelCompFail->getLabel(prog)) });
// 			/* }
// 			func->add(labelSkipComp); */

// 			if (!argType->isKnown()) offset += 1;
// 			offset += 1;
// 		}

// 		func->add(asmMov, { intArg(1), regArg(rax) });
// 		func->add(asmRet, {});

// 		func->add(labelCompFail);
// 		func->add(asmMov, { intArg(0), regArg(rax) });
// 		func->add(asmRet, {});
// 	}
// }
