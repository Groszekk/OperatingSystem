#include "screen.h"

static unsigned int newline_counter;

void print(char* string)
{
    short* VGA = (short*)ADDR;
    unsigned int lenght = 0;
    unsigned int counter = 0;
    unsigned char new_line = 0;
    const short color = WHITE_ON_BLACK;

    while(string[counter] != '\0')
    {
        if(string[counter] == '\n')
        {
            new_line = 1;
            lenght--;
            newline_counter++;
        }

        lenght++;
        counter++;
    }

    for (unsigned int i = 0; i < lenght; i++)
    {
        if(new_line == 0)
            VGA[i] = color | string[i];
        else
            VGA[i + 80 * newline_counter] = color | string[i];
    }
}