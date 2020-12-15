#include <iostream>
#include <fstream>
#include "parser.tab.hpp"
#include "util.hpp"
#include "comp/ast.hpp"
#include "asm/asm.hpp"

extern FILE* yyin;
extern int yyparse(Ast*);
extern int yydebug;

std::string getAsmFilename(std::string filename) {
	int n = filename.size();
	if (n >= 3 && filename.substr(n - 3, 3) == ".jl") {
		return filename.substr(0, n - 3) + ".s";
	}
	return filename + ".s";
}

int main(int argc, char** argv) {
	// yydebug = 1;
	std::string filename;
	try {
		ArgParser parser;
		BoolPt fParseOnly = parser.addFlag("--parse-only");
		BoolPt fTypeOnly = parser.addFlag("--type-only");
		ArgPt filenamePt = parser.newPositional("Julia file name");
		parser.parse(argc, argv);

		filename = filenamePt->get();
		FileObj file(filename);
		yyin = file.c_file();
		Ast ast;

		/* Parse the code */
		int parseCode = yyparse(&ast);
		if (parseCode == 2) {
			throw PJuliaError("Parsing failed due to memory exhaustion");
		}
		else if (parseCode) {
			throw PJuliaError("Parsing failed");
		}
		else if (*fParseOnly) {
			return 0;
		}

		/* Set types */
		// strictTypeMode = !(*fTypeOnly);
		strictTypeMode = false;
		ast.initEnvTypes();

		if (*fTypeOnly) {
			return 0;
		}
		std::cout << ast;
		spt<AsmProg> prog(new AsmProg);
		ast.emitAsm(prog);
		std::cout << prog;

		std::ofstream asmFile(getAsmFilename(filename));
		asmFile << prog;
	}
	catch (PJuliaBaseError& e) {
		e.giveContext(filename);
		std::cerr << "\n" << e.bashFormat() << e.get() << "\e[0m";
		return e.errorCode();
	}
}
