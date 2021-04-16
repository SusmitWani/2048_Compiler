%{
  #include "parser.tab.hh"
  void yyerror (char *s);
  int yylex();
%}
%%
[ \t]                   {;}
"ADD"                   {return ADD;}
"SUBTRACT"              {return SUBTRACT;}
"MULTIPLY"              {return MULTIPLY;}
"DIVIDE"                {return DIVIDE;}

"UP"                    {return UP;}
"DOWN"                  {return DOWN;}
"RIGHT"                 {return RIGHT;}
"LEFT"                  {return LEFT;}

"EXIT"                  {return EXIT;}
"ASSIGN"                {return ASSIGN;}
"TO"                    {return TO;}
"VAR"                   {return VAR;}
"IS"                    {return IS;}
"VALUE"                 {return VALUE;}
"IN"                    {return IN;}
"."                     {return EOL;}
","                     {return COMMA;}

[0-9]+                  {yylval.val = atoi(yytext); return number;}
[a-zA-Z_][A-Za-z0-9_]*  {yylval.str = strdup(yytext); return identifier;}
.                       {;}
"\n"                    {return 0;}
<<EOF>>                 {return GG;}
%%
int yywrap (void) {return 1;}
