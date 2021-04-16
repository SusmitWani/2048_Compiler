%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <bits/stdc++.h>
  #include "helper_functions.h"
  using namespace std;
  #define YYERROR_VERBOSE
  #define YYTYPE int
  int yyerror (char const *s);
  int yylex();
  /* int yyparse(void); */

void move(int g[], map <char*, pair<int,int>> &m, int op, int dir);
int return_value(int g[], int x, int y);
void assign_val(int g[], map <char*, pair<int,int>> &m, int val, int x, int y);
void assign_var(int g[], map <char*, pair<int,int>> &m, char* identifier, int x, int y);
void makezero(int g[]);
int printError (int g[], map <char*, pair<int,int>> & m);
int g[16] = {};
map <char*, pair<int, int>> m;
%}

%union {int val; char id; char* str;}
%start program

/*Operation*/
%token <val> ADD
%token <val> SUBTRACT
%token <val> MULTIPLY
%token <val> DIVIDE

/*Direction*/
%token <val> UP
%token <val> DOWN
%token <val> LEFT
%token <val> RIGHT

/*Keywords*/
%token EXIT
%token ASSIGN
%token TO
%token VAR
%token IS
%token VALUE
%token IN
%token EOL

%token GG

%token COMMA
/* %token number */
%token <str> identifier
%token <val> number
%type <val> operation direction
%type <val> num
%%
/* descriptions of expected inputs     corresponding actions (in C) */

program     : line program | line | GG {printf("\n");exit(EXIT_SUCCESS);};

line        : operation EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing Direction\n");reset();printf("---->");}
            | direction EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing Operation\n");reset();printf("---->");}
            | operation direction {std::cerr << "-1" << '\n';red();printf("2048> Missing EOL\n");reset();printf("---->");}
            | operation {std::cerr << "-1" << '\n';red();printf("2048> Syntax for move: <operation> <direction> EOL\n");reset();printf("---->");}
            | direction {std::cerr << "-1" << '\n';red();printf("2048> Syntax for move: <operation> <direction> EOL\n");reset();printf("---->");}
            | operation direction EOL {move(g, m, $1, $2);}
            | ASSIGN TO num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Enter number to be asigned to the tile\n");reset();printf("---->");}
            | ASSIGN num num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing TO after value\n");reset();printf("---->");}
            | ASSIGN num TO COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing the x coordinate\n");reset();printf("---->");}
            | ASSIGN num TO num num EOL {std::cerr << "-1" << '\n';red();printf("2048> Separate the coordinates by ','\n");reset();printf("---->");}
            | ASSIGN num TO num COMMA EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing the y coordinate\n");reset();printf("---->");}
            | ASSIGN num TO num COMMA num {std::cerr << "-1" << '\n';red();printf("2048> Missing EOL\n");reset();printf("---->");}
            | ASSIGN num EOL {std::cerr << "-1" << '\n';red();printf("2048> Enter coordinates to fill value in\n");reset();printf("---->");}
            | num TO num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Did you forget the ASSIGN token\n");reset();printf("---->");}
            | ASSIGN EOL {std::cerr << "-1" << '\n';red();printf("2048> Syntax for Assign: ASSIGN <num> TO <num>, <num> EOL\n");reset();printf("---->");}
            | ASSIGN num {std::cerr << "-1" << '\n';red();printf("2048> Missing EOL\n");reset();printf("---->");}
            | ASSIGN num TO num COMMA num EOL {assign_val(g, m, $2, $4, $6);}
            | VAR IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Enter variable name after VAR\n");reset();printf("---->");}
            | VAR identifier IS COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing the x coordinate\n");reset();printf("---->");}
            | VAR identifier IS num COMMA EOL {std::cerr << "-1" << '\n';red();printf("2048>Missing the y coordinate\n");reset();printf("---->");}
            | VAR identifier IS num num EOL {std::cerr << "-1" << '\n';red();printf("2048> Separate the coordinates by ','\n");reset();printf("---->");}
            | VAR identifier IS num COMMA num {std::cerr << "-1" << '\n';red();printf("2048> Missing EOL\n");reset();printf("---->");}
            | VAR identifier num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> Missing IS after <identifier>\n");reset();printf("---->");}
            | VAR ADD IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR SUBTRACT IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR MULTIPLY IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR DIVIDE IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR RIGHT IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR LEFT IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR UP IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR DOWN IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR IS IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR EXIT IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR ASSIGN IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR VAR IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR TO IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR VALUE IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR EOL IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR COMMA IS num COMMA num EOL {std::cerr << "-1" << '\n';red();printf("2048> A keyword can't be a variable name\n");reset();printf("---->");}
            | VAR identifier IS num COMMA num EOL {assign_var(g, m, $2, $4, $6);}

            | VALUE IN num COMMA num {std::cerr << "-1" << '\n';red();printf("2048> Missing EOL\n");reset();printf("---->");}
            | VALUE IN num num EOL{std::cerr << "-1" << '\n';red();printf("2048> Separate the coordinates by ','\n");reset();printf("---->");}
            | VALUE num COMMA num EOL{std::cerr << "-1" << '\n';red();printf("2048> Missing IN after value\n");reset();printf("---->");}
            | VALUE EOL{std::cerr << "-1" << '\n';red();printf("2048> Syntax for VALUE query: VALUE IN <x>, <y>.\n");reset();printf("---->");}
            | VALUE {std::cerr << "-1" << '\n';red();printf("Missing EOL");}
            | VALUE IN COMMA num EOL{std::cerr << "-1" << '\n';red();printf("2048> Missing the x coordinate\n");reset();printf("---->");}
            | VALUE IN num COMMA EOL{std::cerr << "-1" << '\n';red();printf("2048> Missing the y coordinate\n");reset();printf("---->");}
            | VALUE IN num COMMA num EOL {return_value(g, $3, $5);}

            | EXIT {yellow();printf("2048> Thanks for Playing!\n");reset();exit(EXIT_SUCCESS);}
            | error "\n" {yyerrok;yyclearin; red();printf("2048> I don't understand that! Try again.\n");reset();printf("---->");}
            ;

operation   : ADD {$$ = 1;}
            | SUBTRACT {$$ = 2;}
            | MULTIPLY {$$ = 3;}
            | DIVIDE {$$ = 4;};

direction   : UP {$$ = 100;}
            | DOWN {$$ = 200;}
            | RIGHT {$$ = 300;}
            | LEFT {$$ = 400;};

num         : number {;}
            | VALUE IN number COMMA number EOL {return_value(g, $3, $5);}

%%

/* All functions come here */

int main(){
  start(g);
  while(1){
    yyparse();
  }
}

int yyerror (char const *s) {
  /* printf("%s\n", s); */
  red();
  printf("2048> I don't understand that! Try again.\n");
  reset();
  printf("---->");
  return 0;
}
