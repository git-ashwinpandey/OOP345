/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Ashwin Pandey
Student ID#: 156027211
Email      : apandey21@myseneca.ca
Section    : NFF

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Get a valid integer from the user
int inputInt(void)
{
    int value;
    char newLine = 'x';
    int validInt = 1;


    while (validInt)
    {
        if (newLine == '\n')
        {
            validInt = 0;
        }
        else
        {
            //printf("Enter the number: ");
            scanf("%d%c", &value, &newLine);

            if (newLine != '\n')
            {
                clearInputBuffer();
                printf("Error! Input a whole number: ");
            }
        }
    }

    return value;
}

// Validates if inputInt is greater than 0
int inputIntPositive(void)
{
    int validInt = 1;
    int value;

    while (validInt)
    {
        value = inputInt();
        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
        else
        {
            validInt = 0;
        }
    }
    return value;
}

//Validates if an Integer is between two range
int inputIntRange(int lowerBound, int upperBound)
{
    int validInt = 1;
    int value;

    while (validInt)
    {
        value = inputInt();
        if (value >= lowerBound && value <= upperBound)
        {
            validInt = 0;
        }
        else
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    }
    return value;
}

// Validates user input char with list of valid characters
char inputCharOption(const char charArray[])
{
    char userInput[50];
    int validChar = 1, i;
    int charFound = 0, charLength;


    //stringLength = strlen(charArray);
  

    while (validChar)
    {
        scanf("%s", userInput);
        charLength = strlen(userInput);
        

        if (charLength != 1)
        {
            printf("ERROR: Character must be one of [%s]: ", charArray);
        }
        else
        {
            for (i = 0; i < strlen(charArray); i++)
            {
                if (charArray[i] == userInput[0])
                {
                    charFound++;
                }
            }

            if (charFound != 1)
            {
                printf("ERROR: Character must be one of [%s]: ", charArray);
            }
            else
            {
                validChar = 0;
            }
        }
        
    }
    
    return userInput[0];
}

//Get a string from the user within specified length
void inputCString(char * cString, int minChar, int maxChar)
{
    int stringLength, validString = 1;
    char userString[35];

    while (validString)
    {
        scanf(" %[^\n]", userString);

        // count the length of userString
        stringLength = strlen(userString);


        //Check whether the length of the string is between specified min and max value
        if (!(stringLength >= minChar && stringLength <= maxChar))
        {
            if (maxChar == minChar)
            {
                if (maxChar == 10 && minChar == 10)
                {
                    printf("Invalid %d-digit number! Number: ", maxChar);
                }
                else
                {
                    printf("ERROR: String length must be exactly %d chars: ", minChar);
                }

            }
            else if (stringLength < minChar)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
                validString = 1;
            }
            else if (stringLength > maxChar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
                validString = 1;
            }
            validString = 1;
        }
        
        else
        {
            strcpy(cString, userString);
            validString = 0;
        }
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


void displayFormattedPhone(const char * cString)
{
    int stringLength ,i , isDigit;
    isDigit = 0;
    if(cString!= NULL){
        stringLength = strlen(cString);

        for(i = 0; i<stringLength; i++)
        {
            if (isdigit(cString[i]))
            {
                isDigit++;
            }
        }
    }

    if (cString!= NULL && isDigit == 10)
    {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", cString[0], cString[1], cString[2], cString[3],
               cString[4], cString[5], cString[6], cString[7],
               cString[8], cString[9]);
    }
    else
    {
        printf("(___)___-____");
    }
}