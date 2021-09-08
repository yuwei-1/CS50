
// This code prints a pyramid of hashtags, in the style of the classic mario game

#include <stdio.h>
#include <cs50.h>


// Prototypes of functions here

void print_pyramid(int n);
void print_stuff(int quantity, string stuff);


// Get number of layers of pyramid from user, then call print_pyramid function

int main(void)
{
    int n;

    do
    {
        n = get_int("How many layers do you want? Please enter a integer from 1 to 8: ");
    }
    while (1 > n || n > 8);

    print_pyramid(n);

}

// Takes number of layers, and prints entire pyramid

void print_pyramid(int n)
{
    int spaces;


    for (int i = 1; i <= n; i++)
    {
        spaces = n - i;

        print_stuff(spaces, (string) " ");
        print_stuff(i, (string) "#");
        printf("  ");
        print_stuff(i, (string) "#");
        printf("\n");
    }
}


// prints individual rows

void print_stuff(int quantity, string stuff)
{
    for (int j = 0; j < quantity; j++)
    {
        printf("%s", stuff);
    }
}
