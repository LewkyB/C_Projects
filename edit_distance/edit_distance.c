//Luke Brown 1001450626 CSE2320 Stefan Fall 2019
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "edit_distance.h"

//helper functions
int min(int x, int y, int z);
void buildArray(int width, int height, int array[][height]);
void printArray(int width, int height, int array[][height], char *str1, char *str2);
int** calcArray(int width, int height, int array[][height], char *str1, char *str2);


/*  Suggestions
    - When you work with 2D arrays, be careful. Either manage the memory yourself, or
    work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
    they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/
 */

int edit_distance(char * first_string, char * second_string, int print_table){

    int strlen1 = strlen(first_string);
    int strlen2 = strlen(second_string);
    int editdistance;
    int arr[strlen1+1][strlen2+1];
    
    buildArray(strlen1+1, strlen2+1, arr);
    calcArray(strlen1+1, strlen2+1, arr, first_string, second_string);
    
    
    if (print_table == 1)
    {
        printArray(strlen1+1, strlen2+1, arr, first_string, second_string);
        printf("\n");
    }
    
    editdistance = arr[strlen1][strlen2]; //edit distance is bottom right element in 2d array
    
    return editdistance;

}

void spellcheck(char * dictname, char * testname){	

    //variables
    char buffer[100]; //longest possible string is 100 char
    int dictSize, testSize, n, number, smallest, counter;
    
    //file pointers
    FILE *dictFile, *testFile;
    
    //open files
    dictFile = fopen(dictname, "r");
    testFile = fopen(testname, "r");

    //close if files empty or not present
    if (dictFile == NULL || testFile == NULL)
    {
        printf("Error with files.\n");
        exit(1);
    }

    //read first line of both files to get sizes
    fscanf(dictFile, "%d", &dictSize);
    fscanf(testFile, "%d", &testSize);

    //pointers for holding words
    char **dictWords;
    char **testWords;

    //allocate memory to 2d pointers
    dictWords = malloc(dictSize * sizeof(char *));
    testWords = malloc(testSize * sizeof(char *));
    
    //reset counter and load in test words
    counter = 0;
    while(fscanf(testFile, "%s", &buffer) != EOF)
    {
        testWords[counter] = malloc(strlen(buffer) + 1);
        strncpy(testWords[counter], buffer, strlen(buffer)+1);
        counter++;
    }

    //reset counter and load in dictionary words
    counter = 0;
    while(fscanf(dictFile, "%s", &buffer) != EOF)
    {
        dictWords[counter] = malloc(strlen(buffer) + 1);
        strncpy(dictWords[counter], buffer, strlen(buffer)+1);
        counter++;
    }
    
    //loops for finding smallest minimum distance and printing all words with minimum distance
    for(counter = 0; counter < testSize; counter++)
    {
        printf("\n------- Current test word: %s\n", testWords[counter]);
        smallest = strlen(testWords[counter]); //set initial smallest distance to length of string
        
        //loop for finding the smallest minimum distance
        for (n = 0; n < dictSize; n++)
        {
            number = edit_distance(testWords[counter], dictWords[n], 0);
            if (number < smallest)
            {
                smallest = number;
            }
        }

        printf("Minimum distance: %d\n", smallest);
        printf("Words that give minimum distance:\n");
        
        //loop to print strings with same minimum distance
        for (n = 0; n < dictSize; n++)
        {
            if (edit_distance(testWords[counter], dictWords[n], 0) == smallest)
            {
                printf("%s\n", dictWords[n]);
            }
        }
    }

    //close files
    fclose(dictFile);
    fclose(testFile);

    //free memory
    for (counter = 0; counter < dictSize;counter++)
    {
        free(dictWords[counter]);
    }
    free(dictWords);
    for (counter = 0; counter < testSize;counter++)
    {
        free(testWords[counter]);
    }
    free(testWords);
}

void buildArray(int width, int height, int array[][height])
{
    int i, j;
    int rowIncrement = 0;
    int columnIncrement = 0;

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            array[i][j] = 0;
            if (i == 0)
            {
                array[i][j] = rowIncrement;
                rowIncrement++;
            }
        }
        array[i][0] = columnIncrement;
        columnIncrement++;
    }
}

int** calcArray(int width, int height, int array[][height], char *str1, char *str2)
{
    int i, j, subCost;
    
    for (i = 1; i < width; i++)
    {
        for (j = 1; j < height; j++)
        {
            if(str1[i-1] == str2[j-1])
            {
                subCost = 0;
            }
            else
            {
                subCost = 1;
            }
            array[i][j] = min(array[i-1][j] + 1, array[i][j-1] +1, array[i-1][j-1] + subCost);
        }
    }
    return array;
}

void printArray(int width, int height, int array[][height], char *str1, char *str2)
{
    int i, j, k;
    int hyphens = 7 + (4*strlen(str2)); //amount of hyphens to print on dividing lines
    printf("%3c%4c",'|','|'); //first 2 blank squares in upper left corner of array print out
    
    //prints string into to row
    for(i=0; i<height-1;i++)
    {
        printf("%3c|", str2[i]);
    }
    printf("\n");
    
    //prints dividing lines
    for(k=0; k < hyphens; k++)
    {
        printf("-");
    }
    printf("\n");
    printf("%3c",'|'); //prints blank square out in 2nd row to far right
    
    //prints out array with formatting and first string in the first elements of each row 
    for (i = 0; i < width; i++)
    {
        if (i != 0)
        {
            printf("%2c|",str1[i-1]);
        }

        for (j = 0; j < height; j++)
        {

            printf("%3d|", array[i][j]);
        }
        printf("\n");
 
        for(k=0; k < hyphens; k++)
        {
            printf("-");
        }
        printf("\n");
    }

}

//helper function for finding the minimum value
int min(int x, int y, int z)
{
    if (x < y && x < z)
    {
        return x;
    }
    else if (y < z)
    {
        return y;
    }
    else
    {
        return z;
    }
}
