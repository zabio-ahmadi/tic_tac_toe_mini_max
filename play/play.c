#include "play.h"
#include "../board/board.h"

int eval_row(board brd)
{

    for (int i = 0; i < brd->col; i++)
    {
        // if (brd->matrix[i][0] == brd->matrix[i][1] &&
        //     brd->matrix[i][1] == brd->matrix[i][2])
        // {
        //     if (brd->matrix[i][0] == 'X')
        //         return +10;
        //     if (brd->matrix[i][0] == 'O')
        //         return -10;
        // }
        int x_count = 0;
        int o_count = 0;
        for (int j = 0; j < brd->row; j++)
        {
            if (brd->matrix[i][j] == 'X')
            {
                x_count++;
            }
            else if (brd->matrix[i][j] == 'O')
            {
                o_count++;
            }
        }
        if (x_count == WIN_FA)
        {
            return +10;
        }
        else if (o_count == WIN_FA)
        {
            return -10;
        }
    }
    return 0;
}

int eval_col(board brd)
{
    for (int j = 0; j < brd->col; j++)
    {

        // if (brd->matrix[0][j] == brd->matrix[1][j] &&
        //     brd->matrix[1][j] == brd->matrix[2][j])
        // {
        //     if (brd->matrix[0][j] == 'X')
        //         return +10;

        //     if (brd->matrix[0][j] == 'O')
        //         return -10;
        // }

        int x_count = 0;
        int o_count = 0;
        for (int i = 0; i < brd->row; i++)
        {
            if (brd->matrix[i][j] == 'X')
                x_count++;

            else if (brd->matrix[i][j] == 'O')
                o_count++;
        }
        if (x_count == WIN_FA)
            return +10;

        else if (o_count == WIN_FA)
            return -10;
    }
    return 0;
}

int eval_forward_diagonal(board brd)
{

    // if (brd->matrix[0][2] == brd->matrix[1][1] && brd->matrix[1][1] == brd->matrix[2][0])
    // {
    //     if (brd->matrix[0][2] == 'X')
    //         return +10;
    //     if (brd->matrix[0][2] == 'O')
    //         return -10;
    // }
    for (int i = brd->row - 1; i >= 0; i--)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = 0; j < brd->col; j++)
        {
            if ((i - j) < 0)
                continue;

            if (brd->matrix[i - j][j] == 'X')
                x_count++;

            if (brd->matrix[i - j][j] == 'O')
                o_count++;

            if (x_count == WIN_FA)
                return +10;

            if (o_count == WIN_FA)
                return -10;
        }
    }

    int index = 1;
    for (int i = 0; i < brd->row; i++)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = 0; j < brd->col; j++)
        {
            if (j + index >= brd->col)
                continue;

            if (brd->matrix[(brd->row - 1) - j][j + index] == 'X')
                x_count++;

            if (brd->matrix[(brd->row - 1) - j][j + index] == 'O')
                o_count++;

            if (x_count == WIN_FA)
                return +10;

            if (o_count == WIN_FA)
                return -10;

            index += 1;
        }
    }
    return 0;
}

int eval_backward_diagonal(board brd)
{

    // if (brd->matrix[0][0] == brd->matrix[1][1] && brd->matrix[1][1] == brd->matrix[2][2])
    // {
    //     if (brd->matrix[0][0] == 'X')
    //     {
    //         return +10;
    //     }
    //     if (brd->matrix[0][0] == 'O')
    //         return -10;
    // }

    for (int i = 0; i < brd->row; i++)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = brd->col; j >= 0; j--)
        {
            if ((i + j) >= brd->row)
                continue;

            if (brd->matrix[i + j][j] == 'X')
                x_count++;

            if (brd->matrix[i + j][j] == 'O')
                o_count++;

            if (x_count == WIN_FA)
                return +10;

            if (o_count == WIN_FA)
                return -10;
        }
    }

    for (int i = 1; i < brd->row; i++)
    {
        int x_count = 0;
        int o_count = 0;

        for (int j = 0; j < brd->col; j++)
        {
            if (i + j >= brd->col)
                continue;

            if (brd->matrix[j][i + j] == 'X')
                x_count++;

            if (brd->matrix[j][i + j] == 'O')
                o_count++;

            if (x_count == WIN_FA)
                return +10;

            if (o_count == WIN_FA)
                return -10;
        }
    }

    return 0;
}

bool check_col(board brd, int col)
{
    --col;
    int x_count = 0;
    int o_count = 0;

    for (int i = brd->row - 1; i >= 0; i--)
    {
        if (brd->matrix[i][col] == 'O')
        {
            o_count++;
            x_count = 0;
        }
        if (brd->matrix[i][col] == 'X')
        {
            x_count++;
            o_count = 0;
        }

        if (x_count == WIN_FA || o_count == WIN_FA)
        {
            return true;
        }
    }
    return false;
}

