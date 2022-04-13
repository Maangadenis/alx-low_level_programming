#include "3-calc.h"
#include <stdlib.h>
#include <stdio.h>
/**
  * main - entry point
  * @argc: # of args
  * @argv: array of pointers to names of args
  * Return: 0
  */
int main(int argc, char **argv)
{
	/* input checking */
	if (argc != 4)
	{
		printf("Error\n");
		exit(98);
	}
	if ((*argv[2] == '/' || *argv[2] == '%') && atoi(argv[3]) == 0)
	{
		printf("Error\n");
		exit(100);
	}
	/* calling get_op_func with arguments */
	printf("%d\n", get_op_func(argv[2])(atoi(argv[1]), atoi(argv[3])));
	return (0);
}
