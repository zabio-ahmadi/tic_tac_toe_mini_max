
#include <stdbool.h>
#ifndef _BOARD_
#define _BOARD_

typedef struct
{
    int row;
    int col;
    char **matrix;
} _board;

typedef _board *board;

board board_alloc(int row, int col);

void add_to_board(board brd, int row, int col, char data);

void print_board(board brd);

void board_destroy(board brd);

#endif