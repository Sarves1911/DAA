#include <stdio.h>
#include <stdlib.h>

// Function to print all valid parenthesizations for n pairs of brackets
void generateParenthesis(int n)
{
    if (n <= 0)
    {
        return;
    }

    // Create an array to store valid combinations
    char *combinations = (char *)malloc(2 * n * sizeof(char));
    if (combinations == NULL)
    {
        return;
    }

    // Helper function with memoization to generate valid combinations recursively
    void generate(int left, int right, int index, char *combinations)
    {
        if (left == 0 && right == 0)
        {
            combinations[index] = '\0';
            printf("%s\n", combinations);
            return;
        }

        if (left > 0)
        {
            combinations[index] = '(';
            generate(left - 1, right, index + 1, combinations);
        }
        if (right > left)
        {
            combinations[index] = ')';
            generate(left, right - 1, index + 1, combinations);
        }
    }

    generate(n, n, 0, combinations);

    free(combinations);
}

int main()
{
    int n;
    printf("Enter the number of pairs of brackets (n): ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    printf("Valid parenthesizations for %d pairs of brackets:\n", n);
    generateParenthesis(n);

    return 0;
}
