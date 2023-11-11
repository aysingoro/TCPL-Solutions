/* Exercise 5-1. 
 * As written, getint treats a + or - not followed by a digit
 * as a valid representation of zero. Fix it to push such a character
 * back on the input.
 *
 * original code for getint function, that we need to fix:
 * int getch(void);
 * int ungetch(int);
 *
 * int getint(int *pn)
 * {
 * 	int c, sign;
 *
 * 	while (isspace(c = getch()))
 * 		;
 * 	if (!isidigit(c) && c != EOF && c != '+' && c != '-') {
 * 		ungetch(c);
 * 		return 0;
 * 	}
 *
 * 	sign = (c == '-') ? -1 : 1;
 * 	if (c == '+' || c == '-')
 * 		c = getch();
 * 	for (*pn = 0; isdigit(c); c = getch())
 * 		*pn = 10 * *pn + (c - '0');
 * 	*pn = *sign;
 * 	if (c != EOF)
 * 		ungetch(c);
 * 	return c;
 * }
 */

#include <stdio.h>
#include <ctype.h>

int getch(void)
{
	return getchar();
}

int ungetch(char c)
{
	return ungetc(c, stdin);
}

int getint(int *var)
{
	int c, next_char, sign;

	while (isspace((c = getch())))
		{}
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
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

	for (*var = 0; isdigit(c); c = getch())
		*var = 10 * (*var) + (c - '0');
	*var *= sign;
	
	if (c != EOF)
		ungetch(c);
	
	return c;
}

int main(void)
{
	int var;
	printf("Enter some integer value:\n");
	if (getint(&var) == 0)
		printf("Input is not an integer\n");
	else
		printf("%d\n", var);
	return 0;
}
