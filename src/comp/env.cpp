#include "ast.hpp"

void Env::setTypeId(spt<Type> tpPt) {
	if (from) {
		from->setTypeId(tpPt);
	}
	else {
		tpPt->typeId = (lastTypeId++);
	}
}

/*
	Build the environments
*/

void ExprBlock::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	for (auto child : expressions) {
		child->initEnv(env);
	}
}
void BaseType::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	name->initEnv(env);
	env->add(name, shared_as<BaseType>());
	env->setTypeId(shared_as<Type>());
}
void Ident::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
}
void IntConst::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
}
void Assignment::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	rvalue->initEnv(env);
	lvalue->initEnv(env);

	auto leftIdent = std::dynamic_pointer_cast<Ident>(lvalue);
	if (leftIdent) {
		env->getOrCreateVar(leftIdent);
	} // otherwise, it is a dot operation (does not affect env)
}
void StrConst::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
}
void BoolConst::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
}
void BinOp::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	left->initEnv(env);
	right->initEnv(env);
}
void UnaryOp::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	expr->initEnv(env);
}
void DotOp::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	object->initEnv(env);
	member->initEnv(env);
}

void CallParamList::initEnv(spt<Env> parentEnv) {
	ExprBlock::initEnv(parentEnv);
}
void CallFunction::initEnv(spt<Env> parentEnv) {
	env = parentEnv->child();
	funcName->initEnv(env);
	args->initEnv(env);
}
void ReturnVal::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	value->initEnv(env);
}
void FlowFor::initEnv(spt<Env> parentEnv) {
	env = parentEnv->child(true); // TODO : WTF is going on with the for loop ???

	counter->initEnv(env);
	env->getOrCreateVar(counter, true, true);

	startAt->initEnv(parentEnv);
	endAt->initEnv(parentEnv);
	body->initEnv(env);
}
void FlowWhile::initEnv(spt<Env> parentEnv) {
	env = parentEnv->child(true);
	condition->initEnv(env);
	body->initEnv(env);
}
void FlowIfElse::initEnv(spt<Env> parentEnv) {
	env = parentEnv;

	condition->initEnv(env);
	ifTrue->initEnv(env);
	ifFalse->initEnv(env);
}

void Argument::initEnv(spt<Env> parentEnv) {
	env = parentEnv;
	name->initEnv(env);
	typeName->initEnv(env);
	env->getOrCreateVar(name, true);
}
void DefStruct::initEnv(spt<Env> parentEnv) {
	name->initEnv(parentEnv);
	parentEnv->add(name, shared_as<DefStruct>());
	parentEnv->setTypeId(shared_as<Type>());

	env = parentEnv->child();
	for (auto member : members) {
		member->initEnv(env);
		// Because struct must reference only previously defined structs
		member->argType = env->getType(member->typeName);
	}
}
void DefFunc::initEnv(spt<Env> parentEnv) {
	parentEnv->declFunction(name, shared_as<DefFunc>());
	env = isMain ? parentEnv : parentEnv->child();
	env->inFunction = shared_as<DefFunc>();

	for (auto arg : args) {
		arg->initEnv(env);
	}
	name->initEnv(env);
	typeName->initEnv(env);
	body->initEnv(env);
}
void FuncDispacher::initEnv(spt<Env>) {
	// env = parentEnv;
	// for (auto& f : functions) {
	// 	f->initEnv(env);
	// }
	throw JError(NO_LOC, "[INTERNAL FuncDispacher::initEnv]");
}

/*
	Reference identifiers
*/

template<class T>
void setRefered(spt<T> node, bool setInitIdent = false) {
	spt<Ident> ident = std::dynamic_pointer_cast<Ident>(node);
	if (ident) {
		auto ptRefIdent = ident->env->getInitialVar(ident);
		if (setInitIdent) {
			ptRefIdent->initialized = true;
		}
		else if (!ptRefIdent->initialized && strictTypeMode) {
			throw JError(node->loc, ptRefIdent->val + " accessed before being initialized");
		}
		ident->setAt = ptRefIdent;
		ident->initialized = true;
	}
	else {
		node->refIdents();
	}
}

void ExprBlock::refIdents() {
	for (auto& child : expressions) {
		setRefered(child);
	}
}
void BaseType::refIdents() {}
void Ident::refIdents() { throw JError(loc, "[ERROR ref Ident]"); }
void IntConst::refIdents() {}
void Assignment::refIdents() {
	setRefered(rvalue);
	setRefered(lvalue, true);
}
void StrConst::refIdents() {}
void BoolConst::refIdents() {}
void BinOp::refIdents() {
	setRefered(left);
	setRefered(right);
}
void UnaryOp::refIdents() {
	setRefered(expr);
}
void DotOp::refIdents() {
	setRefered(object);
	// member is a identifier and is left out (for now)
}

void CallParamList::refIdents() {
	ExprBlock::refIdents();
}
void CallFunction::refIdents() {
	funcPt = env->getCallable(funcName);
	setRefered(args);
}
void ReturnVal::refIdents() {
	setRefered(value);
}
void FlowFor::refIdents() {
	setRefered(counter, true);
	setRefered(startAt);
	setRefered(endAt);
	setRefered(body);
}
void FlowWhile::refIdents() {
	setRefered(condition);
	setRefered(body);
}
void FlowIfElse::refIdents() {
	setRefered(condition);
	setRefered(ifTrue);
	setRefered(ifFalse);
}

void Argument::refIdents() {
	argType = env->getType(typeName);
	setRefered(name, true);
	name->type = env->getType(typeName);
}
void DefStruct::refIdents() {
	for (auto& m : members) {
		setRefered(m);
	}
}
void DefFunc::refIdents() {
	for (auto& a : args) {
		setRefered(a);
	}
	returnType = env->getType(typeName);
	setRefered(body);
}
void FuncDispacher::refIdents() {
	for (auto& f : functions) {
		setRefered(f);
	}
}
