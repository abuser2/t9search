#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*crutch*/
/*if you close the program, you can do without it*/
#define MAX_INPUT 999
/*maximum string length*/
#define MAX_STRING 100

bool check(int index, char symbol);
bool search(char string[], char search[]);
void print_contact(char name[],char phone[]);
bool invalid_data(char name[], char phone[]);

/*initial search results*/
bool NOT_FOUND = true;

int main(int argc, char *argv[])
{
    /*name and number initialization*/
    char name[MAX_INPUT], phone[MAX_INPUT];
    /*checking for valid input*/
    if(argc > 2)
    {
        printf("Invalid input\n");
        return -1;
    }
    else if(argc == 1)
    {
        /*input and output of all values*/
        while(fgets(name, MAX_INPUT, stdin)
              && fgets(phone, MAX_INPUT, stdin))
        {
                print_contact(name, phone);
        }
        return 0;
    }
    else
    {
        while(fgets(name, MAX_INPUT, stdin)
              && fgets(phone, MAX_INPUT, stdin))
        {
            /*search for characters in a name*/
            if(search(name, argv[1]))
            {
                print_contact(name, phone);
            }
            /*search for characters in a number*/
            else if(search(phone, argv[1]))
            {
                print_contact(name, phone);
            }
        }
    }
    /*error output if no contacts matching the criteria were found*/
    if(NOT_FOUND)
    {
        printf("Not Found\n");
        return -1;
    }
    return 0;
}

bool check(int index, char symbol)
{
    /*character search array*/
    char symbolMap[10][9] = {
        {'0', '+'},
        {'1'},
        {'2', 'A', 'a', 'B', 'b', 'C', 'c'},
        {'3', 'D', 'd', 'E', 'e', 'F', 'f'},
        {'4', 'G', 'g', 'H', 'h', 'I', 'i'},
        {'5', 'J', 'j', 'K', 'k', 'L', 'l'},
        {'6', 'M', 'm', 'N', 'n', 'O', 'o'},
        {'7', 'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's'},
        {'8', 'T', 't', 'U', 'u', 'V', 'v'},
        {'9', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'}
    };
    /*checking each character with an array string*/
    for (int i = 0; i < 9; i++)
    {
        /*index in ascii format of the table, so in subtract 48*/
        if (symbolMap[index - 48][i] == symbol)
            return true;
    }
    return false;
}
bool search(char string[], char search[])
{
    /*initializing the length of the name or number of the contact
    and the length of the search string*/
    int lString = strlen(string), lSearch = strlen(search);
    for(int i = 0; i < (lString - lSearch + 1); i++)
    {
        /*checking first search number with character*/
        if(check(search[0], string[i]))
        {
            int pointers = 1;
            while(lSearch > pointers)
            {
                /*checking the second and further numbers
                 with the next character*/
                if(check(search[pointers], string[i+pointers]))
                    pointers++;
                else
                    break;
            }
            /*control*/
            if((pointers) == lSearch)
            {
                /*found at least 1 contact*/
                NOT_FOUND = false;
                return true;
            }
        }
    }
    return false;
}
void print_contact(char name[],char phone[])
{
    /*control valid input*/
    if(invalid_data(name, phone)){
        printf("Invalid data: ");
    }
    /*normal contact output*/
    name[strlen(name) - 1] = '\0';
    phone[strlen(phone) - 1] = '\0';
    printf("%s, %s\n", name, phone);
}


bool invalid_data(char name[], char phone[])
{
    /*checking for input length*/
    if(strlen(name) > MAX_STRING || strlen(phone) > MAX_STRING)
        return true;

    for(int i = 0; i < (int)strlen(phone) - 1; i++)
    {
        /*number check*/
        if(!((int)phone[i] >= '0' && (int)phone[i] <= '9'))
            return true;
    }

    return false;
}
