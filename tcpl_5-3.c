/* Exercise 5.3. 
 * Write a pointer version of the function strcat that we showed in Chapter 2:
 * strcat(s, t) copies the string t to the end of s.
 */

#include <stdio.h>

char* strcat(char* dest, const char* src)
{
	for (; *dest != '\0'; dest++)
		{}
	
	for (; *src != '\0'; src++, dest++)
		*dest = *src;
	*dest = '\0';

	return dest;
}

int main(void)
{
	char s1[14] = "Hello, ";
	char s2[] = "world!";
	strcat(s1, s2);
	printf("%s\n", s1);
	return 0;
}
