#include "ast.hpp"
#include "builtins.hpp"

/*
	Environment
*/
spt<Ident> identAny;

Env::Env(spt<Env> fromVal, bool softScope) : from(fromVal), lastTypeId(0), softScope(softScope) {
	if (from) {
		inFunction = from->inFunction;
	}
}

spt<Env> Env::child(bool soft) {
	return sptOf(new Env(shared_from_this(), soft));
}

bool Env::isNameDefined(spt<Ident> name) {
	return declarations.count(name->val)
		|| (from && from->isNameDefined(name));
}
bool Env::isNameLocal(spt<Ident> name, bool forceLocal) {
	return declarations.count(name->val) || (!forceLocal && softScope && from->isNameLocal(name));
}
void Env::add(spt<Ident> name, spt<Declaration> decl) {
	if (isNameLocal(name)) {
		throw JError(name->loc, "The identifier " + name->val + " is already defined");
	}
	auto strPtr = std::dynamic_pointer_cast<DefStruct>(decl);
	if (strPtr) {
		for (auto m : strPtr->members) {
			std::string name = m->name->val;
			if (memberToStruct.count(name)) {
				throw JError(m->loc, "The field name " + name + " is already used in this file");
			}
			memberToStruct[name] = strPtr;
		}
	}

	declarations[name->val] = decl;
}
spt<DefStruct> Env::structWith(spt<Ident> name) {
	if (!from) {
		if (memberToStruct.count(name->val)) {
			return memberToStruct[name->val];
		}
		throw JError(name->loc, "No structure with a member " + name->val);
	}
	return from->structWith(name);
}
void Env::declFunction(spt<Ident> name, spt<DefFunc> decl) {
	if (isNameLocal(name)) {
		auto prevDecl = getDeclaration(name);
		auto funcPt = std::dynamic_pointer_cast<DefFunc>(prevDecl);
		auto dispatchPt = std::dynamic_pointer_cast<FuncDispacher>(prevDecl);
		if (funcPt) {
			dispatchPt = sptOf(new FuncDispacher());
			dispatchPt->functions.push_back(funcPt);
			dispatchPt->env = shared_from_this();
			declarations[name->val] = dispatchPt;
		}
		if (dispatchPt) {
			dispatchPt->functions.push_back(decl);
		}
		else {
			throw JError(name->loc, "The identifier " + name->val + " is already defined and can't be used for a new function");
		}
	}
	else {
		add(name, decl);
	}
}
spt<Declaration> Env::getDeclaration(spt<Ident> name, bool forceLocal) {
	if (!isNameLocal(name, forceLocal)) {
		if (from) {
			return from->getDeclaration(name);
		}
		throw JError(name->loc, "The identifier " + name->val + " is not defined");
	}
	if (declarations.count(name->val)) {
		return declarations[name->val];
	}
	return from->getDeclaration(name); // in case of softScope
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
spt<Ident> Env::getInitialVar(spt<Ident> name, bool forceLocal) {
	auto pt = std::dynamic_pointer_cast<Ident>(getDeclaration(name, forceLocal));
	if (!pt) {
		throw JError(name->loc, name->val + " is not a variable");
	}
	return pt;
}
spt<Ident> Env::getOrCreateVar(spt<Ident> name, bool force, bool forceLocal) {
	if (!isNameLocal(name, forceLocal)) {
		declarations[name->val] = name;
	}
	else if (force) {
		throw JError(name->loc, "Duplicate identifier: " + name->val);
	}
	return getInitialVar(name);
}

/*
	Abstract Syntax Tree
*/

Ast::Ast() : env(new Env()) {

	declarations.push_back(sptOf(new BaseType("Nothing", TNothing)));
	auto typeAny = sptOf(new BaseType("Any", TAny));
	declarations.push_back(typeAny);
	declarations.push_back(sptOf(new BaseType("Int64", TInt64)));
	declarations.push_back(sptOf(new BaseType("Bool", TBool)));
	declarations.push_back(sptOf(new BaseType("String", TString)));

	declarations.push_back(sptOf(new BuiltinPrint()));
	declarations.push_back(sptOf(new BuiltinPrintLn()));
	declarations.push_back(sptOf(new BuiltinDiv()));

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
	mainFunc->args[0]->name->isMutable = false;
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
		// Can't happen unless I make important incompatible changes and forgot to change this function
		throw ParseError(decl->loc, "Can't cast Declaration [INTERNAL]");
	}
}

/*
	Expressions
*/
bool Type::isKnown() {
	return name->val != "Any";
}

spt<Type> mergeTypes(spt<Type> type1, spt<Type> type2, spt<Env> env) {
	if (type2) {
		if (type1 && type1->name->val != type2->name->val) {
			return env->getType("Any");
		}
		return type2;
	}
	return type1;
}

