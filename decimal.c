#include <stdio.h>
#include <stdbool.h>

// Function to generate decimal strings without consecutive 'd'
void generateDecimalStrings(int n, int d, char *current, int index, bool prevWasD)
{
    if (index == n)
    {
        printf("%s\n", current);
        return;
    }

    for (int i = 0; i <= 9; i++)
    {
        if (i != d || !prevWasD)
        {
            current[index] = '0' + i;
            generateDecimalStrings(n, d, current, index + 1, i == d);
        }
    }
}

int main()
{
    int n, d;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of d: ");
    scanf("%d", &d);

    char current[n + 1];
    current[n] = '\0';
    generateDecimalStrings(n, d, current, 0, false);

    return 0;
}
