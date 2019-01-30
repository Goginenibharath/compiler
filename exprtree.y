%{
	#include <stdio.h>
	#include <stdlib.h>

	#define YYSTYPE tnode *

	#include "exprtree.h"
	#include "exprtree.c"
	
	int yylex(void);

%}

%token NUM PLUS MINUS MUL DIV END
%left PLUS MINUS
%left MUL DIV

%%

program : expr END	{
				$$ = $2;
				printf("Prefix form is:");
				int *registerno;
				*registerno=0;
											
				prefix($1);
				printf("\n");
				printf("Postfix form is:");
				
				postfix($1);
				printf("\n");
				
				printf("Answer : %d\n",evaluate($1));
				//printf("Welcome");
				//FILE *fp;
				//fp=fopen("a.xsm","w");
				//if(fp!=NULL)
				//printf("no file",*registerno);
				codegen($1,registerno);
				exit(1);
			}
		;

expr : expr PLUS expr		{$$ = makeOperatorNode('+',$1,$3);}
	 | expr MINUS expr  	{$$ = makeOperatorNode('-',$1,$3);}
	 | expr MUL expr	{$$ = makeOperatorNode('*',$1,$3);}
	 | expr DIV expr	{$$ = makeOperatorNode('/',$1,$3);}
	 | '(' expr ')'		{$$ = $2;}
	 | NUM			{$$ = $1;}
	 ;

%%

yyerror(char const *s)
{
    printf("yyerror %s",s);
}


int main(void) {
	yyparse();
	return 0;
}