void Expr::mergeType(spt<Type> type2) {
	type = mergeTypes(type, type2, env);
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

std::string DefFunc::getSignature() {
	return name->val + typesToSig(args);
}
std::string DefStruct::getSignature() {
	return name->val + typesToSig(members);
}

void Callable::asmCheckArgType(spt<AsmProg> prog, spt<AsmFunc> func, spt<Expr> arg, spt<Type> mType) {
	if (mType->isKnown() && !arg->getType()->isKnown()) {
		// Value must be the current value
		auto labelIsOk = sptOf(new AsmIns(asmNop, {}));
		func->add(asmCmp, { intArg(mType->typeId), regArg(rbx) });
		func->add(asmJumpIf, { flagArg("e"), labelArg(labelIsOk->getLabel(prog)) });
		func->abort(prog, "Wrong argument type, line %d, characters %d-%d",
			{ intArg(arg->loc.first_line),
				intArg(arg->loc.first_column),
				intArg(arg->loc.last_column) });
		func->add(labelIsOk);
	}
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

// Dispacher

spt<Type> FuncDispacher::getReturnType() {
	if (!returnType) {
		returnType = functions[0]->getReturnType();
		for (auto& f : functions) {
			returnType = mergeTypes(returnType, f->getReturnType(), env);
		}
	}
	return returnType;
}
bool FuncDispacher::matchArgs(std::vector<spt<Type>>& callTypes) {
	for (auto& f : functions) {
		if (f->matchArgs(callTypes)) {
			return true;
		}
	}
	return false;
}
void FuncDispacher::checkCallArgs(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) {
	if (!matchArgs(callTypes)) {
		throw JError(atLoc, functions[0]->name->val + typesToSig(callTypes) + " doesn't match any overload of \"" + functions[0]->name->val + "\" function");
	}
}

void FuncDispacher::checkAmbiguous() {
	for (int i = 0; i < (int)functions.size(); i++) {
		for (int j = i + 1; j < (int)functions.size(); j++) {
			bool isAmbiguous = true;
			if (functions[i]->args.size() != functions[j]->args.size()) {
				continue;
			}
			for (int iArg = 0; iArg < (int)functions[i]->args.size(); iArg++) {
				if (functions[i]->args[iArg]->argType->name !=
					functions[j]->args[iArg]->argType->name) {
					isAmbiguous = false;
					break;
				}
			}
			if (isAmbiguous) {
				throw JError(functions[j]->loc, "Definition of " + functions[j]->getSignature() + " has the same signature as a previous declaration (" + functions[i]->getSignature() + ")");
			}
		}
	}
}

spt<Callable> FuncDispacher::tryPreDispatch(YYLTYPE atLoc, std::vector<spt<Type>>& callTypes) {
	std::vector<spt<DefFunc>> funcMatch;
	for (auto& f : functions) {
		if (f->matchArgs(callTypes)) {
			funcMatch.push_back(f);
		}
	}
	for (int iArg = 0; iArg < (int)callTypes.size(); iArg++) {
		if (callTypes[iArg]->name->val == "Any") {
			return shared_as<FuncDispacher>();
		}
	}

	bool isAmbiguous = false;
	int bestScore = -1;
	spt<DefFunc> match;

	for (auto& f : functions) {
		if (f->matchArgs(callTypes)) {
			int score = 0;
			for (int iArg = 0; iArg < (int)callTypes.size(); iArg++) {
				if (callTypes[iArg]->name->val != "Any"
					&& callTypes[iArg]->name->val == f->args[iArg]->typeName->val) {
					score += 1;
				}
			}
			if (score > bestScore) {
				bestScore = score;
				isAmbiguous = false;
				match = f;
			}
			else if (score == bestScore) {
				isAmbiguous = true;
			}
		}
	}
	if (isAmbiguous) {
		throw JError(atLoc, "Call to " + match->name->val + typesToSig(callTypes) + " is ambiguous");
	}
	return match;
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

void showType(std::ostream& os, spt<Type> type) {
	if (type) {
		os << ":>" << type->name->val;
	}
	else {
		os << ":>[X]";
	}
}



void ExprBlock::show(std::ostream& os) const {
	os << "([";
	for (auto exp : expressions) {
		exp->show(os);
		os << " ;\n";
	}
	os << "])";
	// showType(os, type);
}
void BaseType::show(std::ostream& os) const {
	os << type;
}
void Ident::show(std::ostream& os) const {
	os << val;
	showType(os, type);
}
void IntConst::show(std::ostream& os) const {
	os << value;
	showType(os, type);
}
void Assignment::show(std::ostream& os) const {
	os << "(" << lvalue << " = " << rvalue << ")";
	showType(os, type);
}
void StrConst::show(std::ostream& os) const {
	os << '"' << value << '"';
	showType(os, type);
}
void BoolConst::show(std::ostream& os) const {
	os << (value ? std::string("true") : std::string("false"));
	showType(os, type);
}
void BinOp::show(std::ostream& os) const {
	os << "(" << left << ' ' << op << ' ' << right << ")";
	showType(os, type);
}
void UnaryOp::show(std::ostream& os) const {
	os << "(" << op << " " << expr << ")";
	showType(os, type);
}
void DotOp::show(std::ostream& os) const {
	os << "(" << object << "." << member << ")";
	showType(os, type);
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
	os << funcName->val << "(" << args << ")";
	showType(os, type);
}
void ReturnVal::show(std::ostream& os) const {
	if (value) {
		os << "return " << value;
	}
	else {
		os << "return [Nothing]";
	}
	showType(os, type);
}
void FlowFor::show(std::ostream& os) const {
	os << "for " << counter << " = " << startAt << " : " << endAt << "\n";
	os << body << "\nend\n";
	showType(os, type);
}
void FlowWhile::show(std::ostream& os) const {
	os << "while " << condition << "\n";
	os << body << "\nend\n";
	showType(os, type);
}
void FlowIfElse::show(std::ostream& os) const {
	os << "if " << condition << "\n";
	os << ifTrue << "\nelse\n" << ifFalse << "\nend\n";
	showType(os, type);
}


void Argument::show(std::ostream& os) const {
	os << name->val << " :: " << name->getType()->name->val;
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
void FuncDispacher::show(std::ostream& os) const {
	for (auto& f : functions) {
		os << f;
	}
}
