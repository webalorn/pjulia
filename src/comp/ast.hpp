#if !defined(AST_HPP)
#define AST_HPP

#include <vector>
#include <deque>
#include <map>
#include <string>
#include <ostream>
#include <iostream>

#include "../util.hpp"
#include "../asm/asm.hpp"

struct Declaration;
struct Type;
struct DefFunc;
struct DefStruct;
struct BaseType;
struct Ident;
struct Callable;
struct CallParamList;

#define FINAL_AST_NODE_CLS \
	virtual void show(std::ostream& os) const; \
	virtual void initEnv(spt<Env> parentEnv); \
	virtual void refIdents(); \
	virtual void setTypes(); \
	virtual void emitAsm(spt<AsmProg>, spt<AsmFunc>);

enum BinaryOperation {
	OpEq, OpNotEq, OpLower, OpLowerEq, OpGreater, OpGreaterEq,
	OpPlus, OpMinus, OpTimes, OpMod, OpPower, OpAnd, OpOr
};
enum UnaryOperation {
	UnaryNot, UnaryMinus
};
enum PrimitiveType {
	TAny, TNothing, TInt64, TBool, TString
};
const YYLTYPE NO_LOC = { 0, 0, 0, 0 };

std::ostream& operator<<(std::ostream& os, BinaryOperation op);
std::ostream& operator<<(std::ostream& os, PrimitiveType type);
std::ostream& operator<<(std::ostream& os, UnaryOperation op);


class Env;
class Ast;

class Env : public std::enable_shared_from_this<Env> {
protected:
	std::map<std::string, spt<DefStruct>> memberToStruct;
	int lastTypeId;
	bool softScope;
public:
	spt<Env> from;
	std::map<std::string, spt<Declaration>> declarations;
	spt<DefFunc> inFunction;
	Env(spt<Env> from = nullptr, bool softScope = false);
	spt<Env> child(bool soft = false);

	bool isNameDefined(spt<Ident> name);
	bool isNameLocal(spt<Ident> name, bool forceLocal = false);
	void add(spt<Ident> name, spt<Declaration> decl);
	void declFunction(spt<Ident> name, spt<DefFunc> decl);
	spt<Declaration> getDeclaration(spt<Ident> name, bool forceLocal = false);
	spt<DefFunc> getFunction(spt<Ident> name);
	spt<Callable> getCallable(spt<Ident> name);
	spt<DefStruct> getStruct(spt<Ident> name);
	spt<Type> getType(spt<Ident> name);
	spt<Type> getType(std::string name);
	spt<Ident> getInitialVar(spt<Ident> name, bool forceLocal = false);
	spt<Ident> getOrCreateVar(spt<Ident> name, bool force = false, bool forceLocal = false);

	spt<DefStruct> structWith(spt<Ident> name);
	void setTypeId(spt<Type> tpPt);

	friend class Ast;
};

class Ast {
protected:
	spt<DefFunc> mainFunc;
	spt<Env> env;
public:
	std::vector<spt<Declaration>> declarations;

	Ast();
	void addDeclaration(spt<Declaration> decl);
	friend std::ostream& operator<<(std::ostream& os, const Ast& ast);
	void initEnvTypes();
	void emitAsm(spt<AsmProg>);
};

/*
	Ast Nodes (meta-classes)
*/

struct AstNode;
struct AstNode : public std::enable_shared_from_this<AstNode> {
	YYLTYPE loc;
	spt<Env> env;

	inline AstNode(const YYLTYPE loc) : loc(loc) {};
	template<class T> inline std::shared_ptr<T> shared_as() {
		auto pt = std::dynamic_pointer_cast<T>(shared_from_this());
		if (!pt) {
			throw JError(NO_LOC, "[INTERNAL] shared_as mismatch types");
		}
		return pt;
	}


	virtual void show(std::ostream& os) const = 0;
	inline virtual ~AstNode() {};

	virtual void initEnv(spt<Env> parentEnv) = 0;
	virtual void refIdents() = 0;
	virtual void setTypes() = 0;
	virtual void emitAsm(spt<AsmProg>, spt<AsmFunc>) = 0;
};


/*
	Real Ast Nodes
*/

struct Callable {
	virtual spt<Type> getReturnType() = 0;
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes) = 0;
	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) = 0;
	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args) = 0;
	void asmCheckArgType(spt<AsmProg> prog, spt<AsmFunc> func, spt<Expr> arg, spt<Type> mType);
};
struct Declaration : public AstNode {
	using AstNode::AstNode;
};

