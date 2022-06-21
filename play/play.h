#include <stdio.h>
#include <unistd.h>
#include "../board/board.h"
#include "../helpers/helpers.h"
#ifndef _PLAY_
#define _PLAY_
#define WIN_FA 4
#define RND_UPPER 3
#define RND_LOWER 1

#define _MIN_INF_ -1000000
#define _MAX_INF_ 1000000
#define PC 'X'
#define PLAYER 'O'
#define CASE_EMPTY (char)0

typedef struct _move
{
    int row, col;
} move;

// evaluate score of each case
int eval_row(board brd);
int eval_col(board brd);
int eval_forward_diagonal(board brd);
int eval_backward_diagonal(board brd);
int evaluate(board brd);
// evaluate score of each case
int check_win(board brd);

bool case_is_available(char chr);
void case_to_coordinates(board brd, int cas, int *i, int *j);
bool board_is_full(board brd);

int mini_max(board brd, bool is_max, int depth);
int mini_max_alpha(board brd, bool is_max, int depth, int *alpha, int *beta);
void best_move(board brd, bool prun);

void two_player(board brd);
void player_random_AI(board brd);

void player_vs_smart_ai_mini_max(board brd, bool prun);

#endif