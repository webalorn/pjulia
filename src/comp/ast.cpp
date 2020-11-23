#include "ast.hpp"

/*
	Environment
*/
spt<Ident> identAny;

Env::Env(spt<Env> from) : from(from) {}

spt<Env> Env::child() {
	// return sptOf(new Env(sptOf(this)));
	return shared_from_this();
}

bool Env::isNameDefined(spt<Ident> name) {
	return declarations.count(name->val)
		|| (from && from->isNameDefined(name));
}
bool Env::isNameLocal(spt<Ident> name) {
	return declarations.count(name->val);
}
void Env::add(spt<Ident> name, spt<Declaration> decl) {
	if (isNameLocal(name)) {
		throw JError(name->loc, "The identifier " + name->val + " is already defined");
	}
	declarations[name->val] = decl;
}
spt<Declaration> Env::getDeclaration(spt<Ident> name) {
	if (!isNameLocal(name)) {
		if (from) {
			return from->getDeclaration(name);
		}
		throw JError(name->loc, "The identifier " + name->val + " is not defined");
	}
	return declarations[name->val];
}
spt<DefFunc> Env::getFunction(spt<Ident> name) {
	auto pt = std::dynamic_pointer_cast<DefFunc>(getDeclaration(name));
	if (!pt) {
		throw JError(name->loc, name->val + " is not a function");
	}
	return pt;
}
spt<Callable> Env::getCallable(spt<Ident> name) {
	auto pt = std::dynamic_pointer_cast<Callable>(getDeclaration(name));
	if (!pt) {
		throw JError(name->loc, name->val + " is not callable");
	}
	return pt;
}
spt<DefStruct> Env::getStruct(spt<Ident> name) {
	auto pt = std::dynamic_pointer_cast<DefStruct>(getDeclaration(name));
	if (!pt) {
		throw JError(name->loc, name->val + " is not a structure");
	}
	return pt;
}
spt<Type> Env::getType(spt<Ident> name) {
	auto pt = std::dynamic_pointer_cast<Type>(getDeclaration(name));
	if (!pt) {
		throw JError(name->loc, name->val + " is not a type");
	}
	return pt;
}
spt<Type> Env::getType(std::string name) {
	return getType(sptOf(new Ident(NO_LOC, name)));
}
spt<Ident> Env::getInitialVar(spt<Ident> name) {
	auto pt = std::dynamic_pointer_cast<Ident>(getDeclaration(name));
	if (!pt) {
		throw JError(name->loc, name->val + " is not a variable");
	}
	return pt;
}
spt<Ident> Env::getOrCreateVar(spt<Ident> name) {
	if (!isNameLocal(name)) {
		declarations[name->val] = name;
	}
	return getInitialVar(name);
}

/*
	Abstract Syntax Tree
*/

Ast::Ast() : env(new Env()) {

	auto typeAny = sptOf(new BaseType("Any", TAny));
	declarations.push_back(typeAny);
	declarations.push_back(sptOf(new BaseType("Nothing", TNothing)));
	declarations.push_back(sptOf(new BaseType("Int64", TInt64)));
	declarations.push_back(sptOf(new BaseType("Bool", TBool)));
	declarations.push_back(sptOf(new BaseType("String", TString)));

	identAny = typeAny->name;
	spt<Ident> mainIdent = sptOf(new Ident(NO_LOC, "@main"));

	mainFunc = spt<DefFunc>(new DefFunc(NO_LOC,
		mainIdent,
		identAny,
		sptOf(new ExprBlock(NO_LOC))
	));
	mainFunc->args.push_back(sptOf(new Argument(NO_LOC,
		sptOf(new Ident(NO_LOC, "nothing")),
		sptOf(new Ident(NO_LOC, "Nothing"))
	)));
	mainFunc->isMain = true;
	declarations.push_back(mainFunc);
}

void Ast::addDeclaration(spt<Declaration> decl) {
	spt<DefFunc> ifFunc = std::dynamic_pointer_cast<DefFunc>(decl);
	spt<DefStruct> ifStruct = std::dynamic_pointer_cast<DefStruct>(decl);
	spt<Expr> ifExpr = std::dynamic_pointer_cast<Expr>(decl);
	if (ifFunc || ifStruct) {
		declarations.push_back(decl);
	}
	else if (ifExpr) {
		mainFunc->body->add(ifExpr);
	}
	else {
		throw ParseError(decl->loc, "Can't cast Declaration [INTERNAL]");
	}
}

