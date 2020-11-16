#include "ast.hpp"

Ast::Ast() {}

void ExprBlock::add(spt<Expr> expr) {
	expressions.push_back(expr);
}
void ExprBlock::add(AstNode* pt) {
	if (pt) {
		expressions.push_back(sptOf<Expr>(pt));
	}
}
void ExprBlock::add_front(AstNode* pt) {
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
	node->show(os);
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

std::ostream& operator<<(std::ostream& os, UnaryOperation op) {
	switch (op) {
	case UnaryNot: os << "!"; break;
	case UnaryMinus: os << "-"; break;
	default: break;
	}
	return os;
}



void ExprBlock::show(std::ostream& os) const {
	os << "([ ";
	for (auto exp : expressions) {
		exp->show(os);
		os << " ; ";
	}
	os << " ])";
}
void Ident::show(std::ostream& os) const {
	os << val;
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void IntConst::show(std::ostream& os) const {
	os << value;
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void Assignment::show(std::ostream& os) const {
	os << "(" << lvalue << " = " << rvalue << ")";
	// os << "{" << loc.first_column << "-" << loc.last_column << "|" << loc.first_line << "}";
}
void StrConst::show(std::ostream& os) const {
	os << '"' << value << '"';
}
void BoolConst::show(std::ostream& os) const {
	os << (value ? std::string("true") : std::string("false"));
}
void BinOp::show(std::ostream& os) const {
	os << "(" << left << ' ' << op << ' ' << right << ")";
}
void UnaryOp::show(std::ostream& os) const {
	os << "(" << op << " " << expr << ")";
}
void DotOp::show(std::ostream& os) const {
	os << "(" << object << "." << member << ")";
}


void CallParamList::show(std::ostream& os) const {
	bool prev = false;
	for (auto exp : expressions) {
		if (prev) os << ", ";
		prev = true;
		exp->show(os);
	}
}
void CallFunction::show(std::ostream& os) const {
	os << func << "(" << args << ")";
}
void ReturnVal::show(std::ostream& os) const {
	if (value) {
		os << "return " << value;
	}
	else {
		os << "return [Nothing]";
	}
}
void FlowFor::show(std::ostream& os) const {
	os << "for " << counter << " = " << startAt << " : " << endAt << "\n";
	os << body << "\nend\n";
}
void FlowWhile::show(std::ostream& os) const {
	os << "while " << condition << "\n";
	os << body << "\nend\n";
}
void FlowIfElse::show(std::ostream& os) const {
	os << "if " << condition << "\n";
	os << ifTrue << "\nelse\n" << ifFalse << "\nend\n";
}


void Argument::show(std::ostream& os) const {
	os << name << " :: " << type;
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
	os << ") :: " << type << "\n";
	os << body << "\nend\n";
}
