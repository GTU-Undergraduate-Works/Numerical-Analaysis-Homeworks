#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double * dividedDifferences(double *x, double *y, int size);

int main(void) {

	int i = 0;
	int j = 0;
	int size = 0;
	double *x = NULL;
	double *y = NULL;
	double *a = NULL;


	printf("Enter the number of data pairs to be entered\n");
	scanf("%d", &size);

	x = (double *)calloc(size, sizeof(double));
	y = (double *)calloc(size, sizeof(double));

	printf("Enter the x-axis values:\n");
	for (i = 0; i < size; i++)
		scanf("%lf", &x[i]);

	printf("Enter the y-axis values:\n");
	for (i = 0; i < size; i++)
		scanf("%lf", &y[i]);

	a = dividedDifferences(x, y, size);
  
  	printf("Divided Differences Polynomial:\n");
	printf("P(x) = (%.3f) ", a[0]);

	for (i = 1; i < size; i++) {

		printf("+ (%.3f)(x - %.3f)", a[i], x[0]);

		for (j = 1; j < i; j++)
			printf("(x - %.3f)", x[j]);
	}
	printf("\n");

	free(x);
	free(y);
	free(a);
	return 0;
}

double * dividedDifferences(double *x, double *y, int size) {

	int i = 0;
	int j = 0;
	int k = 0;
	double **Y = NULL;
	double *a = NULL;

	Y = calloc(size, sizeof(double *));
	for(i = 0; i < size; ++i)  
		Y[i] =  calloc(size, sizeof(double));

	a = (double *)calloc(size, sizeof(double));

	for (i = 0; i < size; i++)
		Y[0][i] = y[i];

	for (i = 1; i < size; i++) {

		k = i;
		for (j = 0; j < size-i; j++) {

			Y[i][j] = (Y[i-1][j+1] - Y[i-1][j]) / (x[k] - x[j]);
			k++;
		}
	}

	for (i = 0; i < size; i++) 
		a[i] = Y[i][0];

	for (i = 0; i < size; i++)
    	free(Y[i]);
    free(Y);
    return a;
}