struct Type : public Declaration {
	using Declaration::Declaration;
	spt<Ident> name;
	int typeId;
	inline Type(const YYLTYPE loc, spt<Ident> name) : Declaration(loc), name(name) {};
	bool isKnown();
};
struct BaseType : public Type {
	PrimitiveType type;
	inline BaseType(const YYLTYPE loc, spt<Ident> name, PrimitiveType type)
		: Type(loc, name), type(type) {};
	BaseType(std::string str_name, PrimitiveType type);
	FINAL_AST_NODE_CLS
};

// struct StructDecl : public Declaration {};
// struct FuncDecl : public Declaration {};

/*
	Expressions
*/
struct Expr : public Declaration {
	spt<Type> type;
	bool _forceStoreType;

	inline bool forceStore() { return _forceStoreType || !this->getType()->isKnown(); }
	spt<AsmArg> getAsmType();

	using Declaration::Declaration;
	inline Expr(const YYLTYPE loc) : Declaration(loc), _forceStoreType(false) {}
	void mergeType(spt<Type> type2);
	inline virtual spt<Type> getType() { return type; };
};

struct ExprBlock : public Expr {
	using Expr::Expr;
	std::deque<spt<Expr>> expressions;

	void add(spt<Expr> expr);
	void add(Expr* pt);
	void add_front(Expr* pt);
	FINAL_AST_NODE_CLS
};
struct CallParamList : public ExprBlock {
	using ExprBlock::ExprBlock;
	FINAL_AST_NODE_CLS
};

struct LValue : public Expr {
	using Expr::Expr;
};
struct Ident : public LValue {
	std::string val;
	spt<Ident> setAt; // For a variable
	spt<AsmLoc> asmLoc;
	bool initialized;
	bool isMutable;

	inline Ident(const YYLTYPE loc, std::string val)
		: LValue(loc), val(val), setAt(nullptr), asmLoc(nullptr) {
		initialized = false;
		isMutable = true;
	};
	spt<AsmArg> getAsmTypeRef(spt<AsmLoc> loc);
	inline virtual spt<Type> getType() { return setAt->type; };
	FINAL_AST_NODE_CLS
};

struct Constant : public Expr {
	using Expr::Expr;
};

struct IntConst : public Constant {
	long long value;
	inline IntConst(const YYLTYPE loc, long long value) : Constant(loc), value(value) {}
	IntConst(const YYLTYPE loc, std::string);
	FINAL_AST_NODE_CLS
};
struct StrConst : public Constant {
	std::string value;
	inline StrConst(const YYLTYPE loc, std::string value) : Constant(loc), value(value) {}
	FINAL_AST_NODE_CLS
		void convertSpecialChars();
};
struct BoolConst : public Constant {
	bool value;
	inline BoolConst(const YYLTYPE loc, bool value) : Constant(loc), value(value) {}
	FINAL_AST_NODE_CLS
};

struct CallFunction : public Expr {
	spt<Ident> funcName;
	spt<CallParamList> args;
	spt<Callable> funcPt;

	inline CallFunction(const YYLTYPE loc, spt<Ident> funcName, spt<CallParamList> args)
		: Expr(loc), funcName(funcName), args(args) {}
	FINAL_AST_NODE_CLS
};
struct ReturnVal : public Expr {
	spt<Expr> value;
	inline ReturnVal(const YYLTYPE loc, spt<Expr> valuePt) : Expr(loc) {
		value = valuePt;
		if (!value) {
			value = sptOf(new Ident(loc, "nothing"));
		}
	}
	FINAL_AST_NODE_CLS
};

/*
	Expressions : operations
*/

struct Assignment : public Expr {
	spt<LValue> lvalue;
	spt<Expr> rvalue;

	inline Assignment(const YYLTYPE loc, spt<LValue> left, spt<Expr> right)
		: Expr(loc), lvalue(left), rvalue(right) {};
	FINAL_AST_NODE_CLS
};
struct BinOp : public Expr {
	BinaryOperation op;
	spt<Expr> left, right;

	inline BinOp(const YYLTYPE loc, BinaryOperation op, spt<Expr> left, spt<Expr> right)
		: Expr(loc), op(op), left(left), right(right) {};
	FINAL_AST_NODE_CLS
};
struct UnaryOp : public Expr {
	UnaryOperation op;
	spt<Expr> expr;

	inline UnaryOp(const YYLTYPE loc, UnaryOperation op, spt<Expr> expr)
		: Expr(loc), op(op), expr(expr) {};
	FINAL_AST_NODE_CLS
};
struct DotOp : public LValue {
	spt<Expr> object;
	spt<DefStruct> structType;
	spt<Ident> member;

