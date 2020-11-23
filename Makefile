CXX=g++ -std=c++14
CPPFLAGS=-g -O2 -Wall -Wextra -Wno-deprecated-register
LDFLAGS=
SRC_DIR=src
SRCS=$(shell find src -type f -name '*.cpp')
OBJS=$(subst .cpp,.o,$(SRCS))

all: pjulia

src/parser.tab.cpp: src/parser.ypp # Bison parser
	bison -o src/parser.tab.cpp -d src/parser.ypp

src/lex.yy.cpp: src/lexer.lpp # Flex lexer
	flex -o src/lex.yy.cpp src/lexer.lpp

fbison: src/parser.tab.cpp src/lex.yy.cpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

pjulia: $(OBJS)
	$(CXX) $(LDFLAGS) -o pjulia $(OBJS)

clean:
	rm $(OBJS) pjulia src/lex.yy.cpp src/parser.tab.cpp src/parser.tab.hpp
