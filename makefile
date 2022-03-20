game: game.out
	./game.out
	
game2: game2.out
	./game2.out

game.out: parser.tab.cc lex.yy.cc
	g++ -o game.out -w -g parser.tab.cc lex.yy.cc helper_functions.cpp helper_functions.h
	
game2.out: parser.tab.cc lex.yy.cc
	g++ -o game.out -w -g parser.tab.cc lex.yy.cc helper2.cpp helper_functions.h

lex.yy.cc: lexer.l
	flex -w -o lex.yy.cc lexer.l

parser.tab.cc: parser.y
	bison -d --warnings=none parser.y -o parser.tab.cc

clean:
	rm -f parser.tab.cc parser.tab.hh lex.yy.cc game.out
