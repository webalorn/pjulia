#include "ast.hpp"

void Ast::initEnvTypes() {
	for (auto decl : declarations) {
		decl->initEnv(env);
	}
	for (auto decl : declarations) {
		decl->refIdents();
	}
	for (auto decl : declarations) {
		decl->setTypes();
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
	type = setAt->type;
}
void IntConst::setTypes() {
	type = env->getType("Int64");
}
void Assignment::setTypes() {
	rvalue->setTypes();

	auto leftIdent = std::dynamic_pointer_cast<Ident>(lvalue);
	if (leftIdent) {
		leftIdent->setAt->mergeType(rvalue->type);
	}
	lvalue->setTypes();
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
		type = env->getType("Any");
	}
	else {
		auto str = std::dynamic_pointer_cast<DefStruct>(object->type);
		if (!str) throw JError(object->loc, "Should be a struct");
		if (!str->isMutable) throw JError(object->loc, "Should be mutable");
		if (!str->hasMember(member->val)) {
			throw JError(object->loc, "The structure has no member " + member->val);
		}
		type = str->env->getInitialVar(member)->type;
	}
}

void CallParamList::setTypes() {
	for (auto child : expressions) {
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
	type = funcPt->getReturnType();
}
void ReturnVal::setTypes() {
	value->setTypes();
	type = env->getType("Any");
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
}
