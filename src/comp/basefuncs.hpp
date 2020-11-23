#if !defined(BASE_FUNCS_HPP)
#define BASE_FUNCS_HPP

#include "ast.hpp"

struct BuiltinFunc : public Declaration, public Callable {
	spt<Ident> name;

	inline BuiltinFunc(std::string nameStr) : name(sptOf(new Ident(NO_LOC, nameStr))) {};

	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	// inline virtual spt<Type> getReturnType() { return returnType; };
	// virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
	// std::string getSignature();

	FINAL_AST_NODE_CLS
};

#endif // BASE_FUNCS_HPP
