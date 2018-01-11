#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 50
#define TOL 0.001

double **readFromFileToMatrix(double **arr, int *size, FILE *filePointer);
void freeMatrix(double **arr, int size);
void gauss(double **arr, int size);
void solve(double **arr, double *b, int *l, int size);
double StoppingCriteria(double *arr1, double *arr2, int size);
void jacobi(double **arr,  int size);

int main(int argc, char *argv[]) {

	FILE *filePointer;
	double **arr;
	int size;
	int i,j;

	if (argc != 5) {
		fprintf(stderr, "Usage: %s [-flag for system file] <system.txt> [-flag for method] method\n", argv[0]);
		fprintf(stderr, "Sample Usage: %s -i system.txt -m GESP\n", argv[0]);
		return 1;
	}
	if (strcmp(argv[1],"-i") !=0) {
		fprintf(stderr, "Ivalid flag option for system file\n");
		return 1;
	}
	if (strcmp(argv[3],"-m") !=0) {
		fprintf(stderr, "Ivalid flag option for method\n");
		return 1;
	}
	if (NULL == (filePointer = fopen(argv[2], "r"))) {
		fprintf(stderr, "Failed to open system file %s\n", argv[2]);
		return 1;
	}
	arr = readFromFileToMatrix(arr, &size, filePointer);
	if (strcmp(argv[4], "GESP") == 0)
		gauss(arr, size);
	else if (strcmp(argv[4], "JCB") == 0)
		jacobi(arr, size);
	else
		fprintf(stderr, "%s method is not found \n", argv[4]);

	fclose(filePointer);

	freeMatrix(arr, size);
	return 0;
}





double **readFromFileToMatrix(double **arr, int *size, FILE *filePointer) {

	int i = 0;
	int j = 0;
	char ch = 'x';
	double value = 0;

	while (ch != '\n') {
		fscanf(filePointer, "%lf", &value);
		fscanf(filePointer, "%c", &ch);
		(*size)++;
	}
	(*size)--;
	fseek(filePointer, SEEK_SET, 0);

	arr = calloc((*size)+1, sizeof(double *)); //--arr;
	for(i = 0; i < (*size)+1; ++i)  
		arr[i] =  calloc((*size)+1, sizeof(double)); --arr[i];

	for (i = 0; i < *size; i++) {
		for (j = 0; j < (*size)+1; j++) {
			fscanf(filePointer, "%lf", &value);
			arr[i][j] = value;
			fscanf(filePointer, "%c", &ch);
		}
	}
	return arr;
}

void freeMatrix(double **arr, int size) {

	int i = 0;
	for (i = 0; i < size; i++);
		free(arr[i]);
	free(arr);
}


void jacobi(double **arr,  int size)  {

	int k = 1;
	int i,j;
	double sum = 0.0;
	double *XO = (double *)calloc(size, sizeof(double)); 
	double *x = (double *)calloc(size, sizeof(double)); 
	double *b = (double *)calloc(size, sizeof(double));

	for (i = 0; i < size; i++) {
		b[i] = arr[i][size];
		XO[i] = 0.0;
	}
	while (k <= 100) {
		for (i = 0; i < size; i++) {
			sum = 0.0;
			for (j = 0; j < size; j++) {
				if (i != j)
					sum = sum + arr[i][j] * XO[j];

			}
			x[i] = (1/arr[i][i])*(b[i] - sum);
		}


		if (StoppingCriteria(x, XO, size) < TOL)
			break;
		k++;
		for (i = 0; i < size; i++) 
			XO[i] = x[i];
	}
	if (k > 100)
		fprintf(stderr, "This linear system is not convergent(exceeds maximum iterration number).\n");
	else
		for (i = 0; i < size; i++)
			printf("X[%d] = %f\n", i+1, x[i]);

	free(XO);
	free(x);
	free(b);
}

double StoppingCriteria(double *arr1, double *arr2, int size) {

	double result = 0.0, sum1 = 0.0, sum2 = 0.0;
	int i;

	for (i = 0; i < size; i++) {

		sum1 = sum1 + pow(arr1[i] - arr2[i], 2);
		sum2 = sum2 + pow(arr1[i],2);
	}

	result = sqrt(sum1)/sqrt(sum2);
	return result;
}

void gauss(double **arr, int size) {

  int i,j,k,temp;
  int *l = (int *)calloc(size, sizeof(int));
  double *s = (double *)calloc(size, sizeof(double));
  double *b = (double *)calloc(size, sizeof(double));
  double r,rmax,smax,xmult;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++)
      b[i] = arr[i][size];
  }

  for (i = 0; i < size; i++) {
    l[i] = i;
    smax = 0;
    for (j = 0; j < size; j++) {
      if (fabs(arr[i][j]) > smax)
        smax = fabs(arr[i][j]);
    }
    s[i] = smax;
  }
  for (k = 0; k < size-1; k++) {
    rmax = 0;
    for (i = k; i < size; i++) {
      r = fabs(arr[l[i]][k]/s[l[i]]);
      if (r > rmax) {
        rmax = r;
        j = i;
      }
    }
    temp = l[j];
    l[j] = l[k];
    l[k] = temp;
    for (i = k+1; i < size; i++) {
      xmult = arr[l[i]][k]/arr[l[k]][k];
      arr[l[i]][k] = xmult;
      for (j = k+1; j < size; j++)
        arr[l[i]][j] = arr[l[i]][j] - (xmult)*arr[l[k]][j];
    }
  }

  solve(arr, b, l, size);
  
  free(s);
  free(l);
  free(b);
}

void solve(double **arr, double *b, int *l, int size) {

  int i,j,k;
  double sum;
  double *x = (double *)calloc(size, sizeof(double));

  for (k = 0; k < size-1; k++) {
    for (i = k+1; i < size; i++) 
      b[l[i]] = b[l[i]] - arr[l[i]][k]*b[l[k]];
  }
  x[size-1] = b[l[size-1]]/arr[l[size-1]][size-1];
  for (i = size-2; i >= 0; i--) {
    sum = b[l[i]];
    for (j = i + 1; j < size; j++) 
      sum = sum - arr[l[i]][j]*x[j];
    x[i] = sum/arr[l[i]][i];
  } 

  for (i = 0; i < size; i++) 
    printf("X[%d] = %f\n", i+1, x[i]);

  free(x);
}



