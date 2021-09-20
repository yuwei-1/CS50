# Introduction to cryptography - scrambling an input from the user, given a key, that contains all 26 characters in the alphabet

#include <ctype.h> // library for checking data types
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h> // library used here for rounding


// prototyping all functions

int check_cipher(string cipher);
int check_upper(char letter);
int check_unique(string argv);
void translate(string argv, string plaintext);


// converts messages into ciphertext using user provided key and deals with error handling

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("You did not type a singular argument!");
        return 1;
    }

    else if (check_cipher(argv[1]) == 0)
    {
        printf("Error, you did not type a valid key!");
        return 1;
    }
    
    string plaintext = get_string("plaintext: ");
    
    translate(argv[1], plaintext);
    
    return 0;

}


// Checks if the user's key satisfies all conditions

int check_cipher(string cipher)
{
    int displace;
    
    
    if (strlen(cipher) == 26)
    {

        for (int i = 0; i < 26; i++)
        {
            char curr = cipher[i];
            
            if (isalpha(curr) == 0)
            {
                return 0;
            }
        }

        if (check_unique(cipher) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
            
    }
    
    else
    {
        return 0;
    }
}

// Checking the key user provided contains all 26 characters of alphabet

int check_unique(string argv)
{
    
    for (int i = 0, n = strlen(argv); i < n; i++)
    {
        int check_list[2];
        
        if (check_upper(argv[i]))
        {
            check_list[0] = argv[i];
            check_list[1] = argv[i] + 32;
        }
        else
        {
            check_list[0] = argv[i];
            check_list[1] = argv[i] - 32;
        }
        
        for (int j = 0; j < n; j++)
        {
            if ((argv[j] == check_list[0] || argv[j] == check_list[1]) && i != j)
            {
                return 0;
            }
        }
    }
    
    return 1;
}


// Returns 1 if character is upper case, 0 if lower case

int check_upper(char letter)
{
    if (isupper(letter))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// converts any message from user into ciphertext using their provided key

void translate(string argv, string plaintext)
{
    printf("ciphertext: ");
    
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char new_char;
        char curr = plaintext[i];
        
        if (isalpha(curr) == 0)
        {
            printf("%c", curr);
        }
        
        else if (check_upper(curr))
        {
            new_char = argv[curr - 65];
            
            if (isupper(new_char) == 0)
            {
                new_char -= 32;
            }
            printf("%c", new_char);
        }
        else
        {
            new_char = argv[curr - 97];
            
            if (isupper(new_char))
            {
                new_char += 32;
            }
            
            printf("%c", new_char);
        }
        
    }
    
    printf("\n");
}
