#include <stdio.h>
#include <math.h>

#define MAX_SIZE 1024

int board[MAX_SIZE][MAX_SIZE];
int tile = 1;

void trominoTile(int size, int xHole, int yHole, int xStart, int yStart)
{
    if (size == 2)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (xStart + i != xHole || yStart + j != yHole)
                {
                    board[xStart + i][yStart + j] = tile;
                }
            }
        }
        tile++;
        return;
    }

    int newSize = size / 2;
    int xMid = xStart + newSize;
    int yMid = yStart + newSize;

    if (xHole < xMid && yHole < yMid)
    {
        trominoTile(newSize, xHole, yHole, xStart, yStart);
        board[xMid][yMid - 1] = tile;
        board[xMid - 1][yMid] = tile;
        board[xMid][yMid] = tile;
    }
    else if (xHole < xMid && yHole >= yMid)
    {
        trominoTile(newSize, xHole, yHole, xStart, yMid);
        board[xMid][yMid - 1] = tile;
        board[xMid - 1][yMid - 1] = tile;
        board[xMid][yMid] = tile;
    }
    else if (xHole >= xMid && yHole < yMid)
    {
        trominoTile(newSize, xHole, yHole, xMid, yStart);
        board[xMid - 1][yMid] = tile;
        board[xMid - 1][yMid - 1] = tile;
        board[xMid][yMid] = tile;
    }
    else if (xHole >= xMid && yHole >= yMid)
    {
        trominoTile(newSize, xHole, yHole, xMid, yMid);
        board[xMid - 1][yMid] = tile;
        board[xMid][yMid - 1] = tile;
        board[xMid - 1][yMid - 1] = tile;
    }
    tile++;
}

int main()
{
    int n, i, j;
    scanf("%d %d %d", &n, &i, &j);

    int boardSize = pow(2, n);

    for (int x = 0; x < boardSize; x++)
    {
        for (int y = 0; y < boardSize; y++)
        {
            board[x][y] = 0;
        }
    }

    board[i][j] = -1;

    trominoTile(boardSize, i, j, 0, 0);

    for (int x = 0; x < boardSize; x++)
    {
        for (int y = 0; y < boardSize; y++)
        {
            if (board[x][y] == -1)
            {
                printf("X ");
            }
            else
            {
                printf("%d ", board[x][y]);
            }
        }
        printf("\n");
    }

    return 0;
}
