CC = g++
CFLAGS = -std=c++17 -Wall

all: parser_bison

parser_bison: parser_bison.tab.c lexer.o main.o lex_support.o
	$(CC) $(CFLAGS) -o parser_bison parser_bison.tab.c lexer.o main.o lex_support.o

parser_bison.tab.c parser_bison.tab.h: parser_bison.y
	bison -d parser_bison.y

lexer.o: lexer.cpp lexer.hpp parser_bison.tab.h lex_support.h
	$(CC) $(CFLAGS) -c lexer.cpp

lex_support.o: lex_support.cpp lex_support.h
	$(CC) $(CFLAGS) -c lex_support.cpp

main.o: main.cpp lexer.hpp parser_bison.tab.h lex_support.h
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f parser_bison *.o parser_bison.tab.c parser_bison.tab.h