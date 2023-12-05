#include <stdio.h>

int findDiskNumber(int n, int k, int source, int auxiliary, int destination)
{
    if (n == 1)
    {
        if (k == 1)
        {
            return source;
        }
        else
        {
            return destination;
        }
    }

    int movesWithNMinus1Disks = (1 << (n - 1)) - 1;
    if (k <= movesWithNMinus1Disks)
    {
        return findDiskNumber(n - 1, k, source, destination, auxiliary);
    }
    else if (k == movesWithNMinus1Disks + 1)
    {
        return source;
    }
    else
    {
        return findDiskNumber(n - 1, k - (movesWithNMinus1Disks + 1), auxiliary, source, destination);
    }
}

int main()
{
    int n, k;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    printf("Enter the value of k: ");
    scanf("%d", &k);

    int largestDisk = n - 1;
    int diskNumber = findDiskNumber(n, k, 0, 1, 2);

    if (diskNumber == -1)
    {
        printf("Invalid input\n");
    }
    else
    {
        printf("Disk number %d (disk %d) will be moved after %d moves\n", diskNumber, largestDisk - diskNumber, k);
    }

    return 0;
}
