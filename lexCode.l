%{

#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"

%}

%option noyywrap

%%
".end"          ;
[rviRVI]	    {yylval.character = yytext[0];return CHARACTER;}
[\n]+		    {return *yytext;}
[0-9]+\.[0-9]+  {yylval.number = atof(yytext);return INTEGER;}
[.0-9]+		    {yylval.number =atof(yytext);return INTEGER;}
[ \t]		    ;
".dc"           {yylval.character = 's';return CHARACTER;}
"*".*           ;//Dont parse the line starting with *(Comment)
.		        {printf("Syntax Error in Netlist File\n");exit(1);}

%%


