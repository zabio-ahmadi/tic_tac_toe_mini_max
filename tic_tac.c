#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define COLS 6
#define ROWS 7

char board[ROWS][COLS] = {};
int col_index[COLS] = {};
bool turn = false;

void board_init()
{

    // init col_index
    for (int i = 0; i < COLS; i++)
    {
        col_index[i] = ROWS;
    }
}

void print_board()
{

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("[%c]", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int convert_input(int col)
{

    int col_index = -1;
    switch (col)
    {
    case 1:
        col_index = 0;
        break;
    case 2:
        col_index = 1;
        break;
    case 4:
        col_index = 3;
        break;
    case 8:
        col_index = 4;
        break;
    case 16:
        col_index = 5;
        break;
    case 32:
        col_index = 6;
        break;
    case 64:
        col_index = 7;
        break;
    }
    return col_index;
}

void add_to_board(int col)
{
    int column = convert_input(col);
    char val = (turn) ? 'O' : 'X'; // player one starts with 'X'
    col_index[column]--;
    board[col_index[column]][column] = val;
}

bool board_is_full()
{

    int somme = 0;
    for (int i = 0; i < COLS; i++)
    {
        somme += col_index[i];
    }
    return (somme == 0); // check all column index are arrived to 64
}

bool column_is_full(int col)
{

    return (col_index[convert_input(col)] == 0);
}

bool board_is_empty()
{

    bool is_empty = true;
    for (int i = 0; i < COLS; i++)
    {

        // see if column is full
        if (col_index[i] != ROWS)
        {
            is_empty = false;
        }
    }
    return is_empty;
}

bool check_row(int column)
{

    int row = col_index[convert_input(column)];

    int x_count = 0;
    int o_count = 0;

    for (int i = 0; i < COLS; i++)
    {

        if (board[row][i] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[row][i] == 'X')
        {
            x_count++;
            o_count = 0;
        }

        if (x_count == 4 || o_count == 4)
        {
            return true;
        }
    }
    return false;
}

bool check_col(int column)
{

    int col = convert_input(column);

    int x_count = 0;
    int o_count = 0;

    for (int i = ROWS - 1; i >= 0; i--)
    {

        if (board[i][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[i][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }
        if (x_count == 4 || o_count == 4)
        {
            return true;
        }
    }
    return false;
}

bool check_backward_diagonal(int column)
{

    int col = convert_input(column);
    int row = col_index[col];

    int x_count = 0;
    int o_count = 0;
    // look up
    while (row >= 0 && col >= 0)
    {

        if (board[row][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[row][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }

        if (x_count == 4 || o_count == 4)
        {
            return true;
        }

        row--;
        col--;
    }

    col = convert_input(column);
    row = col_index[col];
    row++;
    col++;

    // look down
    while (row < ROWS && col < COLS)
    {

        if (board[row][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[row][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }
        if (x_count == 4 || o_count == 4)
        {
            return true;
        }
        col++;
        row++;
    }
    return false;
}

bool check_forward_diagonal(int column)
{

    int col = convert_input(column);
    int row = col_index[col];

    int x_count = 0;
    int o_count = 0;

    // look down
    while (col >= 0 && row < ROWS)
    {

        if (board[row][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[row][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }

        if (x_count == 4 || o_count == 4)
        {
            return true;
        }
        row++;
        col--;
    }

    // look up
    col = convert_input(column);
    row = col_index[col];

    while (col <= COLS && row >= 0)
    {

        if (board[row][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (board[row][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }

        if (x_count == 5 || o_count == 5)
        {
            return true;
        }
        row--;
        col++;
    }

    return false;
}

bool check_win(int column)
{

    if (check_col(column))
    {
        return true;
    }

    else if (check_row(column))
    {
        return true;
    }

    else if (check_forward_diagonal(column))
    {
        return true;
    }

    else if (check_backward_diagonal(column))
    {
        return true;
    }
    else
        return false;
}

int main()
{

    while (true)
    {
        printf("Column number? (starts at 1):\n");
        int column;
        scanf("%d", &column);

        add_to_board(column);
        print_board();
        if (check_win(column))
        {
            if (turn == false)
            {
                printf("Player one won!\n");
            }
            else
            {
                printf("Player two won!\n");
            }
            break;
        }

        // change the turn
        turn = !turn;

        // if we have no winner and the board is full -> it is a draw
        if (board_is_full())
        {
            printf("It is a draw.\n");
            break;
        }
    }
}