/*
	Expressions
*/

void Expr::mergeType(spt<Type> type2) {
	if (type2) {
		if (type && type->name->val != type2->name->val) {
			type = env->getType(identAny);
		}
		else {
			type = type2;
		}
	}
}

BaseType::BaseType(std::string str_name, PrimitiveType type) :
	BaseType(NO_LOC, sptOf(new Ident(NO_LOC, str_name)), type) {};

void ExprBlock::add(spt<Expr> expr) {
	expressions.push_back(expr);
}
void ExprBlock::add(Expr* pt) {
	if (pt) {
		expressions.push_back(sptOf<Expr>(pt));
	}
}
void ExprBlock::add_front(Expr* pt) {
	if (pt) {
		expressions.push_front(sptOf<Expr>(pt));
	}
}

IntConst::IntConst(const YYLTYPE loc, std::string strValue) : Constant(loc) {
	// PJulia assume the value is written in base 10
	if (strValue.size() > 19 ||
		(strValue.size() == 19 && strValue > "9223372036854775808")) {
		throw ParseError(loc,
			"An integer constant must be below 2^63, but " + strValue + "is greater");
	}
	value = std::stoull(strValue);
}

void StrConst::convertSpecialChars() {
	std::string newValue;
	newValue.reserve(value.size());
	bool nextSpecial = false;
	for (char c : value) {
		if (nextSpecial) {
			switch (c) {
			case '\\': newValue.push_back('\\'); break;
			case '"': newValue.push_back('"'); break;
			case 'n': newValue.push_back('\n'); break;
			case 't': newValue.push_back('\t'); break;
			default:
				throw ParseError(loc, "Can't parse special character '\\" + std::string(1, c) + "'");
			}
			nextSpecial = false;
		}
		else {
			if (c == '\\') {
				nextSpecial = true;
			}
			else {
				newValue.push_back(c);
			}
		}
	}
	value = newValue;
}

/*
	Callables
*/

bool typesMatch(spt<Type> type1, spt<Type> type2) {
	if (type1->name->val == "Any" || type2->name->val == "Any") {
		return true;
	}
	return type1->name == type2->name;
}

std::string typeNameOf(spt<Type> tp) { return tp->name->val; }
std::string typeNameOf(spt<Argument> tp) { return tp->typeName->val; }
template<class T>
std::string typesToSig(T args) {
	std::stringstream sig;
	sig << "(";
	for (int iArg = 0; iArg < (int)args.size(); iArg++) {
		if (iArg) sig << ", ";
		sig << "::" << typeNameOf(args[iArg]);
	}
	sig << ")";
	return sig.str();
}
std::string DefFunc::getSignature() {
	return name->val + typesToSig(args);
}
std::string DefStruct::getSignature() {
	return name->val + typesToSig(members);
}

// Call functions

bool DefFunc::matchArgs(std::vector<spt<Type>>& callTypes) {
	if (callTypes.size() != args.size()) return false;
	for (int iArg = 0; iArg < (int)args.size(); iArg++) {
		if (!typesMatch(callTypes[iArg], args[iArg]->argType)) {
			return false;
		}
	}
	return true;
}
void DefFunc::checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) {
	if (!matchArgs(callTypes)) {
		throw JError(atLoc, typesToSig(callTypes) + " doesn't match the function signature " + getSignature());
	}
}

// Build structures


bool DefStruct::matchArgs(std::vector<spt<Type>>& callTypes) {
	if (callTypes.size() != members.size()) return false;
	for (int iArg = 0; iArg < (int)members.size(); iArg++) {
		if (!typesMatch(callTypes[iArg], members[iArg]->argType)) {
			return false;
		}
	}
	return true;
}
void DefStruct::checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) {
	if (!matchArgs(callTypes)) {
		throw JError(atLoc, typesToSig(callTypes) + " doesn't match the structure members " + getSignature());
	}
}

/*
	Show the AST
*/

