/* Exercise 5-10. 
 * Write the program expr, which evaluates a reverse Polish expression from the command line, 
 * where each operator or operand is a separate argument. For example, 
 * 	expr 2 3 4 + '*'
 * evaluates to 2 * (3 + 4).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	FALSE,
	TRUE,
} BOOL;

enum { NUMBER = -1, STACK_SIZE = 3 };

int stack[STACK_SIZE];
int stack_top = 0;

void stack_push(int value)
{
	if (stack_top >= STACK_SIZE) {
		printf("Stack overflow\n");
	} else {
		stack[stack_top] = value;
		stack_top++;
	}
}

int stack_pop()
{
	if (stack_top <= 0) {
		printf("Stack is empty\n");
		return 0;
	} else {
		--stack_top;
		return stack[stack_top];
	}
}

BOOL is_number(char* token)
{
	unsigned int token_length = strlen(token);
	unsigned int current_char = 0;

	if (token[current_char] == '-' && token_length > 1)
		current_char++;

	for (; current_char < token_length; current_char++)
		if (!(token[current_char] >= '0' && token[current_char] <= '9'))
			return FALSE;
	
	return TRUE;
}

int conv_to_number(char* token)
{
	int result = 0;
	char sign = 1;
	unsigned int token_length = strlen(token);
	unsigned int current_char = 0;

	if (token[current_char] == '-') {
		sign = -1;
		current_char++;
	}

	for (; current_char < token_length; current_char++) {
		result *= 10;
		result += (int)(token[current_char] - '0');
	}

	return result * sign;
}

int main(int argc, char* argv[])
{
	if (argc < 4) {
		printf("Usage: expr *numeric expression in reverse polish notation*\n");
		return 1;
	}

	char current_token_type;
	int first_operand, second_operand;

	for (int i = 1; i < argc; i++) {
		current_token_type = is_number(argv[i]) == TRUE ? NUMBER : *(argv[i]);
		switch (current_token_type) {
		case NUMBER:
			stack_push(conv_to_number(argv[i]));
			break;
		case '+':
			stack_push(stack_pop() + stack_pop());
			break;
		case '-':
			second_operand = stack_pop();
			first_operand = stack_pop();
			stack_push(first_operand - second_operand);
			break;
		case '*':
			stack_push(stack_pop() * stack_pop());
			break;
		case '/':
			second_operand = stack_pop();
			first_operand = stack_pop();
			if (second_operand != 0) {
				stack_push(first_operand / second_operand);
			} else {
				printf("Division by zero\n");
				return 2;
			}
			break;
		default:
			printf("Illegal token: %s\n", argv[1]);
			return 3;
			break;
		}
	}
	printf("Result: %d\n", stack[0]);
	return 0;
}
