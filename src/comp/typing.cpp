#include "ast.hpp"

void Ast::initEnvTypes() {
	env->inFunction = mainFunc;
	for (auto decl : declarations) {
		decl->initEnv(env);
	}
	for (auto decl : declarations) {
		decl->refIdents();
	}
	// for (auto decl : declarations) {
	// 	decl->setTypes();
	// }
	for (auto declPair : env->declarations) {
		declPair.second->setTypes();
	}
}

bool typeMatch(spt<Type> type, std::vector<PrimitiveType> matchWith) {
	auto asBaseType = std::dynamic_pointer_cast<BaseType>(type);
	if (asBaseType) {
		if (asBaseType->type == TAny) return true;
		for (PrimitiveType t : matchWith) {
			if (asBaseType->type == t) return true;
		}
	}
	return false;
}
void assertType(spt<Expr> expr, std::vector<PrimitiveType> matchWith) {
	if (!typeMatch(expr->type, matchWith)) {
		std::string ofType = asStr(matchWith[0]);
		if (matchWith.size() > 1) ofType += " or " + asStr(matchWith[1]);
		std::string should = "Should";
		auto asIdent = std::dynamic_pointer_cast<Ident>(expr);
		if (asIdent) {
			should = "\"" + asIdent->val + "\" should";
		}

		throw JError(expr->loc, should + " be of type " + ofType);
	}
}

/*
	Set types
*/

void ExprBlock::setTypes() {
	for (auto child : expressions) {
		child->setTypes();
	}
	if (expressions.empty()) {
		type = env->getType("Nothing");
	}
	else {
		type = expressions.back()->type;
	}
}
void BaseType::setTypes() {}
void Ident::setTypes() {
	if (setAt->type) {
		type = setAt->type;
	}
	else {
		type = env->getType("Any"); // TODO ??
	}
}
void IntConst::setTypes() {
	type = env->getType("Int64");
}
void Assignment::setTypes() {
	rvalue->setTypes();

	auto leftIdent = std::dynamic_pointer_cast<Ident>(lvalue);
	if (leftIdent) {
		if (!leftIdent->setAt->isMutable) {
			throw JError(loc, "The variable " + leftIdent->val + " can't be assigned");
		}
		leftIdent->setAt->mergeType(rvalue->type);
	}
	lvalue->setTypes();
	if (!leftIdent) {
		// lvalue->type->name->val != "Any"
		auto leftDot = std::dynamic_pointer_cast<DotOp>(lvalue);
		auto str = std::dynamic_pointer_cast<DefStruct>(leftDot->object->type);
		if (!typesMatch(leftDot->type, rvalue->type)) {
			throw JError(loc, "Can't assign a value of type ::" + rvalue->type->name->val + " to the member " + leftDot->member->val + "::" + leftDot->type->name->val + " of the structure " + leftDot->object->type->name->val);
		}
		if (str) {
			if (!str->isMutable) throw JError(loc, "The structure " + str->name->val + " is not mutable");
		}
	}
	type = rvalue->type;
}
void StrConst::setTypes() {
	type = env->getType("String");
}
void BoolConst::setTypes() {
	type = env->getType("Bool");
}
void BinOp::setTypes() {
	left->setTypes();
	right->setTypes();
	type = env->getType("Bool");
	if (op == OpEq || op == OpNotEq) {
	}
	else if (op == OpAnd || op == OpOr) {
		assertType(left, { TBool });
		assertType(right, { TBool });
	}
	else if (op == OpLower || op == OpLowerEq || op == OpGreater || op == OpGreaterEq) {
		assertType(left, { TBool, TInt64 });
		assertType(right, { TBool, TInt64 });
	}
	else {
		assertType(left, { TInt64 });
		assertType(right, { TInt64 });
		type = env->getType("Int64");
	}
}
void UnaryOp::setTypes() {
	expr->setTypes();
	if (op == UnaryMinus) {
		assertType(expr, { TInt64 });
		type = env->getType("Int64");
	}
	else { // UnaryNot
		assertType(expr, { TBool });
		type = env->getType("Bool");
	}
}
void DotOp::setTypes() {
	object->setTypes();
	if (typeMatch(object->type, { TAny })) {
		std::vector<spt<DefStruct>> structs = env->structsWith(member);
		std::cerr << "nb = " << structs.empty() << "\n";
		if (structs.empty()) {
			throw JError(loc, "No structure with a member " + member->val);
		}
		else if (structs.size() == 1) {
			object->type = structs[0];
		}
	}

	if (typeMatch(object->type, { TAny })) {
		type = env->getType("Any");
	}
	else {
		auto str = std::dynamic_pointer_cast<DefStruct>(object->type);
		if (!str) throw JError(object->loc, "Should be a struct");
		if (!str->hasMember(member->val)) {
			throw JError(object->loc, "The structure has no member " + member->val);
		}
		type = str->env->getInitialVar(member)->type;
	}
}

void CallParamList::setTypes() {
	for (auto& child : expressions) {
		child->setTypes();
	}
}
void CallFunction::setTypes() {
	args->setTypes();
	std::vector<spt<Type>> argTypes;
	for (auto& arg : args->expressions) {
		argTypes.push_back(arg->type);
	}
	funcPt->checkCallArgs(loc, argTypes);
	auto dispacher = std::dynamic_pointer_cast<FuncDispacher>(funcPt);
	if (dispacher) {
		funcPt = dispacher->tryPreDispatch(loc, argTypes);
	}

	type = funcPt->getReturnType();
}
void ReturnVal::setTypes() {
	value->setTypes();
	type = env->getType("Any");
	if (!typesMatch(value->type, env->inFunction->returnType)) {
		throw JError(loc, "return value type ::" + value->type->name->val + " doesn't match the function " + env->inFunction->name->val + " return type ::" + env->inFunction->returnType->name->val);
	}
}
void FlowFor::setTypes() {
	counter->type = env->getType("Int64");
	type = env->getType("Nothing");

	startAt->setTypes();
	endAt->setTypes();
	assertType(startAt, { TInt64 });
	assertType(endAt, { TInt64 });
	body->setTypes();
}
void FlowWhile::setTypes() {
	condition->setTypes();
	assertType(condition, { TBool });
	body->setTypes();
	type = env->getType("Nothing");
}
void FlowIfElse::setTypes() {
	condition->setTypes();
	ifTrue->setTypes();
	ifFalse->setTypes();

	assertType(condition, { TBool });
	type = ifTrue->type;
	mergeType(ifFalse->type);
}

void Argument::setTypes() {
	name->setAt->type = env->getType(typeName);
	name->setTypes();
}
void DefStruct::setTypes() {
	for (auto member : members) {
		member->setTypes();
	}
}
void DefFunc::setTypes() {
	for (auto arg : args) {
		arg->setTypes();
	}
	body->setTypes();

	if (!typesMatch(returnType, body->type)) {
		throw JError(loc, "The implicit return value (last instruction) of the function " + name->val + " has type ::" + body->type->name->val + ", which doesn't match the function return type ::" + returnType->name->val);
	}
}
void FuncDispacher::setTypes() {
	checkAmbiguous();
	for (auto& f : functions) {
		f->setTypes();
	}
}
