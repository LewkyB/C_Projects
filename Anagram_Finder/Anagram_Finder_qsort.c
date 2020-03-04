#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 400000 //allows for up to 400000 strings to be compared

typedef struct
{
	char *word;
	char *sorted;
} wordStruct;

//allocate size of words structure and sets both members in the structure
//to null 
wordStruct words[MAXSIZE] = { {NULL, NULL} }; 

//declare functions in preprocessor
int compare(const void *ptr1, const void *ptr2);

int main()
{
	char input[1024]; //size of this allows for up to 1024 character string
	int i = 0; //used as variable to keep track of number of rows in each struct 
	while(scanf("%s", input) != EOF)
	{
		if (strcmp(input, "-1") == 0) //if input is -1 it will stop reading from file
		{
			break;
		}
		//allocate memory for both members in wordStruct
		words[i].word = (char *) malloc((strlen(input)) * sizeof(char *));
		words[i].sorted = (char *) malloc((strlen(input)) * sizeof(char *));
		//copy word from input into both members of wordStruct
		strcpy(words[i].word, input);
		strcpy(words[i].sorted, input);
		i++; //each time it reads a line it adds to i to keep track of array size
	}
	for (int z=0; z < i; z++)
	{
		qsort(words[z].sorted, strlen(words[z].sorted), sizeof(char), compare);
	}
	int anagramCounter = 0; //used to keep track of number of anagrams
	
	//these loops compare one word to the rest of the words in words.sorted
	//and when they have a match they will print out the unsorted version of 
	//the words
	
	for (int m = 0; m < i; m++)
	{
		for (int n = m + 1; n < i; n++)
		{
			if (strcmp(words[m].sorted, words[n].sorted) == 0)
			{
				printf("%s %s\n", words[m].word, words[n].word);
				anagramCounter++;
			}
		}
	}
	printf("\nFound %d anagrams.\n", anagramCounter);
	
	//free memory that was allocated
	free(words->word);
	free(words->sorted);
}

int compare(const void *ptr1, const void *ptr2)
{
	return *(char*)ptr1 - *(char*)ptr2;
}






