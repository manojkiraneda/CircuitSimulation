#include<stdio.h>
#include<stdlib.h>

void GSolve(double **a,int order,double *x)
{
	double temp,t,temp1;
	int i,j,k,l,p;

	for(i=0;i<order;i++)
	{
		for(j=0;j<order+1;j++)
		printf("%f\t",a[i][j]);
		printf("\n");
	}
//partial pivoting(pivotisation)
    for(i=0;i<order;i++)
    {
        for(k=i+1;k<order;k++)
        {

            if(a[i][i]<a[k][i])
            {
                for(j=0;j<=order;j++)
                {
                    temp = a[i][j];
                    a[i][j] = a[k][j];
                    a[k][j] = temp;
                }
            }

        }
    }
printf("Matrix After Partial Pivoting \n");
printf("++++++++++++++++++++++++++++++++\n");
for(i=0;i<order;i++)
{
	for(j=0;j<order+1;j++)
	printf("%f\t",a[i][j]);
	printf("\n");
}

//Performing the Gaussian Elimination
for(i=0;i<order-1;i++)
{
    for(p=i+1;p<order;p++)
    {

        if(a[i][i]==0)//If pivot becomes zero,then row exchange will happen
        {
            for(j=0;j<=order;j++)
            {
                temp1 = a[i][j];
                a[i][j] = a[p][j];
                a[p][j] = temp1;
            }
        }

    }

    for(k=i+1;k<order;k++)
    {
        t = a[k][i]/a[i][i];
        for(j=0;j<=order;j++)
        {
            a[k][j]=a[k][j]-t*a[i][j];
        }
    }
}
printf("\nMatrix After Gaussian Elimination \n");
printf("++++++++++++++++++++++++++++++++\n");
for(i=0;i<order;i++)
{
	for(j=0;j<order+1;j++)
	printf("%f\t",a[i][j]);
	printf("\n");
}

//Back Substitution
for(i=order-1;i>=0;i--)
{
    x[i]=a[i][order];
    for(j=0;j<order;j++)
    {
        if(j!=i)
            {
                x[i]=x[i]-a[i][j]*x[j];
            }

    }
    x[i]=x[i]/a[i][i];
}
printf("\nMatrix Solution\n");
printf("++++++++++++++++++++++++++++++++\n");
for(i=0;i<order;i++)
{
	printf("%f\n",x[i]);

}

}






