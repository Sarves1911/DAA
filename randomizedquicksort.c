#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int low, int high, int **swapsMatrix)
{
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low;           // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot)
        {
            i++; // Increment the index of the smaller element
            swap(&arr[i], &arr[j]);
            swapsMatrix[i][j] = 1;
            swapsMatrix[j][i] = 1;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    swapsMatrix[i + 1][high] = 1;
    swapsMatrix[high][i + 1] = 1; // Symmetry
    return (i + 1);
}

// Function to perform QuickSort
void quickSort(int arr[], int low, int high, int **swapsMatrix)
{
    if (low < high)
    {
        // Generate a random pivot and swap it with the last element
        srand(time(NULL));
        int random = low + rand() % (high - low + 1);
        swap(&arr[random], &arr[high]);

        // Partition the array and get the pivot index
        int pivot_index = partition(arr, low, high, swapsMatrix);

        // Recursively sort elements before and after the pivot
        quickSort(arr, low, pivot_index - 1, swapsMatrix);
        quickSort(arr, pivot_index + 1, high, swapsMatrix);
    }
}

// Function to print the array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printSwapsMatrix(int size, int **swapsMatrix)
{
    printf("Swaps Matrix:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
                printf("0 ");
            else
                printf("%d ", swapsMatrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    int **swapsMatrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        swapsMatrix[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++)
        {
            swapsMatrix[i][j] = 0;
        }
    }

    printf("Unsorted array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1, swapsMatrix);

    printf("Sorted array: \n");
    printArray(arr, n);

    printSwapsMatrix(n, swapsMatrix);

    // Clean up dynamically allocated memory
    for (int i = 0; i < n; i++)
    {
        free(swapsMatrix[i]);
    }
    free(swapsMatrix);

    return 0;
}
