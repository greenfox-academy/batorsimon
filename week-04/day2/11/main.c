#include <stdio.h>
#include <stdlib.h>

void calc(int a, int b, int *p_sum, int *p_mul);

int main()
{
	int x, y;
	x = 5;
	y = 8;

	int sum, mul;

	//TODO: write a void function which calculates the sum and multiplication of x and y according to the function prototype.
	//Use 'output parameters'. Print out these values.


    calc(x, y, &sum, &mul);
    printf("sum of x and y: %d and multiplicated: %d\n", sum, mul);

	return 0;
}

void calc(int a, int b, int *p_sum, int *p_mul)
{
    *p_sum = a + b;
    *p_mul = a * b;
}