std::ostream& operator<<(std::ostream& os, const Ast& ast) {
	for (auto decl : ast.declarations) {
		decl->show(os);
		os << "\n\n";
	}
	return os;
}
template<class T>
std::ostream& operator<<(std::ostream& os, const spt<T>& node) {
	if (node) {
		node->show(os);
	}
	else {
		os << "[X]";
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, BinaryOperation op) {
	switch (op) {
	case OpEq: os << "=="; break;
	case OpNotEq: os << "!="; break;
	case OpLower: os << "<"; break;
	case OpLowerEq: os << "<="; break;
	case OpGreater: os << ">"; break;
	case OpGreaterEq: os << ">="; break;
	case OpPlus: os << "+"; break;
	case OpMinus: os << "-"; break;
	case OpTimes: os << "*"; break;
	case OpMod: os << "%"; break;
	case OpPower: os << "^"; break;
	case OpAnd: os << "&&"; break;
	case OpOr: os << "||"; break;
	default: break;
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, PrimitiveType type) {
	if (type == TAny) os << "Any";
	if (type == TNothing) os << "Nothing";
	if (type == TBool) os << "Bool";
	if (type == TInt64) os << "Int64";
	if (type == TString) os << "String";
	return os;
}

std::ostream& operator<<(std::ostream& os, UnaryOperation op) {
	switch (op) {
	case UnaryNot: os << "!"; break;
	case UnaryMinus: os << "-"; break;
	default: break;
	}
	return os;
}



void ExprBlock::show(std::ostream& os) const {
	os << "([";
	for (auto exp : expressions) {
		exp->show(os);
		os << " ;\n";
	}
	os << "])";
	// os << ":>" << type;
}
void BaseType::show(std::ostream& os) const {
	os << type;
}
void Ident::show(std::ostream& os) const {
	os << val;
	os << ":>" << type;
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void IntConst::show(std::ostream& os) const {
	os << value;
	os << ":>" << type;
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void Assignment::show(std::ostream& os) const {
	os << "(" << lvalue << " = " << rvalue << ")";
	os << ":>" << type;
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void StrConst::show(std::ostream& os) const {
	os << '"' << value << '"';
	os << ":>" << type;
}
void BoolConst::show(std::ostream& os) const {
	os << (value ? std::string("true") : std::string("false"));
	os << ":>" << type;
}
void BinOp::show(std::ostream& os) const {
	os << "(" << left << ' ' << op << ' ' << right << ")";
	os << ":>" << type;
}
void UnaryOp::show(std::ostream& os) const {
	os << "(" << op << " " << expr << ")";
	os << ":>" << type;
}
void DotOp::show(std::ostream& os) const {
	os << "(" << object << "." << member << ")";
	os << ":>" << type;
}


void CallParamList::show(std::ostream& os) const {
	bool prev = false;
	for (auto exp : expressions) {
		if (prev) os << ", ";
		prev = true;
		exp->show(os);
	}
	// os << ":>" << type;
}
void CallFunction::show(std::ostream& os) const {
	os << funcName->val << "(" << args << ")";
	os << ":>" << type;
}
void ReturnVal::show(std::ostream& os) const {
	if (value) {
		os << "return " << value;
	}
	else {
		os << "return [Nothing]";
	}
	os << ":>" << type;
}
void FlowFor::show(std::ostream& os) const {
	os << "for " << counter << " = " << startAt << " : " << endAt << "\n";
	os << body << "\nend\n";
	os << ":>" << type;
}
void FlowWhile::show(std::ostream& os) const {
	os << "while " << condition << "\n";
	os << body << "\nend\n";
	os << ":>" << type;
}
void FlowIfElse::show(std::ostream& os) const {
	os << "if " << condition << "\n";
	os << ifTrue << "\nelse\n" << ifFalse << "\nend\n";
	os << ":>" << type;
}


void Argument::show(std::ostream& os) const {
	os << name->val << " :: " << name->type->name->val;
}
void DefStruct::show(std::ostream& os) const {
	if (isMutable) os << "mutable ";
	os << "struct " << name << "\n";
	for (auto m : members) os << m << "\n";
	os << "end\n";
}
void DefFunc::show(std::ostream& os) const {
	os << "function " << name << "(";
	for (auto arg : args) os << arg << ", ";
	os << ") :: " << returnType << "\n";
	os << body << "\nend\n";
}
