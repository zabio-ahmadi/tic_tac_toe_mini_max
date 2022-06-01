#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./board/board.h"
#include "./helpers/helpers.h"
#include "./play/play.h"
#include <unistd.h>

int main()
{

    int size, mode;
    request_cofig(&size, &mode);

    board brd = board_alloc(size, size);
    switch (mode)
    {
    case 1:
        two_player(brd);
        break;
    case 2:
        player_random_AI(brd);
        break;
    case 3:
        player_vs_smart_ai_mini_max(brd);
        break;
    default:
        break;
    }

    board_destroy(brd);

    return 0;
}