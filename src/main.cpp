#include <iostream>
#include "parser.tab.hpp"
#include "util.hpp"
#include "comp/ast.hpp"

extern FILE* yyin;
extern int yyparse(Ast*);
extern int yydebug;

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
		ast.initEnvTypes();
		// std::cout << ast;
	}
	catch (PJuliaBaseError& e) {
		e.giveContext(filename);
		std::cerr << "\n" << e.bashFormat() << e.get() << "\e[0m";
		return 1;
	}
}
