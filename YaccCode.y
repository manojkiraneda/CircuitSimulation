%union
{
    float number;
    char character;
}
%token <number> INTEGER
%token <character> CHARACTER

%{

#include<stdio.h>
#include<stdlib.h>
#include"nodedefinitions.h"
extern int yylex();
void yyerror(char *msg);
char ch1,ch6,ch7;
int ch2,ch3,ch4,ch8,marker;
extern int nnodes,nvoltages,nlines;
double ch5,ch9,ch10,ch11;
extern struct dc_node_data dc_node;
extern struct node_data *node;
extern struct node_data *head;
extern void printtable();
extern int generatehash(int);
extern int getunique_nodes();
extern FILE* yyin;
int *pointer_unique_vol;

%}


%%

PROG	:	PROG EXP '\n'   {


				                //printf("Marker in yac = %d\n",marker);
                                if(ch6 != 's')
                                {
                                marker = generatehash(ch3);
                                nlines++;
                                node = (struct node_data*)malloc(sizeof(struct node_data));
       	                        node->element_type = ch1;
       	                        node->element_number = ch2;
       	                        node->ini_node = ch3;
       	                        node->fin_node = ch4;
       	                        node->element_value = ch5;
       	                        if(ch1 == 'v' || ch1 == 'V')
       	                            {
       	                                if(nvoltages >=1)
       	                                {
       	                                    pointer_unique_vol = (int*)realloc(pointer_unique_vol,nvoltages*sizeof(int));
           	                                *(pointer_unique_vol+nvoltages) = node->element_number;

       	                                }
       	                                else
       	                                {
       	                                    pointer_unique_vol = (int*)realloc(pointer_unique_vol,sizeof(int));
           	                                *(pointer_unique_vol) = node->element_number;
       	                                }
       	                                ++nvoltages;
       	                            }
       	                        if(hashtable[marker]== NULL)
       		                        {
      		                            hashtable[marker] = node;
                					    //printf("%p\n",hashtable[marker]);
            						    node->nextnode = NULL;
       		                        }
       	                        else
       		                        {
       		                            node->nextnode = hashtable[marker];
	            					    //printf("next node = %p\n",node->nextnode);
	            					    hashtable[marker] = node;
       		                        }


                                //display();
                                //printf("element_type = %c%d,ini_node = %d,fin_node = %d,element_value = %f,node =%p head = %p\n",

                                //node->element_type,node->element_number,node->ini_node,node->fin_node,node->element_value,node->nextnode,head);


                     		}
                     		}
    	|	PROG '\n'
    	|
    	;

EXP	:	CHARACTER INTEGER INTEGER INTEGER INTEGER 	{ch1=$1;ch2=$2;ch3=$3;ch4=$4,ch5=$5;}
	|   CHARACTER CHARACTER INTEGER INTEGER INTEGER INTEGER {ch6=$1;ch7=$2;ch8=$3;ch9=$4,ch10=$5,ch11=$6;
	                                                            if(ch6 == 's')
                                                                {
                                                                    dc_node.status = 1;
                                                                    dc_node.dc_type = ch7;
                                                                    dc_node.dc_number = ch8;
                                                                    dc_node.start = ch9;
                                                                    dc_node.stop = ch10;
                                                                    dc_node.step = ch11;
                                                                }
       //printf("dc_type = %c,dc_number=%d,start=%d,stop=%d,step=%d\n",dc_node.dc_type,dc_node.dc_number,dc_node.start,dc_node.stop,dc_node.step);

	                                                        }
	;


%%
void yyerror(char *msg)
{
	fprintf(stderr,"%s\n",msg);
	exit(1);
}

int parser_init(char *name)
{
    yyin=fopen(name,"r");

	while(!feof(yyin))
	{
		yyparse();
	}


	fclose(yyin);

	return 1;
}


