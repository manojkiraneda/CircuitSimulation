#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"engine.h"

extern struct node_data *hashtable[100];
extern struct node_data *node;
struct node_data *tempNode;
struct node_data *tempNode1;
struct node_data *tempNode2;
extern struct node_data *head;
extern int nnodes,nvoltages,nlines;
struct dc_node_data dc_node;
extern int *pointer_unique_vol;
int *pointer_unique_elements;
int unique = 0;
double **mna_matrix;
double **mna_matrix_z;
double *mna_matrix_x;
double **augmentedmatrix;


int map_index_volatge(int);
void GSolve(double **,int,double *);
//void gaussianelimination(double **mna_matrix,double **mna_matrix_z,int row);
void printtable();
int parser_init(char *);
int getunique_nodes();
int unique_elements_count(int* arr, int len);
void form_mna_matrix(int *,int *);
int map_index(int);
void dc_sweep(double **,int,double *,double **,struct dc_node_data*,int,int,int,double **);



int main(int argc,char* argv[])
{
    int status = parser_init(argv[1]);
    printtable();
    nnodes = getunique_nodes();
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nNvoltages = %d \nNnodes = %d\n",nvoltages,nnodes);
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\nPrinting the MNA Matrix : \n");
    //printf("Manoj\n");i   i
    form_mna_matrix(&nnodes,&nvoltages);
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    return 0;

}

int map_index(int node_number)
{

    //printf("unique = %d\n",unique);
    for(int i=0;i<unique;i++)
    {
        //printf("node_number = %d\t unique_no = %d\n",node_number,pointer_unique_elements[i]);
       if(node_number == (pointer_unique_elements[i]))
        {
            return i;
        }
    }
    return -1;
}

int map_index_volatge(int vol_number)
{
    for(int i=0;i<nvoltages;i++)
    {
        if(vol_number == (pointer_unique_vol[i]))
        {
            return i;
        }
    }
    //return -1;

}

void form_mna_matrix(int *nnodes,int *nvoltages)
{
    //printf("here");
    int i,j,p,q,r,k,status;
    int n = *nnodes;
    int m = *nvoltages;
    int row = n+m;
    int column = n+m;
    //mna_matrix;
    //mna_matrix = malloc(row*sizeof(double *) + (row * (column * sizeof(double))));

    mna_matrix = (double **)malloc(row*sizeof(double *));
    for(i=0;i<row;i++)
    {
        mna_matrix[i]=(double *)malloc(column*sizeof(double));
    }

    augmentedmatrix = (double **)malloc(row*sizeof(double *));
    for(i=0;i<row;i++)
    {
        augmentedmatrix[i]=(double *)malloc((column+1)*sizeof(double));
    }
    //double mna_matrix[row][column];

    mna_matrix_x = (double *)malloc(row*sizeof(double));

    for(i=0;i<row;i++)
    {
        mna_matrix_x[i]=0;
    }

    mna_matrix_z = (double **)malloc(row*sizeof(double*));
    for(i=0;i<row;i++)
    {
        mna_matrix_z[i]=(double *)malloc(sizeof(double));
    }

    //double mna_matrix_z[row][1];
    //double G;
    //memset(mna_matrix, 0, sizeof(mna_matrix));
    //memset(mna_matrix_z, 0, sizeof(mna_matrix));

    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            mna_matrix[i][j]=0;
            *(*(mna_matrix_z+i))=0;
            printf("%f\t",mna_matrix[i][j]);
        }
        printf("\n");
     }

     for(i=0;i<row;i++)
     {
         for(j=0;j<(column+1);j++)
         {
             augmentedmatrix[i][j] = 0;
             //printf("%f\t",augmentedmatrix[i][j]);
         }
         printf("\n");
      }

     //scanf("%d",&i);
    //tempNode2 = (struct node_data*)malloc(sizeof(struct node_data));
    //if(tempNode2 == NULL) printf("Error Gen");
    //printf("%d\t",tempNode2->ini_node);

	for(i=0;i<=99;i++)
	{
	    tempNode2 = hashtable[i];
    	while((tempNode2) !=NULL)
	    {
	        if(tempNode2->element_type == 'r' || tempNode2->element_type == 'R' )
	            {
	                p = map_index(tempNode2->ini_node);
        	        q = map_index(tempNode2->fin_node);
        	        printf("Index-p = %d\t,Index-q = %d\n",p,q);
                    if(p!=-1)
                    {
                        mna_matrix[p][p] += (float)1/(tempNode2->element_value);
                    }
                    if(q!=-1)
                    {
                        mna_matrix[q][q] += (float)1/(tempNode2->element_value);
                    }
                    if(p!=-1 && q!=-1)
                    {
                        mna_matrix[p][q] -= (float)1/(tempNode2->element_value);
                        mna_matrix[q][p] -= (float)1/(tempNode2->element_value);
                    }

	            }
	         printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	         if(tempNode2->element_type == 'v'|| tempNode2->element_type == 'V')
	            {
	                p = map_index(tempNode2->ini_node);
        	        q = map_index(tempNode2->fin_node);
        	        r = map_index_volatge(tempNode2->element_number)+unique;
        	        printf("Index-p = %d\t,Index-q = %d\t,Index-r = %d\n",p,q,r);
        	        if(p!=-1)
        			{
        				mna_matrix[p][r]=1;
        				mna_matrix[r][p]=1;

        			}

        			if(q!=-1)
        			{
          				mna_matrix[q][r]=-1;
    				    mna_matrix[r][q]=-1;
                    }

                    //printf("%f\n",mna_matrix_z[r][1]);
                    *(*(mna_matrix_z+r))= (float)tempNode2->element_value;

                    //scanf("%d",&k);
	            }
	            if(tempNode2->element_type == 'i'|| tempNode2->element_type == 'I')
            		{
            			p = map_index(tempNode2->ini_node);
            	        q = map_index(tempNode2->fin_node);

            			if(p!=-1)
            			{
            			    //printf("manoj");
            			    *(*(mna_matrix_z+p)) = (float)tempNode2->element_value;
            			}


            			if(q!=-1)
            			{
            				*(*(mna_matrix_z+q)) = -(float)tempNode2->element_value;
            			}

                    }
	      //printf("%d\t",tempNode1->ini_node);
	      tempNode2 = tempNode2->nextnode;
	    }
	 }

