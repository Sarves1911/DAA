#include <stdio.h>

int josephus(int n)
{
    int i, idx, remaining;
    int array[n];

    // Initialize the array of people with 1 indicating they are still present
    for (i = 0; i < n; i++)
    {
        array[i] = 1;
    }

    idx = 0;       // starting index (2nd person)
    remaining = n; // number of people remaining

    while (remaining > 1)
    {
        int count = 0;
        int k = 2; // Step size is 2 for Josephus starting from the 2nd person
        while (count < k)
        {
            // Find the next person who is still in the array
            if (array[idx] == 1)
            {
                count++;
            }
            idx = (idx + 1) % n; // move to the next person in the array
        }

        // Mark the k-th person for elimination
        array[(idx + n - 1) % n] = 0;
        remaining--;
    }

    // Find the value of the last remaining person
    for (i = 0; i < n; i++)
    {
        if (array[i] == 1)
        {
            return i + 1; // Add 1 to get the actual person number
        }
    }

    // Should never reach this point for valid inputs
    return -1;
}

int main()
{
    int n;
    printf("Enter the number of people: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input. n should be a positive integer.\n");
        return 1;
    }

    int winner = josephus(n);
    printf("The winner is person number %d.\n", winner);

    return 0;
}
