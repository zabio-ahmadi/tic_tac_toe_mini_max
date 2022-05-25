#include <stdio.h>
#include "../board/board.h"
#include "../helpers/helpers.h"
#ifndef _PLAY_
#define _PLAY_
#define WIN_FA 3
#define RND_UPPER 3
#define RND_LOWER 1

#define _MIN_INF_ -1000000
#define _MAX_INF_ 1000000
#define PC 'x'
#define PLAYER 'O'
#define CASE_EMPTY (char)0

typedef struct _move
{
    int row, col;
} move;

void two_player(board brd);

void player_random_AI(board brd);

void smart_ai_min_max(board brd);
#endif