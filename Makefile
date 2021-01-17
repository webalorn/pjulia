UNAME=$(shell uname)
CXX=g++ -std=c++14
CPPFLAGS=-O2 -Wall -Wextra
LDFLAGS=
SRC_DIR=src
SRCS=$(shell find src -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

ifeq ($(UNAME),Darwin)
	CXX=clang++ -std=c++14
	CPPFLAGS += -Wno-deprecated-register
endif

all: pjuliac

src/parser.tab.cpp: src/parser.ypp # Bison parser
	bison -o src/parser.tab.cpp -d src/parser.ypp

src/lex.yy.cpp: src/lexer.lpp # Flex lexer
	flex -o src/lex.yy.cpp src/lexer.lpp

fbison: src/parser.tab.cpp src/lex.yy.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

pjuliac: $(OBJS)
	$(CXX) $(LDFLAGS) -o pjuliac $(OBJS)

clean:
	rm $(OBJS) pjuliac src/lex.yy.cpp src/parser.tab.cpp src/parser.tab.hpp
