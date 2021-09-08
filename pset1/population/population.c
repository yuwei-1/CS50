
// This is the code that approximates the amount of years it takes for a population of llamas
// to reach a certain population size.

#include <stdio.h>
#include <cs50.h>


// Declaring any functions

int calc_no_of_years(int num1, int num2);



int main(void)
{
    // Prompt for start size
    
    int answer1;
    int answer2;
    
    do
    {
        answer1 = get_int("What is the starting population? :");
    }
    while (answer1 < 9);
    

    // Prompt for end size
    
    do
    {
        answer2 = get_int("What is the end population? :");
    }
    while (answer2 < answer1);
    

    // Calculate number of years until we reach threshold
    
    int response = calc_no_of_years(answer1, answer2);

    // Print number of years
    
    
    
    printf("Years: %i", response);
}


int calc_no_of_years(int num1, int num2)
{
    
    int count = 0;
    
    while (num1 < num2)
    {
        num1 += num1/3 - num1/4;
        count++;
    }
    
    return count;
}
