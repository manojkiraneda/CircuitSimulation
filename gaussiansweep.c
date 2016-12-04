#include<stdio.h>
#include<stdlib.h>
#include"engine.h"

extern int map_index_volatge(int);
double **mna_matrix_dc;
double **final_matrix_dc;

void dc_sweep(double **a,int order,double *x,double **b,struct dc_node_data *dc_node,int unique,int row,int column,double **mna)
{
	double temp,t,temp1;
	double *dc_sweep_voltage,h=0;
	int i,j,k,l,p,mapp_index,size;
  printf("dc_type = %c,dc_number=%d,start=%f,stop=%f,step=%f\n",dc_node->dc_type,dc_node->dc_number,dc_node->start,dc_node->stop,dc_node->step);
    size = (int)((dc_node->stop - dc_node->start)/dc_node->step + 1);
    printf("Size : %d\n",size);
    dc_sweep_voltage = (double *)malloc(size*sizeof(double));
    for(i=0;i<size;i++)
    {
        h = dc_node->start+(dc_node->step*i);
        dc_sweep_voltage[i]=h;
    }
    for(i=0;i<size;i++)
    {
        printf("dc_sweep_volatge[%d]=%f\n",i,dc_sweep_voltage[i]);
    }

    mapp_index = map_index_volatge(dc_node->dc_number)+unique;
    printf("Mapp_index = %d\n",mapp_index);

    mna_matrix_dc = (double **)malloc(row*sizeof(double*));
    for(i=0;i<row;i++)
    {
        mna_matrix_dc[i]=(double *)malloc(size*sizeof(double));
    }

    for(i=0;i<row;i++)
    {
        for(j=0;j<size;j++)
         {
            mna_matrix_dc[i][j] = 0.0;
            printf("%f\t",mna_matrix_dc[i][j]);
         }
         printf("\n");
    }

    printf("\n++++++++++++++++++++++++++++++++++++\n");
     printf("\n++++++++++++B Matrix++++++++++++++++\n");
     for(i=0;i<row;i++) printf("%f\n",*(*(b+i)));
     printf("\n+++++++++++++++++++++++++++++++\n");
    for(i=0;i<size;i++)
    {
        for(j=0;j<row;j++)
        {

                mna_matrix_dc[j][i] = *(*(b+j));
                if(j == mapp_index)
                {
                    mna_matrix_dc[j][i] = dc_sweep_voltage[i];
                }
        }
    }

    for(i=0;i<row;i++)
    {
        for(j=0;j<size;j++)
        {
               printf("%f\t",mna_matrix_dc[i][j]);
        }
        printf("\n");
    }
    printf("\n++++++++++++++++++++++++++++++++++++++\n");

    final_matrix_dc = (double **)malloc(row*sizeof(double *));
    for(i=0;i<row;i++)
    {
        final_matrix_dc[i]=(double *)malloc((column+size)*sizeof(double));
    }
printf("\n++++++++MNA_MATRIX++++++++++\n");
for(i=0;i<row;i++)
{
    for(j=0;j<column;j++)
    {
        printf("%f\t",mna[i][j]);
    }
    printf("\n");
 }
 printf("\n+++++++++++++++++++++++++++++++\n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<column+size;j++)
         {
            final_matrix_dc[i][j] = 0.0;
            printf("%f\t",final_matrix_dc[i][j]);
         }
         printf("\n");
    }
    //stitching Matrix to The augmented Matrix

    for(i=0;i<row;i++)
    {
        for(j=0;j<(column+size);j++)
        {
            if(j<column)
            {
                final_matrix_dc[i][j]=mna[i][j];
            }
            else
            {
                final_matrix_dc[i][j]=mna_matrix_dc[i][j-column];
            }
        }
    }
    printf("\n++++++++++++++++++++++++++++++++++\n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<column+size;j++)
         {
            printf("%f\t",final_matrix_dc[i][j]);
         }
         printf("\n");
    }



    printf("\n+++++++++++++++++++++++++++++++++++\n");
    //getchar();
	for(i=0;i<order;i++)
	{
		for(j=0;j<order+size;j++)
		printf("%f\t",final_matrix_dc[i][j]);
		printf("\n");
	}

//partial pivoting(pivotisation)
    for(i=0;i<order;i++)
    {
        for(k=i+1;k<order;k++)
        {

            if(final_matrix_dc[i][i]<final_matrix_dc[k][i])
            {
                for(j=0;j<=order+size;j++)
                {
                    temp = final_matrix_dc[i][j];
                    final_matrix_dc[i][j] = final_matrix_dc[k][j];
                    final_matrix_dc[k][j] = temp;
                }
            }

        }
    }

printf("Matrix After Partial Pivoting \n");
printf("++++++++++++++++++++++++++++++++\n");
for(i=0;i<order;i++)
{
	for(j=0;j<order+size;j++)
	printf("%f\t",final_matrix_dc[i][j]);
	printf("\n");
}

//Performing the Gaussian Elimination
for(i=0;i<order-1;i++)
{
    for(p=i+1;p<order;p++)
    {

        if(final_matrix_dc[i][i]==0)//If pivot becomes zero,then row exchange will happen
        {
            for(j=0;j<=order+size;j++)
            {
                temp1 = final_matrix_dc[i][j];
                final_matrix_dc[i][j] = final_matrix_dc[p][j];
                final_matrix_dc[p][j] = temp1;
            }
        }

    }

    for(k=i+1;k<order;k++)
    {
        t = final_matrix_dc[k][i]/final_matrix_dc[i][i];
        for(j=0;j<=order+size;j++)
        {
            final_matrix_dc[k][j]=final_matrix_dc[k][j]-t*final_matrix_dc[i][j];
        }
    }
}

printf("\nMatrix After Gaussian Elimination \n");
printf("++++++++++++++++++++++++++++++++\n");
for(i=0;i<order;i++)
{
	for(j=0;j<order+size;j++)
	printf("%f\t",final_matrix_dc[i][j]);
	printf("\n");
}

//Back Substitution
for(k=0;k<size;k++)
{
    for(i=order-1;i>=0;i--)
    {
        x[i]=final_matrix_dc[i][order+k];
        for(j=0;j<order;j++)
        {
            if(j!=i)
                {
                    x[i]=x[i]-final_matrix_dc[i][j]*x[j];
                }

        }
        x[i]=x[i]/final_matrix_dc[i][i];
    }
    printf("\nMatrix Solution\n");
    printf("++++++++++++++++++++++++++++++++\n");
    for(i=0;i<order;i++)
    {
    	printf("%f\n",x[i]);

    }
}
getchar();

}






