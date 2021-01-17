#if !defined(BUILTINS_HPP)
#define BUILTINS_HPP

#include "ast.hpp"

struct BuiltinFunc : public Declaration, public Callable {
	spt<Ident> name;

	inline BuiltinFunc(std::string nameStr)
		: Declaration(NO_LOC), name(sptOf(new Ident(NO_LOC, nameStr))) {};

	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	virtual std::string getSignature() = 0;
	FINAL_AST_NODE_CLS
};

struct BuiltinPrint : public BuiltinFunc {
	inline BuiltinPrint(std::string nameStr = "print") : BuiltinFunc(nameStr) {}
	inline virtual spt<Type> getReturnType() { return env->getType("Nothing"); };
	virtual std::string getSignature();
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
	void emitAsm(spt<AsmProg> prog, spt<AsmFunc> func);

	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
};

struct BuiltinPrintLn : public BuiltinPrint {
	inline BuiltinPrintLn() : BuiltinPrint("println") {}
	virtual std::string getSignature();
	void emitAsm(spt<AsmProg> prog, spt<AsmFunc> func);

	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
};

struct BuiltinDiv : public BuiltinFunc {
	inline BuiltinDiv() : BuiltinFunc("div") {}
	inline virtual spt<Type> getReturnType() { return env->getType("Int64"); };
	virtual std::string getSignature();
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);

	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
};

// struct AbstractBuiltin : public BuiltinFunc {
// 	inline AbstractBuiltin(std::string name) : BuiltinFunc("@" + name) {}
// 	inline virtual spt<Type> getReturnType() { return env->getType("Any"); };
// 	virtual std::string getSignature();
// 	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
// 	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
// };

// struct BuiltinEqual : public AbstractBuiltin {
// 	inline BuiltinEqual() : AbstractBuiltin("equal") {}
// 	void emitAsm(spt<AsmProg> prog, spt<AsmFunc> func);
// };


#endif // BUILTINS_HPP
