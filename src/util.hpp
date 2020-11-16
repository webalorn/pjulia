#if !defined(UTIL_HPP)
#define UTIL_HPP

#include <string>
#include <exception>
#include <map>
#include <vector>
#include <memory>
#include "parser.tab.hpp"

/*
	Locations
*/

// Split loc on first line
YYLTYPE locLeft(YYLTYPE loc, int splitAt);
YYLTYPE locRight(YYLTYPE loc, int splitAt);

/*
	Exceptions
*/

class PJuliaBaseError : public std::exception {
public:
	std::string ctxFileName;
public:
	const char* what() const throw();
	virtual std::string get() const = 0;
	virtual std::string bashFormat() const;
	void giveContext(std::string);
};

class PJuliaError : public PJuliaBaseError {
protected:
	std::string str;
public:
	PJuliaError(const std::string str);
	std::string get() const;
};

class UsageError : public PJuliaBaseError {
protected:
	std::string str;
public:
	UsageError(const std::string str);
	std::string get() const;
};

class LocalizedError : public PJuliaBaseError {
protected:
	YYLTYPE loc;
	virtual std::string errorBody() const = 0;
public:
	std::string get() const;
	LocalizedError(const YYLTYPE loc);
};

class SyntaxError : public LocalizedError {
protected:
	std::string str;
public:
	std::string errorBody() const;
	SyntaxError(const YYLTYPE loc, const std::string str);
};

class ParseError : public LocalizedError {
protected:
	std::string str;
public:
	std::string errorBody() const;
	ParseError(const YYLTYPE loc, const std::string str);
};

/*
	Argument parsing
*/

class CmdArgument {
protected:
	std::string value, name;
	bool optional;
	friend class ArgParser;
public:
	CmdArgument(const std::string name, const bool optional);
	std::string get();
};

using BoolPt = std::shared_ptr<bool>;
using ArgPt = std::shared_ptr<CmdArgument>;

class ArgParser {
	std::map<std::string, std::shared_ptr<bool>> flags;
	std::vector<std::shared_ptr<CmdArgument>> posiArgs;

public:
	std::shared_ptr<bool> addFlag(std::string name);
	std::shared_ptr<CmdArgument> newPositional(std::string name, bool optional = false);
	void parse(int argc, char** argv);
};

/*
	Files
*/

class FileObj {
protected:
	FILE* filePt;
public:
	FileObj(const std::string name, const std::string mode = "r");
	~FileObj();
	FILE* c_file();
};

#endif // UTIL_HPP
