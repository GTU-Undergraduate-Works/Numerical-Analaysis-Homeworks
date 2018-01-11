#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double * findLeastsquarePolynomial(double *x, double *y, int m, int size) ;

int main(void) {

	int i = 0;
	int m = 0;
	int size = 0;
	double *x;
	double *y;
	double *a;

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

	printf("Enter degree of polynomial to fit.\n");
		scanf("%d", &m);

	if (m > size) {
		printf("The degree of polynomial can be up to %d\n", size);
		return 1;
	}

	a = findLeastsquarePolynomial(x, y, m, size);

	printf("Degrees of polynomial:\n");

	for (i = 0; i < m+1; i++)
		printf("a[%d] = %f\n", i, a[i]);

	free(x);
	free(y);
	free(a);
	return 0;
}

double * findLeastsquarePolynomial(double *x, double *y, int m, int size) {

	int i,j,k;
	double *X;
	double *Y;
	double **B;
	double *a;
	double t;
	double temp;

	X = (double *)calloc(2*m+1, sizeof(double));
	Y = (double *)calloc(m+1, sizeof(double));
	a = (double *)calloc(m+1, sizeof(double));

	B = calloc(m+1, sizeof(double *));
	for(i = 0; i < m+1; ++i)  
		B[i] =  calloc(m+2, sizeof(double));



	for (i = 0; i < 2*m+1; i++) {

		X[i] = 0;
		for (j = 0; j < size; j++)
			X[i] = X[i] + pow(x[j], i);
	}

	for (i = 0; i <= m; i++) {

		for (j = 0; j <= m; j++)
			B[i][j] = X[i+j];
	}
	for (i = 0; i < m+1; i++) {

		Y[i] = 0; 
		for (j = 0; j < size; j++)
			Y[i] = Y[i] + pow(x[j], i)*y[j];
	}

    for (i = 0;i <= m; i++)
        B[i][m+1] = Y[i]; 

    m = m + 1;

    for (i = 0; i < m; i++) {

    	for (k = i+1; k < m; k++) {

    		if (B[i][i] < B[k][i])
    			for (j = 0; j <= m; j++) {

    				temp = B[i][j];
    				B[i][j] = B[k][j];
    				B[k][j] = temp;
    			}
    	}
    }

    for (i = 0; i < m-1; i++) {

    	for (k = i+1; k < m; k++) {

    		t = B[k][i]/B[i][i];
    		for (j = 0; j <= m; j++)
    			B[k][j] = B[k][j] - t*B[i][j];
    	}
    }

    for (i = m-1; i >= 0; i--) {

    	a[i] = B[i][m];
		for (j = 0; j < m; j++) {
			if (j != i)
    			a[i] = a[i] - B[i][j]*a[j];
    	}

    	a[i] = a[i]/B[i][i];
    }

    for (i = 0; i < m+1; i++)
    	free(B[i]);
    free(B);
    free(X);
    free(Y);
	return a;
}