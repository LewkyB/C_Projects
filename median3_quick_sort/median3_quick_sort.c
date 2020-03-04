#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

int partition(int arr[], int N, int start, int end);
void quicksort(int arr[], int N, int start, int end);
void swap (int *x, int *y);
int median(int arr[], int start, int end);

int main(int argc, char* argv[])
{

    char buffer[BUFFER_SIZE];
    int *numArray;
    unsigned int n; 
    int i;

    while ((fscanf(stdin, "%d", &n)) > 0) /*get first number in stdin*/
    {
        fgets(buffer, BUFFER_SIZE, stdin); /*remove '\n' from size of array line*/
        numArray = malloc(n * sizeof(numArray));

        while(fgets(buffer, BUFFER_SIZE, stdin))
        {
            printf("Loaded new array:\nIndexes:\n");
            for (i = 0; i < n; i++)
            {
                printf("   %d,",i);
            }
            char* input = buffer;
            int counter = 0; 
            int number;
            int bytesread;
            while(sscanf(input, "%d%n", &number, &bytesread) > 0)
            {
                numArray[counter++] = number;
                input += bytesread;
            }

            printf("\nOriginal array:\n");
            for (i = 0; i < n; i++)
            {
                printf("   %d,",numArray[i]);
            }
            printf("\n");

            quicksort(numArray,n-1, 0, n-1);

            printf("Sorted array:\n");
            for (i = 0; i < n; i++)
            {
                printf("   %d,",numArray[i]);
            }
            printf("\n\n");
            free(numArray);
            break;
        }
    }
    return 0;
}

int partition(int arr[], int N, int start, int end)
{
    int i;
    printf("start of partition(A, N, %d, %d)\n", start, end);

    int median_index = median(arr, start, end);
    for (i = 0; i <= N; i++)
    {
        if(i >= start && i<=end)
        {
            printf("%4d,", arr[i]);
        }
        else
        {
            printf("%5c",',');
        }
    }
    printf("  A[%d]=%d,  A[%d]=%d,  A[%d]=%d\n", start, arr[start], median_index,arr[median_index], end, arr[end]);

    swap(&arr[median_index], &arr[end]);

    int pivot = arr[end]; 

    for (i = 0; i <= N; i++)
    {
        if(i >= start && i<=end)
        {
            printf("%4d,", arr[i]);
        }
        else
        {
            printf("%5c",',');
        }
    }
    printf("  <- updated pivot: %d\n", pivot);
    
    int partitionIndex = start;
    
    for (i = start; i < end; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(&arr[partitionIndex], &arr[i]);
            partitionIndex++;
        }
    }
    
    swap(&arr[partitionIndex], &arr[end]);

    for (i = 0; i <= N; i++)
    {
        if(i >= start && i<=end)
        {
            printf("%4d,", arr[i]);
        }
        else
        {
            printf("%5c",',');
        }
    }
    printf("  <- partitioned array around pivot %d, at final index %d,\n", pivot, partitionIndex);
    printf("  end of partition(A, N, %d, %d)\n", start, end);
    return partitionIndex;
}

void quicksort(int arr[], int N, int start, int end)
{
    if(start < end)
    {
        int partitionIndex = partition(arr,N,start,end);
        quicksort(arr, N, start, partitionIndex-1);
        quicksort(arr, N, partitionIndex+1, end);
    }
}

void swap (int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int median(int arr[], int start, int end)
{
    int middle = (start + end) / 2;

    if ((arr[middle] >= arr[start] && arr[middle] <= arr[end]) || (arr[middle] <= arr[start] && arr[middle] >= arr[end]))
    {
        return middle;
    }
    if ((arr[start] >= arr[middle] && arr[start] <= arr[end]) || (arr[start] <= arr[middle] && arr[end] >= arr[middle]))
    {
        return start;
    }
    if ((arr[end] >= arr[start] && arr[end] <= arr[middle]) || (arr[end] <= arr[start] && arr[end] >= arr[middle]))
    {
        return end;
    }
    return 0;
}
