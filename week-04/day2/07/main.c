#include <stdio.h>
#include <stdlib.h>

int main()
{
    int high_number = 6655;
    int low_number = 2;

    int* hight_number_pointer = &low_number;
    int* low_number_pointer = &high_number;
    //TODO:
    // Please fix the problem and swap where the pointers point,
    // without using the "&" operator.


    int *a = hight_number_pointer;
    hight_number_pointer = low_number_pointer;
    low_number_pointer = a;

    printf("High number pointer: %d.\n", *hight_number_pointer);
    printf("Low number pointer: %d.\n", *low_number_pointer);
    printf("a pointer: %d.\n", *a);
    return 0;
}
