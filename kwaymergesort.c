#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent a node in the heap
typedef struct
{
    int element;   // The element value
    int listIndex; // The index of the list the element belongs to
    int nextIndex; // The index of the next element in the list
} HeapNode;

// Structure to represent a min heap
typedef struct
{
    HeapNode *nodes; // Array to store heap nodes
    int capacity;    // Maximum possible size of the min heap
    int size;        // Current size of the min heap
} MinHeap;

// Function to create a new heap node
HeapNode *createHeapNode(int element, int listIndex, int nextIndex)
{
    HeapNode *node = (HeapNode *)malloc(sizeof(HeapNode));
    node->element = element;
    node->listIndex = listIndex;
    node->nextIndex = nextIndex;
    return node;
}

// Function to create a new min heap
MinHeap *createMinHeap(int capacity)
{
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->nodes = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    return heap;
}

// Function to swap two heap nodes
void swapHeapNodes(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain the min heap property
void heapify(MinHeap *heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->nodes[left].element < heap->nodes[smallest].element)
        smallest = left;

    if (right < heap->size && heap->nodes[right].element < heap->nodes[smallest].element)
        smallest = right;

    if (smallest != index)
    {
        swapHeapNodes(&heap->nodes[smallest], &heap->nodes[index]);
        heapify(heap, smallest);
    }
}

// Function to insert a new element into the min heap
void insertIntoHeap(MinHeap *heap, int element, int listIndex, int nextIndex)
{
    if (heap->size == heap->capacity)
    {
        printf("Overflow: Could not insert element into heap!\n");
        return;
    }
    int i = heap->size;
    heap->nodes[i].element = element;
    heap->nodes[i].listIndex = listIndex;
    heap->nodes[i].nextIndex = nextIndex;

    // Fix the min heap property by comparing with parent nodes
    while (i != 0 && heap->nodes[(i - 1) / 2].element > heap->nodes[i].element)
    {
        swapHeapNodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    heap->size++;
}
// Function to perform K-way merge sort using min heap
void kWayMergeSort(int *arr, int n, int k)
{
    MinHeap *heap = createMinHeap(k);
    int *output = (int *)malloc(n * sizeof(int));
    int *nextIndex = (int *)malloc(k * sizeof(int));

    // Initialize nextIndex array with the first index of each list
    for (int i = 0; i < k; i++)
        nextIndex[i] = (n / k) * i;

    // Build initial min heap with first element from each list
    for (int i = 0; i < k; i++)
    {
        if (nextIndex[i] < (n / k) * (i + 1))
            insertIntoHeap(heap, arr[nextIndex[i]], i, nextIndex[i] + 1);
        else
            insertIntoHeap(heap, INT_MAX, i, nextIndex[i]);
    }

    // Perform K-way merge sort
    for (int i = 0; i < n; i++)
    {
        HeapNode *root = heap->nodes;
        output[i] = root->element;

        if (root->nextIndex < (n / k) * (root->listIndex + 1))
            root->element = arr[root->nextIndex++];
        else
            root->element = INT_MAX;

        heapify(heap, 0);
    }

    // Copy the sorted elements from the output array back to the input array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
    free(nextIndex);
    free(heap->nodes);
    free(heap);
}

// Function to print an array
void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int n, k;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter the value of K: ");
    scanf("%d", &k);

    printf("Input array: ");
    printArray(arr, n);

    kWayMergeSort(arr, n, k);

    printf("Sorted array: ");
    printArray(arr, n);

    free(arr);

    return 0;
}
