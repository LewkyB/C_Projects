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
void swap(char *x, char *y);
void sort(wordStruct *words, int size);

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
	sort(words, i);	//sorts the characters in each string of sorted member in alphabetical order 	

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

void swap(char *x, char *y)
{
	char temp = *x;
	*x = *y;
	*y = temp;
}

void sort(wordStruct *words, int size)
{
	for (int i = 0; i < size; i++)
	{	
		//set length to length of word[i].sorted while also removing one for the 
		//null char at the end of the string
		int length = strlen(words[i].sorted)-1;  	
		
		for (int j = 0; j < length; j++)
		{
			int min_index = j; //start min_index at beginning of string
			for (int k = j+1; k < length + 1; k++)
			{
				//compares the min_index to all the chars in the string
				//and if it finds a character that is lower it will 
				//change the min_index to that char
				if (words[i].sorted[k] < words[i].sorted[min_index])
				{
					min_index = k;
				}
			}
			//when innermost loop finishes going through all the chars
			//and finds the lowest char it will swap it to the very front
			swap(&words[i].sorted[min_index], &words[i].sorted[j]);	
		}
	}
}