	inline DotOp(const YYLTYPE loc, spt<Expr> object, spt<Ident> member)
		: LValue(loc), object(object), member(member) {};
	FINAL_AST_NODE_CLS
};

/*
	Flow control
*/
struct FlowControl : public Expr {
	using Expr::Expr;
};
struct FlowFor : public FlowControl {
	spt<Ident> counter;
	spt<Expr> startAt, endAt;
	spt<ExprBlock> body;
	inline FlowFor(const YYLTYPE loc, spt<Ident> counter, spt<Expr> startAt, spt<Expr> endAt,
		spt<ExprBlock> body)
		: FlowControl(loc), counter(counter), startAt(startAt), endAt(endAt), body(body) {};
	FINAL_AST_NODE_CLS
};
struct FlowWhile : public FlowControl {
	spt<Expr> condition;
	spt<ExprBlock> body;
	inline FlowWhile(const YYLTYPE loc, spt<Expr> condition, spt<ExprBlock> body)
		: FlowControl(loc), condition(condition), body(body) {};
	FINAL_AST_NODE_CLS
};
struct FlowIfElse : public FlowControl {
	spt<Expr> condition, ifTrue, ifFalse;
	inline FlowIfElse(const YYLTYPE loc, spt<Expr> condition, spt<Expr> ifTrue, spt<Expr> ifFalse)
		: FlowControl(loc), condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {};
	FINAL_AST_NODE_CLS
};

/*
	Structures & functions
*/

struct Argument : public AstNode {
	spt<Ident> name, typeName;
	spt<Type> argType;

	inline Argument(const YYLTYPE loc, spt<Ident> name, spt<Ident> typeName)
		: AstNode(loc), name(name), typeName(typeName) {};
	FINAL_AST_NODE_CLS
};

class ArgumentList : public std::deque<spt<Argument>> {};

struct StructType : public Type {
	using Type::Type;
};

struct DefStruct : public StructType, public Callable {
	bool isMutable;
	ArgumentList members;
	inline bool hasMember(std::string val) {
		for (auto& m : members) {
			if (m->name->val == val) return true;
		}
		return false;
	}

	inline DefStruct(const YYLTYPE loc, bool isMutable, spt<Ident> name)
		: StructType(loc, name), isMutable(isMutable) {};

	inline virtual spt<Type> getReturnType() { return shared_as<Type>(); };
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
	std::string getSignature();

	FINAL_AST_NODE_CLS
};

struct DefFunc : public Declaration, public Callable {
	spt<Ident> name, typeName;
	std::string asmName;
	spt<Type> returnType;
	bool isMain;
	ArgumentList args;
	spt<ExprBlock> body;

	inline DefFunc(const YYLTYPE loc, spt<Ident> name, spt<Ident> typeName, spt<ExprBlock> body)
		: Declaration(loc), name(name), typeName(typeName), body(body) {
		isMain = false;
	};

	inline virtual spt<Type> getReturnType() { return returnType; };
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
	std::string getSignature();

	FINAL_AST_NODE_CLS
};

struct FuncDispacher : public Declaration, public Callable {
	spt<Type> returnType;
	std::string asmName;
	std::vector<spt<DefFunc>> functions;
	inline FuncDispacher() : Declaration(NO_LOC), returnType(nullptr) {};

	virtual spt<Type> getReturnType();
	virtual bool matchArgs(std::vector<spt<Type>>& callTypes);
	virtual void checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	virtual void emitAsmCall(spt<AsmProg> prog, spt<AsmFunc> func, spt<CallParamList> args);
	spt<Callable> tryPreDispatch(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes);
	std::string getSignature();
	void checkAmbiguous();

	std::string getAsmName(int nbArgs);
	void dynamicDispatch(spt<AsmProg> prog, spt<AsmFunc> asmFunc, spt<AsmIns> errorLabel, int iArg, std::vector<spt<DefFunc>> funcs);

	FINAL_AST_NODE_CLS
};

/*
	Template functions & utility
*/
bool typesMatch(spt<Type> type1, spt<Type> type2);

inline std::string typeNameOf(spt<Type> tp) { return tp->name->val; }
inline std::string typeNameOf(spt<Argument> tp) { return tp->typeName->val; }

template<class T> std::string typesToSig(T args) {
	std::stringstream sig;
	sig << "(";
	for (int iArg = 0; iArg < (int)args.size(); iArg++) {
		if (iArg) sig << ", ";
		sig << "::" << typeNameOf(args[iArg]);
	}
	sig << ")";
	return sig.str();
}

#endif // AST_HPP
