#if !defined(ASM_HPP)
#define ASM_HPP

#include "../util.hpp"
#include <vector>
#include <set>

class AsmProg;

enum RegName {
	rax,
	rbx,
	rcx,
	rdx,
	rsi,
	rdi,
	rbp,
	rsp,
	r8,
	r9,
	r10,
	r11,
	r12,
	r12b,
	r13,
	r14,
	r15,
};
enum AsmInsName {
	asmMov,
	asmPushq,
	asmPopq,
	asmLoadAddr,
	asmAdd,
	asmSub,
	asmBitNot,
	asmBitAnd,
	asmBitOr,
	asmBitXor,
	asmNop,
	asmCall,
	asmRet,
	asmCmp,
	asmTest,
	asmJumpIf,
	asmSet,
	asmMult,
	asmJump,
	asmCqto,
	asmIdivq,
	asmNeg,
	asmInc,
};

struct AsmArg {
	virtual void emit(std::ostream& os) = 0;
	inline virtual ~AsmArg() {};
};

struct AsmInt : AsmArg {
	long long value;
	inline AsmInt(long long value) : value(value) {}
	void emit(std::ostream& os);
};
struct AsmLabelRef : AsmArg {
	std::string label;
	inline AsmLabelRef(std::string label) : label(label) {}
	void emit(std::ostream& os);
};
struct AsmFlag : AsmArg {
	std::string flag;
	inline AsmFlag(std::string flag) : flag(flag) {}
	void emit(std::ostream& os);
};

struct AsmLoc : AsmArg {
	using AsmArg::AsmArg;
	virtual spt<AsmLoc> withOffset(int offset) = 0;
};

struct AsmOffset : AsmLoc {
	int qOffset; // should be * 8 (64 bits)
	RegName reg;
	inline AsmOffset(int qOffset, RegName reg = rbp) : AsmLoc(), qOffset(qOffset), reg(reg) {}
	virtual void emit(std::ostream& os);
	virtual spt<AsmLoc> withOffset(int offset);
};
struct AsmRegArg : AsmLoc {
	RegName reg;
	inline AsmRegArg(RegName reg = rbp) : AsmLoc(), reg(reg) {}
	virtual void emit(std::ostream& os);
	virtual spt<AsmLoc> withOffset(int offset);
};
struct AsmGlobalVar : AsmLoc {
	std::string varName;
	bool isTypeVar;
	inline AsmGlobalVar(std::string varName, bool isTypeVar = false)
		: AsmLoc(), varName(varName), isTypeVar(isTypeVar) {}
	virtual void emit(std::ostream& os);
	virtual spt<AsmLoc> withOffset(int offset);
	std::string getLabel();
};

inline spt<AsmRegArg> regArg(RegName reg) {
	return sptOf(new AsmRegArg(reg));
}
inline spt<AsmInt> intArg(long long val) {
	return sptOf(new AsmInt(val));
}
inline spt<AsmLabelRef> labelArg(std::string val) {
	return sptOf(new AsmLabelRef(val));
}
inline spt<AsmFlag> flagArg(std::string val) {
	return sptOf(new AsmFlag(val));
}


struct AsmIns {
	std::string labelName;
	bool hasLabel;
	AsmInsName ins;
	std::vector<spt<AsmArg>> args;

	AsmIns(AsmInsName ins, std::vector<spt<AsmArg>> args, std::string setLabel = "");
	void emit(std::ostream& os);
	std::string getLabel(spt<AsmProg> prog);

	static int nbArgs(AsmInsName insName);
	static std::string codeOf(AsmInsName insName);
};

class AsmFunc {
protected:
	std::vector<spt<AsmIns>> instructions;
	std::string name;
public:
	int rbpOffset, argOffset;
	std::vector<spt<AsmLoc>> localVars;
	bool isMain, needReturnType;
	spt<AsmIns> footerOp;

	AsmFunc(std::string name, bool isMain);
	virtual void emit(std::ostream& os);
	spt<AsmIns> add(AsmInsName insName, std::vector<spt<AsmArg>> args);
	spt<AsmIns> add(spt<AsmIns> ins);
	void alignStack(spt<AsmProg> prog);
	void abort(spt<AsmProg> prog, std::string message = "", std::vector<spt<AsmArg>> args = {});
	inline virtual ~AsmFunc() {};
};

class AsmPrimitiveCode : public AsmFunc {
public:
	AsmPrimitiveCode();
	virtual void emit(std::ostream& os);
};

class AsmProg {
protected:
	std::vector<spt<AsmFunc>> functions;
	std::set<std::string> usedLabels;
public:
	std::map<std::string, std::string> stringConsts, stringToLabel;
	std::vector<spt<AsmGlobalVar>> globalVars;

	friend std::ostream& operator<<(std::ostream& os, const AsmProg& prog);
	void add(spt<AsmFunc> func);
	std::string addString(std::string label, std::string content);
	std::string store(std::string content);
	spt<AsmLabelRef> storeArg(std::string content);
	void storeVar(spt<AsmGlobalVar> var);
	std::string randomLabel();
};
std::ostream& operator<<(std::ostream& os, const AsmProg& prog);
std::ostream& operator<<(std::ostream& os, const spt<AsmProg>& prog);



#endif // ASM_HPP
