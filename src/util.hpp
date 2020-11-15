#if !defined(UTIL_HPP)
#define UTIL_HPP

#include <string>
#include <exception>
#include <map>
#include <vector>
#include <memory>
#include "parser.tab.hpp"

/*
	Exceptions
*/

class PJuliaError : public std::exception {
public:
	std::string ctxFileName;
public:
	const char* what() const throw();
	virtual std::string get() const = 0;
	virtual std::string bashFormat() const;
	void giveContext(std::string);
};

class UsageError : public PJuliaError {
protected:
	std::string str;
public:
	UsageError(const std::string str);
	std::string get() const;
};

class LocalizedError : public PJuliaError {
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

/*
	Argument parsing
*/

class Argument {
protected:
	std::string value, name;
	bool optional;
	friend class ArgParser;
public:
	Argument(const std::string name, const bool optional);
	std::string get();
};

using BoolPt = std::shared_ptr<bool>;
using ArgPt = std::shared_ptr<Argument>;

class ArgParser {
	std::map<std::string, std::shared_ptr<bool>> flags;
	std::vector<std::shared_ptr<Argument>> posiArgs;

public:
	std::shared_ptr<bool> addFlag(std::string name);
	std::shared_ptr<Argument> newPositional(std::string name, bool optional = false);
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
