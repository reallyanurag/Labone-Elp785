#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include"../include/header.h"

const int scale = 16;


int DoubleToFixed(double);
double FixedToDouble(int);
int Mul(int,int);

int main()
{
	int sum,i=0,j=0,k=0,r=0,micro = 1e-6;
	int nreps=750;
	double start,end,start1,end1;
	
	
	double **A,**B,**C;
	int **D,**E,**F;
	
	
	
	FILE *fpointer = fopen("src/floatingpoint.dat","w");
	FILE *fpointer1 = fopen("src/fixedpoint.dat","w");
	
	
	for(r=1;r<=nreps;r=r+25){
		
		A = malloc(sizeof(double *) * r);
		for(i=0;i<r;i++){
			A[i] = malloc(sizeof(double)*r);
		}
		B = malloc(sizeof(double *) * r);
		for(i=0;i<r;i++){
			B[i] = malloc(sizeof(double)*r);
		}
		C = malloc(sizeof(double *) * r);
		for(i=0;i<r;i++){
			C[i] = malloc(sizeof(double)*r);
		}
		D = malloc(sizeof(int *) * r);
		for(i=0;i<r;i++){
			D[i] = malloc(sizeof(int)*r);
		}
		E = malloc(sizeof(int *) * r);
		for(i=0;i<r;i++){
			E[i] = malloc(sizeof(int)*r);
		}
		F = malloc(sizeof(int *) * r);
		for(i=0;i<r;i++){
			F[i] = malloc(sizeof(int)*r);
		}
		
		
		for(i=0;i<r;i++){
			for(j=0;j<r;j++){
				A[i][j] = ((double)rand()/RAND_MAX)*5.0; 
				B[i][j] = ((double)rand()/RAND_MAX)*5.0;
			}
		}
		
		for(i=0;i<r;i++){
			for(j=0;j<r;j++){
				D[i][j] = DoubleToFixed(A[i][j]);
				E[i][j] = DoubleToFixed(B[i][j]);
			}
		}
		
		start = calculateTime();
		
		for(i=0;i<r;i++){
			for(j=0;j<r;j++){
				sum=0;
				for(k=0;k<r;k++){
					sum+= A[i][k] * B[k][j];
					C[i][j] = sum;
					}
				}
			}
		end = calculateTime();
		
		fprintf(fpointer, "%d    %lf\n",r, (end-start));
		
		
		start1 = calculateTime();
		
		for(i=0;i<r;i++){
			for(j=0;j<r;j++){
				sum=0;
				for(k=0;k<r;k++){
					sum+= Mul(D[i][k],E[k][j]);
					F[i][j] = FixedToDouble(sum);
				}
			}
		}
		
		end1 = calculateTime();
		fprintf(fpointer1,"%d    %lf\n",r,(end1-start1));
		
		}
		
		fclose(fpointer);
		fclose(fpointer1);
	
}


int DoubleToFixed(double x){
	return (x*(double)(1<<scale));
}

double FixedToDouble(int x){
	return ((double)x/(double)(1<<scale));
}

int Mul(int x, int y){
	return((x>>8)*(y>>8));
}
