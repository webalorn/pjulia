#include "util.hpp"

bool strictTypeMode = true;
bool targetMacos = false;

/*
	Locations
*/

// Split loc on first line
YYLTYPE locLeft(YYLTYPE loc, int splitAt) {
	loc.last_column = loc.first_column + splitAt - 1;
	return loc;
}
YYLTYPE locRight(YYLTYPE loc, int splitAt) {
	loc.first_column += splitAt;
	return loc;
}

std::string locToString(const YYLTYPE& loc) {
	std::string strLoc = "";
	if (loc.first_line != loc.last_line) {
		strLoc = "lines " + std::to_string(loc.first_line) + "-"
			+ std::to_string(loc.last_line);
	}
	else {
		strLoc = "line " + std::to_string(loc.first_line) + ", ";
		if (loc.first_column != loc.last_column) {
			strLoc += "characters " + std::to_string(loc.first_column) + "-"
				+ std::to_string(loc.last_column);
		}
		else {
			strLoc += "character " + std::to_string(loc.first_column);
		}
	}
	return strLoc;
}

/*
	Exceptions
*/

const char* PJuliaBaseError::what() const throw() {
	return get().c_str();
}
std::string PJuliaBaseError::bashFormat() const {
	return "\e[31m";
}
void PJuliaBaseError::giveContext(std::string fname) {
	ctxFileName = fname;
}
int PJuliaBaseError::errorCode() {
	return 1;
};


PJuliaError::PJuliaError(const std::string str) : str(str) {};
std::string PJuliaError::get() const {
	return "Error: " + str + "\n";
}
int PJuliaError::errorCode() {
	return 2;
};

UsageError::UsageError(const std::string str) : str(str) {};
std::string UsageError::get() const {
	return "Usage error: " + str + "\n";
}
int UsageError::errorCode() {
	return 2;
};

std::string LocalizedError::get() const {
	return "File \"" + ctxFileName + "\", " + locToString(loc) + ":\n" + errorBody();
}

LocalizedError::LocalizedError(const YYLTYPE loc) : loc(loc) {}


SyntaxError::SyntaxError(const YYLTYPE loc, const std::string str) : LocalizedError(loc), str(str) {};
std::string SyntaxError::errorBody() const {
	return "Syntax error: unexpected string near \"" + str + "\"\n";
}

ParseError::ParseError(const YYLTYPE loc, const std::string str) : LocalizedError(loc), str(str) {};
std::string ParseError::errorBody() const {
	return "Parse error: " + str + "\n";
}

JError::JError(const YYLTYPE loc, const std::string str) : LocalizedError(loc), str(str) {};
std::string JError::errorBody() const {
	return "Error: " + str + "\n";
}

/*
	Argument parsing
*/

CmdArgument::CmdArgument(const std::string name, const bool optional) : name(name), optional(optional) {}
std::string CmdArgument::get() {
	return value;
}

std::shared_ptr<bool> ArgParser::addFlag(std::string name) {
	if (flags.find(name) == flags.end()) {
		flags[name] = std::shared_ptr<bool>(new bool);
		*flags[name] = false;
	}
	return flags[name];
}
std::shared_ptr<CmdArgument> ArgParser::newPositional(std::string name, bool optional) {
	std::shared_ptr<CmdArgument> arg(new CmdArgument(name, optional));
	posiArgs.push_back(arg);
	return arg;
}

void ArgParser::parse(int argc, char** argv) {
	int iPositional = 0;
	for (int iArg = 1; iArg < argc; iArg++) {
		std::string val = argv[iArg];
		if (flags.count(val)) {
			*flags[val] = true;
		}
		else if (val.size() && val[0] == '-') {
			throw UsageError("The flag " + val + " doesn't exists");
		}
		else {
			if (iPositional < (int)posiArgs.size()) {
				posiArgs[iPositional++]->value = val;
			}
			else {
				throw UsageError("Too many positional arguments");
			}
		}
	}
	for (; iPositional < (int)posiArgs.size(); iPositional++) {
		if (!posiArgs[iPositional]->optional) {
			throw UsageError("The positional argument " + posiArgs[iPositional]->name +
				" (" + std::to_string(iPositional + 1) + ") is required but is not given");
		}
	}
}

/*
	Files
*/


FileObj::FileObj(const std::string name, const std::string mode) {
	filePt = fopen(name.c_str(), mode.c_str());
	if (!filePt) {
		throw UsageError("Can't open the file " + name);
	}
}
FileObj::~FileObj() {
	if (filePt) {
		fclose(filePt);
	}
}
FILE* FileObj::c_file() {
	return filePt;
}
