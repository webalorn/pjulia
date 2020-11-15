CXX=g++ -std=c++14
CPPFLAGS=-g -O2 -Wall -Wextra -Wno-deprecated-register
LDFLAGS=
SRC_DIR=src
SRCS=$(shell find src -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

# TODO : real makefile

all: pjulia

fbison:
	bison -o src/parser.tab.cpp -d src/parser.ypp
	flex -o src/lex.yy.cpp src/lexer.lpp

pjulia: $(OBJS)
	$(CXX) $(LDFLAGS) -o pjulia $(OBJS)

clean:
	rm $(OBJS) pjulia src/lex.yy.cpp src/parser.tab.cpp src/parser.tab.hpp
