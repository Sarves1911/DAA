#include <stdio.h>
#include <stdlib.h>

// Structure for circular queue
typedef struct
{
    int front, rear, size;
    unsigned capacity;
    int *array;
} CircularQueue;

// Function to create a new circular queue
CircularQueue *createQueue(unsigned capacity)
{
    CircularQueue *queue = (CircularQueue *)malloc(sizeof(CircularQueue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1; // Empty queue initially
    queue->array = (int *)malloc(capacity * sizeof(int));
    return queue;
}

// Function to check if the circular queue is full
int isFull(CircularQueue *queue)
{
    return (queue->size == queue->capacity);
}

// Function to check if the circular queue is empty
int isEmpty(CircularQueue *queue)
{
    return (queue->size == 0);
}

// Function to enqueue an element into the circular queue
void enqueue(CircularQueue *queue, int item)
{
    if (isFull(queue))
        return;

    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size++;
}

// Function to dequeue an element from the circular queue
int dequeue(CircularQueue *queue)
{
    if (isEmpty(queue))
        return -1;

    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// Function to get the Josephus winner
int josephusWinner(int n)
{
    CircularQueue *queue = createQueue(n);
    for (int i = 1; i <= n; i++)
        enqueue(queue, i);

    int k = 1; // Step size, always 1 for Josephus starting from the 2nd person
    int round = 1;
    while (queue->size > 1)
    {
        printf("Round %d: ", round);
        for (int i = 0; i < k; i++)
        { // Fix the step size here
            int eliminated = dequeue(queue);
            enqueue(queue, eliminated);
        }
        printf("Eliminated: %d\n", dequeue(queue));
        round++;

        // Create a new queue with remaining people
        CircularQueue *newQueue = createQueue(queue->size);
        while (!isEmpty(queue))
            enqueue(newQueue, dequeue(queue));
        free(queue);
        queue = newQueue;
    }

    int winner = dequeue(queue);
    free(queue);
    return winner;
}

int main()
{
    int n;
    printf("Enter the number of people: ");
    scanf("%d", &n);

    int winner = josephusWinner(n);
    printf("Josephus Winner: %d\n", winner);

    return 0;
}
