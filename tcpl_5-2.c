/* Exercise 5-2. 
 * Write getfloat, the floating-point analog of getint.
 * What type does getfloat return as its function value?
 * 
 * getint accepts one parameter - pointer to some integer variable.
 * It reads next integer from input and stores it in this variable.
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

int getch(void)
{
	return getchar();
}

int ungetch(char c)
{
	return ungetc(c, stdin);
}

int getfloat(double *var)
{
	int c, next_char, sign;
	unsigned int point_flag, power;

	while (isspace((c = getch())))
		{}
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c); /* it is not a number */
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	
	if (c == '+' || c == '-') {
		next_char = getch();
		if (!isdigit(next_char)) {
			ungetch(next_char);
			ungetch(c);
			return 0;
		}
		c = next_char;
	}


	point_flag = 0;
	power = 1;
	for (*var = 0; isdigit(c) || c == '.'; c = getch()) {
		if (c == '.') {
			point_flag = 1;
			c = getch();
		}
		
		if (point_flag == 1 && c != '.') {
			*var += (c - '0') / pow(10.0, power);
			power += 1;
		} else if (point_flag == 1 && c == '.') {
			return 0;
		} else {
			*var = 10 * (*var) + (c - '0');
		}
	}
	*var *= sign;
	
	if (c != EOF)
		ungetch(c);
	
	return 1;
}

int main(void)
{
	double var;
	printf("Enter some floating-point value:\n");
	if (getfloat(&var) == 0)
		printf("Input is not a float\n");
	else
		printf("%g\n", var);
	return 0;
}
