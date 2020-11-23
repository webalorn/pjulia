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

// Div function
std::string BuiltinDiv::getSignature() {
	return "div(::Int64, ::Int64)";
}
bool BuiltinDiv::matchArgs(std::vector<spt<Type>>& callTypes) {
	auto intType = env->getType("Int64");
	return callTypes.size() == 2 &&
		typesMatch(callTypes[0], intType) && typesMatch(callTypes[1], intType);
}
