#include <stdio.h>
#include <stdlib.h>

//create a program to print ASCII values of all characters.
/*your output should be something like this:
ASCII value of character 8 = 56
ASCII value of character 9 = 57
ASCII value of character : = 58
ASCII value of character ; = 59
ASCII value of character < = 60
ASCII value of character = = 61
ASCII value of character > = 62
ASCII value of character ? = 63
ASCII value of character @ = 64
ASCII value of character A = 65
ASCII value of character B = 66
*/

int main()
{
    int b=33;
    char a=0;

    for(a = '!'; a <= '~'; a++){
            printf("ASCII value of character %c = %d\n", a, b);
            b++;

    }

    return 0;

}
