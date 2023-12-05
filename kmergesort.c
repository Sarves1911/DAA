#include <stdio.h>
#include <stdlib.h>

void mergesort(int A[], int length)
{
    if (length < 2)
    {
        return;
    }
    else
    {
        int mid1 = length / 3;
        int mid2 = 2 * (length / 3);

        int left[mid1];
        int middle[mid2 - mid1];
        int right[length - mid2];

        for (int i = 0; i < mid1; i++)
        {
            left[i] = A[i];
        }

        for (int i = mid1; i < mid2; i++)
        {
            middle[i - mid1] = A[i];
        }

        for (int i = mid2; i < length; i++)
        {
            right[i - mid2] = A[i];
        }

        mergesort(left, mid1);
        mergesort(middle, mid2 - mid1);
        mergesort(right, length - mid2);

        merge(left, middle, right, A, mid1, mid2 - mid1, length - mid2);
    }
}

void merge(int left[], int middle[], int right[], int A[], int nL, int nM, int nR)
{
    int i, j, k;
    i = j = k = 0;

    while (i < nL && j < nM && k < nR)
    {
        if (left[i] <= middle[j] && left[i] <= right[k])
        {
            A[i + j + k] = left[i];
            i++;
        }
        else if (middle[j] <= left[i] && middle[j] <= right[k])
        {
            A[i + j + k] = middle[j];
            j++;
        }
        else
        {
            A[i + j + k] = right[k];
            k++;
        }
    }

    while (i < nL && j < nM)
    {
        if (left[i] <= middle[j])
        {
            A[i + j + k] = left[i];
            i++;
        }
        else
        {
            A[i + j + k] = middle[j];
            j++;
        }
    }

    while (i < nL && k < nR)
    {
        if (left[i] <= right[k])
        {
            A[i + j + k] = left[i];
            i++;
        }
        else
        {
            A[i + j + k] = right[k];
            k++;
        }
    }

    while (j < nM && k < nR)
    {
        if (middle[j] <= right[k])
        {
            A[i + j + k] = middle[j];
            j++;
        }
        else
        {
            A[i + j + k] = right[k];
            k++;
        }
    }

    while (i < nL)
    {
        A[i + j + k] = left[i];
        i++;
    }

    while (j < nM)
    {
        A[i + j + k] = middle[j];
        j++;
    }

    while (k < nR)
    {
        A[i + j + k] = right[k];
        k++;
    }
}

int main()
{
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    int A[n];
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    mergesort(A, n);

    printf("Sorted Array is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }

    return 0;
}
