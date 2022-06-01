#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "../helpers/helpers.h"

board board_alloc(int row, int col)
{
    board brd = calloc(1, sizeof(_board));
    brd->row = row;
    brd->col = col;

    brd->matrix = calloc(brd->row, sizeof(char **));

    for (int i = 0; i < brd->row; i++)
    {
        brd->matrix[i] = calloc(brd->col, sizeof(char *));
    }

    for (int i = 0; i < brd->row; i++)
    {
        for (int j = 0; j < brd->col; j++)
        {
            brd->matrix[i][j] = 0;
        }
    }
    return brd;
}

void add_to_board(board brd, int row, int col, char data)
{
    --row;
    --col;

    if ((row >= 0 && col >= 0) && (row < brd->row && col < brd->col))
        brd->matrix[row][col] = data;
}

void print_board(board brd)
{
    // row 2n + 1 //
    for (int i = 0; i < (2 * brd->row + 1); i++)
    {
        // col 2n + 1
        for (int j = 0; j < (2 * brd->col + 1); j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    printf("┌");
                    continue;
                }
                else if (j == (2 * brd->col))
                {
                    printf("┐");
                    continue;
                }

                else if (j % 2 == 1)
                {
                    printf("───");
                }

                else if (j % 2 == 0)
                {
                    printf("┬");
                }
            }
            else if (i == (2 * brd->row))
            {

                if (j == 0)
                {
                    printf("└");
                    continue;
                }
                else if (j == (2 * brd->col))
                {
                    printf("┘");
                    continue;
                }
                else if (j % 2 == 1)
                {
                    printf("───");
                }

                else if (j % 2 == 0)
                {
                    printf("┴");
                }
            }
            else
            {

                if (i % 2 == 1)
                {

                    if (j == 0 || j == (2 * brd->col))
                    {
                        printf("│");
                    }
                    else
                    {
                        if (j % 2 == 0)
                        {
                            printf("│");
                        }
                        else
                        {
                            if ((int)brd->matrix[i / 2][j / 2] > 65)
                            {

                                if (brd->matrix[i / 2][j / 2] == 'O')
                                {
                                    printInColor("purple", "");
                                    printf(" %c ", brd->matrix[i / 2][j / 2]);
                                    printInColor("white", "");
                                }
                                else
                                {
                                    printInColor("cyan", "");
                                    printf(" %c ", brd->matrix[i / 2][j / 2]);
                                    printInColor("white", "");
                                }
                                // printf(" %c ", brd->matrix[i / 2][j / 2]);
                            }
                            else
                            {
                                printf("   ");
                            }
                        }
                    }
                }
                else
                {
                    if (j == 0)
                    {
                        printf("├");
                    }
                    else if (j == (2 * brd->col))
                    {
                        printf("┤");
                    }
                    else if (j % 2 == 0)
                    {
                        printf("┼");
                    }
                    else
                    {
                        printf("───");
                    }
                }
            }
        }
        printf("\n");
    }

    printInColor("green", "");
    for (int i = 1; i <= brd->col; i++)
    {
        printf("  %d ", i % 10);
    }
    printInColor("white", "");
    printf("\n");
}

void board_destroy(board brd)
{
    for (int i = 0; i < brd->row; i++)
    {
        free(brd->matrix[i]);
    }
    free(brd->matrix);
    free(brd);
    brd = NULL;
}