printf("\n\n");


printf("\n++++++++MNA_MATRIX++++++++++\n");
for(i=0;i<row;i++)
{
    for(j=0;j<column;j++)
    {
        printf("%f\t",mna_matrix[i][j]);
    }
    printf("\n");
 }

printf("\n++++++++MNA_MATRIX_Z++++++++++\n");

for(i=0;i<row;i++) printf("%f\n",*(*(mna_matrix_z+i)));

for(i=0;i<row;i++)
{
    for(j=0;j<(column+1);j++)
    {
        if(j<column)
        {
            augmentedmatrix[i][j]=mna_matrix[i][j];
        }
        else
        {
            augmentedmatrix[i][j]=*(*(mna_matrix_z+i));
        }
    }
}

printf("\n++++++++AUGMENTED MATRIX++++++++++\n");

for(i=0;i<row;i++)
{
    for(j=0;j<(column+1);j++)
    {
        printf("%f\t",augmentedmatrix[i][j]);
    }
    printf("\n");
}

printf("row = %d \t column = %d\n",row,column);
printf("+++++++++++++++++++++++++++++++++++++\n");
//gaussianelimination(mna_matrix,mna_matrix_z,row);
GSolve(augmentedmatrix,row,mna_matrix_x);
if(dc_node.status == 1)
{
    printf("+++++++++++++++DC-Sweep Required+++++++++++++++++\n");
    dc_sweep(augmentedmatrix,row,mna_matrix_x,mna_matrix_z,&dc_node,unique,row,column,mna_matrix);

}


}


int getunique_nodes()
{
    int count = 0;
    int *node_pointer = (int*)malloc(200*sizeof(int));
    //tempNode = (struct node_data*)malloc(sizeof(struct node_data));
    int *temp_node_pointer = node_pointer;
    for(int i =0;i<=99;i++)
    {
        if(hashtable[i]!=NULL)
            {
            //printf("hash = %p\n",hashtable[i]);
            tempNode = (struct node_data*)hashtable[i];
            while((tempNode) != NULL)
            {
                *node_pointer = tempNode->ini_node;
                //printf("%p\n",node_pointer);
                node_pointer++;
                *node_pointer = tempNode->fin_node;
                //printf("%p\n",node_pointer);
                tempNode = tempNode->nextnode;
                node_pointer++;

            }

            }
    }
    node_pointer = temp_node_pointer;
    for(int j=0;j<=99;j=j+2)
    {
        printf("Values : %d,%d\n",*(node_pointer+j),*(node_pointer+j+1));

    }
    count = unique_elements_count(node_pointer,2*nlines);
    return (count);

}

int unique_elements_count(int* arr, int len)
{
 int inner,i,j;
 pointer_unique_elements = (int*)malloc(sizeof(int));
 int *temppointer = pointer_unique_elements;

for(i = 0; i < len; i++)
{
    for (j=0; j<i; j++)
    {
        if (arr[i] == arr[j])
        break;
    }

    if ((i == j) && arr[i]!=0)
    {
       /* No duplicate element found between index 0 to i */
       //printf("%d\t", arr[i]);

        if(unique >= 1)
           {
                pointer_unique_elements = (int*)realloc(pointer_unique_elements,unique*sizeof(int));*(pointer_unique_elements+unique) = arr[i];
           }
        else
           {
                pointer_unique_elements = (int*)realloc(pointer_unique_elements,sizeof(int));*(pointer_unique_elements) = arr[i];
           }
   ++unique;
}
}
pointer_unique_elements = temppointer;
for(int i=0;i< unique;i++)
{
   printf("%d\n",*(pointer_unique_elements+i));

}
printf("No of Unique Elements : %d\n",unique);
return (unique);
}


int generatehash(int val)
{
    int marker;
    marker = val%97;
    //printf("marker = %d\n",marker);
    return marker;
}

void printtable()
{
    int i;
    tempNode1 = (struct node_data*)malloc(sizeof(struct node_data));

     //printf("%d\t",tempNode1->ini_node);
	for(i=0;i<=99;i++)
	{
	    tempNode1 = hashtable[i];
    	while((tempNode1) !=NULL)
	    {
	      printf("%d\t",tempNode1->ini_node);
	      tempNode1 = tempNode1->nextnode;
	    }
	}
	printf("\nindex = %d,pointer = %p\n",i,hashtable[i]);
}


