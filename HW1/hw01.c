#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



double f(double x) {

	return pow(x, 2) - 4*x + 4 - log(x);
}



double bisectionMethod(double a, double b, char *stopCriteria, double epsilon);


int main(int argc, char *argv[]) {
	

	if (argc != 5) {
		fprintf(stderr, "Usage: %s startInterval endInterval stopCriteria epsilon\n",argv[0]);
		return 1;
	}
     
    if (bisectionMethod(atof(argv[1]),atof(argv[2]),argv[3],atof(argv[4])) == -1)
    	return 1;

	return 0; 
}



double bisectionMethod(double a, double b, char *stopCriteria, double epsilon) {

	double middle;
	double oldMiddle;
	double relativeError;
	double absoluteError;
	double distanceToRoot;
	double temp = epsilon;
	int counter = 0;
	int i = 1;
	int teoIteration;


	teoIteration = ceil(((-1)*log10(epsilon/(b-a)))/log10(2));
	fprintf(stdout,"Exercise D for Interval [%.2f, %.2f] Epsilon =  %f Stopping Criteria type = %s \n\n", a, b, epsilon, stopCriteria);

	if (a >= b) {
		fprintf(stderr, "Third Arguman is bigger than second arguman\n");
		return -1;
	}
	if (strcmp(stopCriteria,"DISTANCE_TO_ROOT") != 0 && strcmp(stopCriteria,"ABSOLUTE_ERROR") != 0 && strcmp(stopCriteria,"RELATIVE_ERROR") != 0) {
		fprintf(stderr, "You entered stopping criteria incorrectly\n");
		return -1;
	}
	oldMiddle = a;
	middle = (a + b)/2.0;
	relativeError = fabs(middle - oldMiddle)/fabs(middle);
	absoluteError = fabs(middle - oldMiddle);
	distanceToRoot = fabs(f(middle));
	fprintf(stdout,"|Iter |Absolute Error   |Relative Error   |\n");
	if (strcmp(stopCriteria,"DISTANCE_TO_ROOT") == 0) {
		while (distanceToRoot > epsilon && i < 101) {
			fprintf(stdout,"|-----------------------------------------|\n");
			fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);

			if ((f(middle) * f(a)) > 0)
				a = middle;
			else if ((f(middle) * f(a)) < 0)
				b = middle;

			oldMiddle = middle;
			middle = (a + b)/2.0;
			relativeError = fabs(middle - oldMiddle)/fabs(middle);
			absoluteError = fabs(middle - oldMiddle);
			distanceToRoot = fabs(f(middle));
			i++;
		}
		fprintf(stdout,"|-----------------------------------------|\n");
		fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);
	}
	else if (strcmp(stopCriteria,"ABSOLUTE_ERROR") == 0) {
		while (absoluteError > epsilon && i < 101) {
			fprintf(stdout,"|-----------------------------------------|\n");
			fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);

			if ((f(middle) * f(a)) > 0)
				a = middle;
			else if ((f(middle) * f(a)) < 0)
				b = middle;

			oldMiddle = middle;
			middle = (a + b)/2.0;
			relativeError = fabs(middle - oldMiddle)/fabs(middle);
			absoluteError = fabs(middle - oldMiddle);
			distanceToRoot = fabs(f(middle));
			i++;
		}
		fprintf(stdout,"|-----------------------------------------|\n");
		fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);
	}
	else if (strcmp(stopCriteria,"RELATIVE_ERROR") == 0) {
		while (relativeError > epsilon && i < 101) {
			fprintf(stdout,"|-----------------------------------------|\n");
			fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);

			if ((f(middle) * f(a)) > 0)
				a = middle;
			else if ((f(middle) * f(a)) < 0)
				b = middle;

			oldMiddle = middle;
			middle = (a + b)/2.0;
			relativeError = fabs(middle - oldMiddle)/fabs(middle);
			absoluteError = fabs(middle - oldMiddle);
			distanceToRoot = fabs(f(middle));
			i++;
		}
		fprintf(stdout,"|-----------------------------------------|\n");
		fprintf(stdout,"|%-5d|%1.15f|%1.15f|\n", i, absoluteError, relativeError);
		

	}

	if (i > 100) {
		fprintf(stderr, "The tolerance value is not reached after 100 iterations\n");
		return -1;
	}
	fprintf(stdout,"|-----------------------------------------|\n");
	fprintf(stdout,"Approximate Root = %f\n", middle);
	fprintf(stdout,"Number of iterations that have been executed = %d\n", i);
	fprintf(stdout,"Theoretically required number of iterations = %d\n\n\n", teoIteration);

	return 1;
}