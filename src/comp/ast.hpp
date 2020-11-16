#if !defined(AST_HPP)
#define AST_HPP

#include <memory>
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <ostream>

#include "../util.hpp"

struct Declaration;
#define spt std::shared_ptr

enum BinaryOperation {
	OpEq, OpNotEq, OpLower, OpLowerEq, OpGreater, OpGreaterEq,
	OpPlus, OpMinus, OpTimes, OpMod, OpPower, OpAnd, OpOr
};
enum UnaryOperation {
	UnaryNot, UnaryMinus
};


class Ast {
protected:
public:
	std::vector<spt<Declaration>> declarations;
	Ast();
	friend std::ostream& operator<<(std::ostream& os, const Ast& ast);
};

/*
	Ast Nodes
*/
struct AstNode {
	YYLTYPE loc;
	inline AstNode(const YYLTYPE loc) : loc(loc) {};
	virtual void show(std::ostream& os) const = 0;
	inline virtual ~AstNode() {};
};

// Inline converter
template<class T> inline std::shared_ptr<T> sptOf(AstNode* pt) {
	return std::shared_ptr<T>(static_cast<T*>(pt));
}


struct Declaration : public AstNode {
	using AstNode::AstNode;
};

// struct StructDecl : public Declaration {};
// struct FuncDecl : public Declaration {};

/*
	Expressions
*/
struct Expr : public Declaration {
	using Declaration::Declaration;
};
struct ExprBlock : public Expr {
	using Expr::Expr;
	std::deque<spt<Expr>> expressions;
	void add(spt<Expr> expr);
	void add(AstNode* pt);
	void add_front(AstNode* pt);
	virtual void show(std::ostream& os) const;
};
struct CallParamList : public ExprBlock {
	using ExprBlock::ExprBlock;
	virtual void show(std::ostream& os) const;
};

struct LValue : public Expr {
	using Expr::Expr;
};
struct Ident : public LValue {
	std::string val;
	inline Ident(const YYLTYPE loc, std::string val) : LValue(loc), val(val) {};
	virtual void show(std::ostream& os) const;
};

struct Constant : public Expr {
	using Expr::Expr;
};

struct IntConst : public Constant {
	long long value;
	inline IntConst(const YYLTYPE loc, long long value) : Constant(loc), value(value) {}
	IntConst(const YYLTYPE loc, std::string);
	virtual void show(std::ostream& os) const;
};
struct StrConst : public Constant {
	std::string value;
	inline StrConst(const YYLTYPE loc, std::string value) : Constant(loc), value(value) {}
	virtual void show(std::ostream& os) const;
	void convertSpecialChars();
};
struct BoolConst : public Constant {
	bool value;
	inline BoolConst(const YYLTYPE loc, bool value) : Constant(loc), value(value) {}
	virtual void show(std::ostream& os) const;
};

struct CallFunction : public Expr {
	spt<Ident> func;
	spt<CallParamList> args;
	inline CallFunction(const YYLTYPE loc, spt<Ident> func, spt<CallParamList> args)
		: Expr(loc), func(func), args(args) {}
	virtual void show(std::ostream& os) const;
};
struct ReturnVal : public Expr {
	spt<Expr> value; // Can be nullptr
	inline ReturnVal(const YYLTYPE loc, spt<Expr> value) : Expr(loc), value(value) {}
	virtual void show(std::ostream& os) const;
};

/*
	Expressions : operations
*/

struct Assignment : public Expr {
	spt<LValue> lvalue;
	spt<Expr> rvalue;

	inline Assignment(const YYLTYPE loc, spt<LValue> left, spt<Expr> right)
		: Expr(loc), lvalue(left), rvalue(right) {};
	virtual void show(std::ostream& os) const;
};
struct BinOp : public Expr {
	BinaryOperation op;
	spt<Expr> left, right;

	inline BinOp(const YYLTYPE loc, BinaryOperation op, spt<Expr> left, spt<Expr> right)
		: Expr(loc), op(op), left(left), right(right) {};
	virtual void show(std::ostream& os) const;
};
struct UnaryOp : public Expr {
	UnaryOperation op;
	spt<Expr> expr;

	inline UnaryOp(const YYLTYPE loc, UnaryOperation op, spt<Expr> expr)
		: Expr(loc), op(op), expr(expr) {};
	virtual void show(std::ostream& os) const;
};
struct DotOp : public LValue {
	spt<Expr> object;
	spt<Ident> member;

	inline DotOp(const YYLTYPE loc, spt<Expr> object, spt<Ident> member)
		: LValue(loc), object(object), member(member) {};
	virtual void show(std::ostream& os) const;
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
	virtual void show(std::ostream& os) const;
};
struct FlowWhile : public FlowControl {
	spt<Expr> condition;
	spt<ExprBlock> body;
	inline FlowWhile(const YYLTYPE loc, spt<Expr> condition, spt<ExprBlock> body)
		: FlowControl(loc), condition(condition), body(body) {};
	virtual void show(std::ostream& os) const;
};
struct FlowIfElse : public FlowControl {
	spt<Expr> condition, ifTrue, ifFalse;
	inline FlowIfElse(const YYLTYPE loc, spt<Expr> condition, spt<Expr> ifTrue, spt<Expr> ifFalse)
		: FlowControl(loc), condition(condition), ifTrue(ifTrue), ifFalse(ifFalse) {};
	virtual void show(std::ostream& os) const;
};

/*
	Structures & functions
*/

struct Argument : public AstNode {
	spt<Ident> name, type;

	inline Argument(const YYLTYPE loc, spt<Ident> name, spt<Ident> type)
		: AstNode(loc), name(name), type(type) {};
	virtual void show(std::ostream& os) const;
};

class ArgumentList : public std::deque<spt<Argument>> {};

struct DefStruct : public Declaration {
	bool isMutable;
	spt<Ident> name;
	std::deque<spt<Argument>> members;

	inline DefStruct(const YYLTYPE loc, bool isMutable, spt<Ident> name)
		: Declaration(loc), isMutable(isMutable), name(name) {};
	virtual void show(std::ostream& os) const;
};

struct DefFunc : public Declaration {
	spt<Ident> name, type;
	std::deque<spt<Argument>> args;
	spt<ExprBlock> body;

	inline DefFunc(const YYLTYPE loc, spt<Ident> name, spt<Ident> type, spt<ExprBlock> body)
		: Declaration(loc), name(name), type(type), body(body) {};
	virtual void show(std::ostream& os) const;
};


#endif // AST_HPP
