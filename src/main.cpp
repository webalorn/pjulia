#include <iostream>
#include "parser.tab.hpp"
#include "util.hpp"

extern FILE* yyin;
extern int yyparse(void);
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
		yyparse();
	}
	catch (PJuliaError& e) {
		e.giveContext(filename);
		std::cerr << "\n" << e.bashFormat() << e.get() << "\e[39m";
		return -1;
	}
}
