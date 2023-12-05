#include <stdio.h>

int josephus(int n)
{
    if (n == 1)
    {
        return 1; // Only one person remains, so the position is 1.
    }
    else
    {
        return (josephus(n - 1) + 1) % n + 1;
    }
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
