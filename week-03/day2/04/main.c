#include <stdio.h>
#include <stdlib.h>

int main()
{
    float val;
	char str[5];
	strcpy(str, "3.14");
	//TODO: print out the value of pi, first as a string, then a float value.
    val = atof(str);
	printf("The string value of 3.14 is %s is and the float value is %.4f.\n", str, val);
    return 0;
}
