all:netlistlexexe run
netlistlexexe:lexCode.l YaccCode.y lex.yy.c y.tab.c engine.c elimination.c gaussiansweep.c
	      yacc -d YaccCode.y
	      lex lexCode.l 
	      gcc -o netlistlexexe lex.yy.c y.tab.c engine.c elimination.c gaussiansweep.c
.PHONY:	      run
run:	      netlistlexexe 
	      ./netlistlexexe netlist.sp