int check_win(board brd)
{

    int ev = eval_col(brd);
    if (ev == 10 || ev == -10)
        return ev;

    ev = eval_row(brd);
    if (ev == 10 || ev == -10)
        return ev;

    ev = eval_forward_diagonal(brd);
    if (ev == 10 || ev == -10)
        return ev;

    ev = eval_backward_diagonal(brd);
    if (ev == 10 || ev == -10)
        return ev;

    return 0;
}

bool case_is_available(char chr) { return ((int)chr == 0); }

int evaluate(board brd)
{
    // check row
    int points = eval_row(brd);
    if (points == 10 || points == -10)
    {
        return points;
    }
    // Checking column.
    points = eval_col(brd);
    if (points == 10 || points == -10)
    {
        return points;
    }
    // Checking backward Diagonals for X or O.
    points = eval_backward_diagonal(brd);
    if (points == 10 || points == -10)
        return points;

    // check forward Diagonal for x or O
    points = eval_forward_diagonal(brd);
    if (points == 10 || points == -10)
    {
        return points;
    }

    // no win return 0
    return 0;
}

bool board_is_full(board brd)
{

    for (int i = 0; i < brd->row; i++)
    {
        for (int j = 0; j < brd->col; j++)
        {
            if (case_is_available(brd->matrix[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

int min_max(board brd, bool is_max)
{
    // calcule les points de chaque case
    int score = evaluate(brd);
    if (score == 10 || score == -10)
        return score;

    if (is_max)
    {
        int best_score = _MIN_INF_;
        for (int i = 0; i < brd->row; i++)
        {
            for (int j = 0; j < brd->col; j++)
            {
                // the case is available
                if (case_is_available(brd->matrix[i][j]))
                {
                    add_to_board(brd, i + 1, j + 1, 'X');
                    // print_board(brd);
                    int score = min_max(brd, false);
                    add_to_board(brd, i + 1, j + 1, (char)0);

                    // max(score, best_score);
                    best_score = (score > best_score) ? score : best_score;
                }
            }
        }
        return best_score;
    }
    else
    {
        int best_score = _MAX_INF_;
        for (int i = 0; i < brd->row; i++)
        {
            for (int j = 0; j < brd->col; j++)
            {
                // the case is available
                if (case_is_available(brd->matrix[i][j]))
                {
                    add_to_board(brd, i + 1, j + 1, 'O');
                    int score = min_max(brd, true);
                    add_to_board(brd, i + 1, j + 1, (char)0);

                    // min(score, best_score);
                    best_score = (score < best_score) ? score : best_score;
                }
            }
        }
        return best_score;
    }
}

void best_move(board brd)
{
    int best_score = _MIN_INF_;
    move best_move;

    for (int i = 0; i < brd->row; i++)
    {
        for (int j = 0; j < brd->col; j++)
        {
            // the case is available
            if (case_is_available(brd->matrix[i][j]))
            {
                // add move to evalaute
                add_to_board(brd, i + 1, j + 1, 'X');

                // find max score
                int score = min_max(brd, false);
                // undo move
                add_to_board(brd, i + 1, j + 1, (char)0);
                // find the case with max probab
                if (score > best_score)
                {

                    best_move.row = i;
                    best_move.col = j;
                    best_score = score;
                }
            }
        }
    }

    add_to_board(brd, best_move.row + 1, best_move.col + 1, 'X');
    printf("\nmove : %d move : %d\n", best_move.row, best_move.col);
}

void two_player(board brd)
{
    printInColor("blue", "\n\n---------------------------------------------------------------------------\n");
    printf("TWO PLAYER MODE \n");
    printf("---------------------------------------------------------------------------\n");
    printInColor("white", "");
    printf("- game start with player [X] \n");
    printf("- please choose the case [row][space][column]: \n");

    bool win = false;
    bool turn = true;
    while (!win)
    {
        if (!board_is_full(brd))
        {
            int row, col;
            scanf("%d %d", &row, &col);
            if ((row < 0 || row > brd->row) || (col < 0 || col > brd->col))
            {
                printInColor("red", "in-valid case\n");
                printInColor("white", "please reenter\n");
                continue;
            }
            else
            {
                char data = (turn) ? 'X' : 'O';
                add_to_board(brd, row, col, data);
                print_board(brd);

                int checked = check_win(brd);
                if (checked == 10)
                {
                    printInColor("green", "");
                    printf("player X Wins\n");
                    printInColor("white", "");
                    return;
                }

                if (checked == -10)
                {
                    printInColor("red", "");
                    printf("player O Wins\n");
                    printInColor("white", "");
                    return;
                }
                turn = !turn;
            }
        }
        else
        {
            printf("MATH NULL\n");
            return;
        }
    }
}

void player_random_AI(board brd)
{
    srand(time(NULL));
    printInColor("blue", "\n\n---------------------------------------------------------------------------\n");
    printf("random AI MODE \n");
    printf("---------------------------------------------------------------------------\n");
    printInColor("white", "");
    printf("- game start with player [X] \n");
    printf("- please choose the case rowXcolumn: \n");

    bool win = false;
    while (!win)
    {
        if (!board_is_full(brd))
        {
            int row, col;
            scanf("%d %d", &row, &col);
            if ((row < 0 || row > brd->row) || (col < 0 || col > brd->col))
            {
                printInColor("red", "in-valid case\n");
                printInColor("white", "please reenter\n");
                continue;
            }
            else
            {
                add_to_board(brd, row, col, 'O');
                print_board(brd);
                int checked = check_win(brd);

                if (checked == -10)
                {
                    printInColor("red", "");
                    printf("player O Wins\n");
                    printInColor("white", "");
                    return;
                }
                else if (!board_is_full(brd))
                {

                    // computer turn
                    // 1 . generate random number between 1-3 for row , et 1-3 for colum
                    int rnd_row = generate_random(brd->row - 1, 1);
                    int rnd_col = generate_random(brd->col - 1, 1);
                    // 2 . if the case is occupied regenerate the random number
                    while (brd->matrix[rnd_row][rnd_col] == 'O' || brd->matrix[rnd_row][rnd_col] == 'X')
                    {
                        rnd_row = generate_random(brd->row - 1, 1);
                        rnd_col = generate_random(brd->col - 1, 1);
                        // printf("rnd_row: %d rnd_col:%d\n", rnd_row, rnd_col);
                    }

                    add_to_board(brd, rnd_row, rnd_col, 'X');
                    print_board(brd);
                    int checked = check_win(brd);

                    if (checked == 10)
                    {
                        printInColor("green", "");
                        printf("player X Wins\n");
                        printInColor("white", "");
                        return;
                    }
                }
                else
                {
                    printf("MATH NULL\n");
                    return;
                }
            }
        }

        // int row, col;
        // scanf("%d %d", &row, &col);

        // if ((row < 0 || row > brd->row) || (col < 0 || col > brd->col))
        // {
        //     printInColor("red", "in-valid index\n");
        //     printInColor("white", "please reenter\n");
        //     continue;
        // }
        // else
        // {
        //     add_to_board(brd, row, col, 'O');
        //     win = check_win(brd);
        //     if (win)
        //     {
        //         printf("WIN");
        //         break;
        //     }
        //     else // no win
        //     {
        //         // computer turn

        //         // 1 . generate random number between 1-3 for row , et 1-3 for colum
        //         int rnd_row = generate_random(RND_UPPER, RND_LOWER);
        //         int rnd_col = generate_random(RND_UPPER, RND_LOWER);
        //         // 2 . if the case is occupied regenerate the random number
        //         while (!case_is_available(brd->matrix[rnd_row][rnd_col]))
        //         {
        //             rnd_row = generate_random(RND_UPPER, RND_LOWER);
        //             rnd_col = generate_random(RND_UPPER, RND_LOWER);
        //         }

        //         // printf("%d %d\n", rnd_row, rnd_col);
        //         add_to_board(brd, rnd_row, rnd_col, 'X');
        //     }
        //     print_board(brd);
        // }
    }
}

void smart_ai_min_max(board brd)
{
    bool win = false;
    bool turn = true; // computer starts
    while (!win)
    {
        bool is_full = board_is_full(brd);
        if (!is_full)
        {
            if (turn)
            {
                best_move(brd);
                print_board(brd);

                if (evaluate(brd) == 10)
                {
                    printf("computer win the game !!!");
                    return;
                }
                turn = !turn;
                continue; // jump to the start of loop
            }
            else
            {
                int row, col;
                printf("please choose the case by [row][col] :\n");
                scanf("%d %d", &row, &col);

                if (case_is_available(brd->matrix[row - 1][col - 1]))
                {
                    add_to_board(brd, row, col, 'O');
                    print_board(brd);

                    if (evaluate(brd) == -10)
                    {
                        printf("you win the game !!!\n");
                        return;
                    }
                    turn = !turn;
                    continue;
                }
                else
                {

                    printInColor("red", "choose another box this box is taking\n");
                    printInColor("white", " ");
                    continue;
                }
            }
        }
        // if not full & no win => draw
        else
        {
            printf("the game is draw !!! \n");

            return;
        }
    }
}