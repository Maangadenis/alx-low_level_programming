#include <stdio.h>
#include "main.h"

/**
 * main - print the first 98 fibonacci numbers.
 *
 * Return: Nothing.
 */

int main(void)
{
	int count;
	unsigned long x, y, z, a, b, c, carry;

	x = 0;
	y = 1;

	for (count = 1; count <= 90; count++)
	{
		z = x + y;
		x = y;
		y = z;
		printf("%lu, ", z);
	}

	a = x % 1000;
	x = x / 1000;
	b = y % 1000;
	y = y / 1000;

	while (count <= 98)
	{
		carry = (a + b) / 1000;
		c = (a + b) - carry * 1000;
		z = (x + y) + carry;
		x = y;
		y = z;
		a = b;
		b = c;

		if (c >= 100)
			printf("%lu%lu", z, c);
		else
			printf("%lu0%lu", z, c);
		if (count < 98)
			printf(", ");
		count++;
	}
	putchar('\n');
	return (0);
}
