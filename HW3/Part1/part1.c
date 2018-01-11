#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*  
	NNI :	Nearest Neighbor Interpolation
	BCI	:	Bicubic Interpolation
	BLI : 	Bilinear Interpolation
*/
typedef enum {
	NNI, BCI, BLI
} tehcnique;

double **nearestNeighborInterpolation(double arr[][10], int zoomFactor);
double **bicubicInterpolation(double arr[][10], int zoomFactor);
double **bilenearInterpolation(double arr[][10], int zoomFactor);
double **ImageScalingWithInterpolation(double arr[][10], int zoomFactor, tehcnique tech);
int myRound(double x);
void freeMatrix(double **arr, int size);

int main(void) {

	double arr[10][10] = { {10,20,30,40,50,60,70,80,90,99},
					       {11,12,13,14,15,16,17,18,19,20},
					       {21,22,23,24,25,26,27,28,29,30},
					       {31,32,33,34,35,36,37,38,39,40},
					       {41,42,43,44,45,46,47,48,49,50},
					       {51,52,53,54,55,56,57,58,59,60},
					       {61,62,63,64,65,66,67,68,69,70},
					       {71,72,73,74,75,76,77,78,79,80},
					       {81,82,83,84,85,86,87,88,89,90},
					       {91,92,93,94,95,96,97,98,99,10} };

	int i = 0,j = 0;
	int zoomFactor = 0;
	int s = 0;
	double **newArr;

	printf("Please choose a Interpolation strategy to enlarge matrix\n");
	printf("Press 1 for Nearest Neighbor Interpolation.\n");
	printf("Press 2 for Bilinear Interpolation.\n");
	scanf("%d", &s);
	printf("Please enter integer zooming factor\n");
	scanf("%d", &zoomFactor);

	if (zoomFactor < 0) {

		printf("Zooming factor must be greater than 0.\n");
		return 1;
	}

	switch (s) {

		case 1:		
					newArr = ImageScalingWithInterpolation(arr, zoomFactor, NNI);
					break;
		case 2:    	
					newArr = ImageScalingWithInterpolation(arr, zoomFactor, BLI);
					break;

		default:
					printf("You made wrong choice for Interpolation strategy.\n");
					return 1;


	}

	printf("\n10 x 10 Matrix :\n\n");

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++)
			printf("%.2f ", arr[i][j]);
		printf("\n");
	}

	newArr = ImageScalingWithInterpolation(arr, zoomFactor, BLI);

	printf("\n%d x %d new matrix:\n\n", 10*zoomFactor, 10*zoomFactor);

	for (i = 0; i < 10*zoomFactor; i++) {
		for (j = 0; j < 10*zoomFactor; j++)
			printf("%.2f ", newArr[i][j]);
		printf("\n");
	}

	freeMatrix(newArr, 10*zoomFactor);
	return 0;
}

double **ImageScalingWithInterpolation(double arr[][10], int zoomFactor, tehcnique tech) {

	double **newArr;

	switch(tech) {

		case NNI: 
					newArr = nearestNeighborInterpolation(arr, zoomFactor);
					break;

		case BLI:	
					newArr = bilenearInterpolation(arr, zoomFactor);
					break;

	}
	return newArr;
}

double **nearestNeighborInterpolation(double arr[][10], int zoomFactor) {

	double **newArr;
	int i = 0, j = 0;
	int rowIndex = 0;
	int columnIndex = 0;

	newArr = calloc(10*zoomFactor, sizeof(double *));
	for(i = 0; i < 10*zoomFactor; ++i)  
		newArr[i] =  calloc(10*zoomFactor, sizeof(double));

	for (i = 0; i < 10*zoomFactor; ++i) {
		for (j = 0; j < 10*zoomFactor; ++j) {

			rowIndex = myRound((double)i/zoomFactor);
			columnIndex = myRound((double)j/zoomFactor);
			newArr[i][j] = arr[rowIndex][columnIndex];
		}
	}

	return newArr;
}

int myRound(double x) {

	int y = 0;

	y = (x+0.4999999999999999);

	if (y > 9)
		y = 9;
	
	return y;
}

void freeMatrix(double **arr, int size) {
  int i = 0;
  for (i = 0; i < size; ++i)
    free(arr[i]);
  free(arr);
}

double **bilenearInterpolation(double arr[][10], int zoomFactor) {

	double **newArr;
	int i = 0, j = 0;
	int rowIndex1 = 0;
	int rowIndex2 = 0;
	int columnIndex1 = 0;
	int columnIndex2 = 0;
	double a = 0.0, b = 0.0;
	double x = 0.0, y = 0.0;

	newArr = calloc(10*zoomFactor, sizeof(double *));
	for(i = 0; i < 10*zoomFactor; ++i)  
		newArr[i] =  calloc(10*zoomFactor, sizeof(double));

	for (i = 0; i < 10*zoomFactor; ++i) {

		for (j = 0; j < 10*zoomFactor; ++j) {

			rowIndex1 = floor((double)i/zoomFactor);
			columnIndex1 = floor((double)j/zoomFactor);
			
			rowIndex2 = ceil((double)i/zoomFactor);
			columnIndex2 = ceil((double)i/zoomFactor);

			a = (double)j/zoomFactor - floor((double)j/zoomFactor);
			b = (double)i/zoomFactor - floor((double)i/zoomFactor);


			if (rowIndex2 > 9 && columnIndex2 > 9)
				newArr[i][j] = arr[rowIndex1][columnIndex1];
			else if (rowIndex2 > 9 && columnIndex2 <= 9)
				newArr[i][j] = (1-a)*(1-b)*arr[rowIndex1][columnIndex1] + a*(1-b)*arr[rowIndex1][columnIndex2];
			else if (rowIndex2 <= 9 && columnIndex2 > 9)
				newArr[i][j] = (1-a)*(1-b)*arr[rowIndex1][columnIndex1] + (1-a)*b*arr[rowIndex2][columnIndex1];
			else
				newArr[i][j] = (1-a)*(1-b)*arr[rowIndex1][columnIndex1] + a*(1-b)*arr[rowIndex1][columnIndex2] + (1-a)*b*arr[rowIndex2][columnIndex1] + a*b*arr[rowIndex2][columnIndex2];
		}
	}
	return newArr;
}

