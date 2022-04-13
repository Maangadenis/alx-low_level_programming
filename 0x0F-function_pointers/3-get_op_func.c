#include "3-calc.h"
#include <stdlib.h>
#include <stdio.h>
/**
  * get_op_func - choosing the right func for the operator
  * @s: the operator
  *
  * Return: result of function or error
  */
int (*get_op_func(char *s))(int, int)
{
	/* declarations */
	op_t ops[] = {
	{"+", op_add},
	{"-", op_sub},
	{"*", op_mul},
	{"/", op_div},
	{"%", op_mod},
	{NULL, NULL}
	};
	int i;
	/* matches operator to function */
	i = 0;
	while (ops[i].op)
	{
		if (ops[i].op[0] == *s && s[1] == '\0')
			return (ops[i].f);
		i++;
	}
	/* bad operator, print error */
	printf("Error\n");
	exit(99);
}
