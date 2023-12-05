#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int swapsMatrix[][7])
{
    int pivot = arr[low];
    int i = low;

    for (int j = low + 1; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
            swapsMatrix[i][j] = 1; // Mark the swap in the matrix
            swapsMatrix[j][i] = 1; // Mark the swap in the matrix (symmetry)
        }
    }

    swap(&arr[low], &arr[i]);
    swapsMatrix[low][i] = 1; // Mark the swap in the matrix
    swapsMatrix[i][low] = 1; // Mark the swap in the matrix (symmetry)
    return i;
}

void quicksort(int arr[], int low, int high, int swapsMatrix[][7])
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high, swapsMatrix);
        quicksort(arr, low, pivotIndex - 1, swapsMatrix);
        quicksort(arr, pivotIndex + 1, high, swapsMatrix);
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printSwapsMatrix(int matrix[][7], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                printf("0 "); // Diagonal elements should be 0
            }
            else
            {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    int swapsMatrix[7][7] = {0}; // Initialize swaps matrix to zero
    quicksort(arr, 0, n - 1, swapsMatrix);

    printf("Sorted array: ");
    printArray(arr, n);

    printf("Swaps matrix:\n");
    printSwapsMatrix(swapsMatrix, n);

    return 0;
}
