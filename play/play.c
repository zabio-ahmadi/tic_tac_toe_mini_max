#include "play.h"
#include "../board/board.h"

int eval_row(board brd)
{

    for (int i = 0; i < brd->row; i++)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = 0; j < brd->col; j++)
        {
            if (brd->matrix[i][j] == 'X')
            {
                x_count++;
                o_count = 0;
            }
            else if (brd->matrix[i][j] == 'O')
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
            }
            if (x_count == WIN_FA)
            {
                return +1;
            }
            else if (o_count == WIN_FA)
            {
                return -1;
            }
        }
    }
    return 0;
}

int eval_col(board brd)
{
    for (int j = 0; j < brd->col; j++)
    {
        int x_count = 0;
        int o_count = 0;
        for (int i = 0; i < brd->row; i++)
        {
            if (brd->matrix[i][j] == PC)
            {
                x_count++;
                o_count = 0;
            }
            else if (brd->matrix[i][j] == PLAYER)
            {
                o_count++;
                x_count = 0;
            }
            else
            {
                x_count = 0;
                o_count = 0;
            }
            if (x_count == WIN_FA)
                return +1;

            else if (o_count == WIN_FA)
                return -1;
        }
    }
    return 0;
}

int eval_forward_diagonal(board brd)
{
    for (int i = brd->row - 1; i >= 0; i--)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = 0; j < brd->col; j++)
        {
            if ((i - j) < 0)
                continue;

            if (brd->matrix[i - j][j] == PC)
            {
                x_count++;
                o_count = 0;
            }

            if (brd->matrix[i - j][j] == PLAYER)
            {
                o_count++;
                x_count = 0;
            }

            if (x_count == WIN_FA)
                return +1;

            if (o_count == WIN_FA)
                return -1;
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

            if (brd->matrix[(brd->row - 1) - j][j + index] == PC)
            {
                x_count++;
                o_count = 0;
            }

            if (brd->matrix[(brd->row - 1) - j][j + index] == PLAYER)
            {
                o_count++;
                x_count = 0;
            }

            if (x_count == WIN_FA)
                return +1;

            if (o_count == WIN_FA)
                return -1;

            index += 1;
        }
    }
    return 0;
}

int eval_backward_diagonal(board brd)
{

    for (int i = 0; i < brd->row; i++)
    {
        int x_count = 0;
        int o_count = 0;
        for (int j = brd->col; j >= 0; j--)
        {
            if ((i + j) >= brd->row)
                continue;

            if (brd->matrix[i + j][j] == PC)
            {
                x_count++;
                o_count = 0;
            }

            if (brd->matrix[i + j][j] == PLAYER)
            {
                o_count++;
                x_count = 0;
            }

            if (x_count == WIN_FA)
                return +1;

            if (o_count == WIN_FA)
                return -1;
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

            if (brd->matrix[j][i + j] == PC)
            {
                x_count++;
                o_count = 0;
            }

            if (brd->matrix[j][i + j] == PLAYER)
            {
                o_count++;
                x_count = 0;
            }

            if (x_count == WIN_FA)
                return +1;

            if (o_count == WIN_FA)
                return -1;
        }
    }

    return 0;
}

int check_win(board brd)
{

    int ev = eval_col(brd);
    if (ev == 1 || ev == -1)
        return ev;

    ev = eval_row(brd);
    if (ev == 1 || ev == -1)
        return ev;

    ev = eval_forward_diagonal(brd);
    if (ev == 1 || ev == -1)
        return ev;

    ev = eval_backward_diagonal(brd);
    if (ev == 1 || ev == -1)
        return ev;

    return 0;
}

bool case_is_available(char chr) { return ((int)chr == 0); }

int evaluate(board brd)
{
    // check row
    int points = eval_row(brd);
    if (points == 1 || points == -1)
    {
        return points;
    }
    // Checking column.
    points = eval_col(brd);
    if (points == 1 || points == -1)
    {
        return points;
    }
    // Checking backward Diagonals for X or O.
    points = eval_backward_diagonal(brd);
    if (points == 1 || points == -1)
        return points;

    // check forward Diagonal for x or O
    points = eval_forward_diagonal(brd);
    if (points == 1 || points == -1)
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

int remaining_case(board brd)
{
    int count = 0;
    for (int i = 0; i < brd->row; i++)
    {
        for (int j = 0; j < brd->col; j++)
        {
            if (case_is_available(brd->matrix[i][j]))
            {
                count++;
            }
        }
    }
    return count;
}

int min_max(board brd, bool is_max, int depth)
{

    // printf("depth:  %d\n", depth);
    if (depth >= 7)
    {
        return 0;
    }

    int score = evaluate(brd);

    if (score == 1)
    {
        return score * (remaining_case(brd) + 1);
    }
    else if (score == -1)
    {
        return score * (remaining_case(brd) + 1);
    }

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
                    // add to board
                    add_to_board(brd, i + 1, j + 1, PC);

                    // calculate score of this case
                    int scores = min_max(brd, false, depth + 1);

                    // undo move
                    add_to_board(brd, i + 1, j + 1, (char)0);

                    // max(score, best_score);
                    best_score = (scores > best_score) ? scores : best_score;
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
                    // add to board
                    add_to_board(brd, i + 1, j + 1, PLAYER);
                    // calculate score of this case
                    int scores = min_max(brd, true, depth + 1);

                    // undo move
                    add_to_board(brd, i + 1, j + 1, (char)0);

                    // min(score, best_score);
                    best_score = (scores < best_score) ? scores : best_score;
                }
            }
        }
        return best_score;
    }
}

void case_to_coordinates(board brd, int cas, int *i, int *j)
{

    if (brd->row == 3)
    {
        switch (cas)
        {
        case 1:
            *i = 1;
            *j = 1;
            break;
        case 2:
            *i = 1;
            *j = 2;
            break;
        case 3:
            *i = 1;
            *j = 3;
            break;
        case 4:
            *i = 2;
            *j = 1;
            break;

        case 5:
            *i = 2;
            *j = 2;
            break;
        case 6:
            *i = 2;
            *j = 3;
            break;
        case 7:
            *i = 3;
            *j = 1;
            break;
        case 8:
            *i = 3;
            *j = 2;
            break;
        case 9:
            *i = 3;
            *j = 3;
            break;
        }
    }

    if (brd->row == 4)
    {
        switch (cas)
        {
        case 1:
            *i = 1;
            *j = 1;
            break;
        case 2:
            *i = 1;
            *j = 2;
            break;
        case 3:
            *i = 1;
            *j = 3;
            break;
        case 4:
            *i = 1;
            *j = 4;
            break;

        case 5:
            *i = 2;
            *j = 1;
            break;
        case 6:
            *i = 2;
            *j = 2;
            break;
        case 7:
            *i = 2;
            *j = 3;
            break;
        case 8:
            *i = 2;
            *j = 4;
            break;
        case 9:
            *i = 3;
            *j = 1;
            break;

        case 10:
            *i = 3;
            *j = 2;
            break;
        case 11:
            *i = 3;
            *j = 3;
            break;
        case 12:
            *i = 3;
            *j = 4;
            break;

        case 13:
            *i = 4;
            *j = 1;
            break;

        case 14:
            *i = 4;
            *j = 2;
            break;
        case 15:
            *i = 4;
            *j = 3;
            break;
        case 16:
            *i = 4;
            *j = 4;
            break;
        }
    }
}

void make_move(board brd, bool turn, int *i, int *j)
{

    int cas = generate_random(brd->row * brd->col, 1);
    int tmp_i = 0;
    int tmp_j = 0;

    case_to_coordinates(brd, cas, &tmp_i, &tmp_j);
    while (!case_is_available(brd->matrix[tmp_i - 1][tmp_j - 1]))
    {
        cas = generate_random(9, 1);
        case_to_coordinates(brd, cas, &tmp_i, &tmp_j);
    }

    add_to_board(brd, tmp_i, tmp_j, (turn) ? PC : PLAYER);

    *i = tmp_i;
    *j = tmp_j;
}
void best_move(board brd, bool first_move)
{
    int best_score = 0;
    move best_move;
    /*
        in first move every case has the same probability :
        it is not good to start every time from index [0][0]
        we should randomize this in the range of [1 to 9]
    */
    if (first_move)
    {
        srand(time(0));
        make_move(brd, true, &best_move.col, &best_move.row);
    }
    else
    {
        // for available case add and undo -> to see best score
        for (int i = 0; i < brd->row; i++)
        {
            for (int j = 0; j < brd->col; j++)
            {
                // the case is available
                if (case_is_available(brd->matrix[i][j]))
                {
                    // add move to evalaute
                    add_to_board(brd, i + 1, j + 1, PC);

                    // find max score
                    int score = min_max(brd, false, 0);
                    // printf("col: %d row: %d score : %d\n", i, j, score);
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
        add_to_board(brd, best_move.row + 1, best_move.col + 1, PC);
    }
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
            else if (case_is_available(brd->matrix[row - 1][col - 1]) == false)
            {
                printInColor("red", "please choose another box this box is taking\n");
                printInColor("white", " ");
                continue;
            }
            else
            {
                char data = (turn) ? PC : PLAYER;
                add_to_board(brd, row, col, data);
                print_board(brd);

                int checked = check_win(brd);
                if (checked == 1)
                {
                    printInColor("green", "");
                    printf("player X Wins\n");
                    printInColor("white", "");
                    return;
                }
                if (checked == -1)
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

    printInColor("blue", "\n\n---------------------------------------------------------------------------\n");
    printf("random AI MODE \n");
    printf("---------------------------------------------------------------------------\n");
    printInColor("white", "");
    printf("- game start with player [X] \n");
    printf("- please choose the case rowXcolumn: \n");

    srand(time(0));
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
            else if (case_is_available(brd->matrix[row - 1][col - 1]) == false)
            {
                printInColor("red", "please choose another box this box is taking\n");
                printInColor("white", " ");
                continue;
            }
            else
            {
                add_to_board(brd, row, col, PLAYER);
                print_board(brd);
                int checked = check_win(brd);

                if (checked == -1)
                {
                    printInColor("red", "");
                    printf("player O Wins\n");
                    printInColor("white", "");
                    return;
                }
                else if (!board_is_full(brd))
                {

                    int i = 0, j = 0;
                    make_move(brd, true, &i, &j);
                    print_board(brd);
                    int checked = check_win(brd);

                    if (checked == 1)
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
    }
}

void player_vs_smart_ai_mini_max(board brd)
{
    bool win = false;
    bool turn = true; // computer starts
    bool first_move = true;

    while (!win)
    {
        bool is_full = board_is_full(brd);
        if (!is_full)
        {
            if (turn)
            {
                best_move(brd, first_move);
                first_move = false;

                print_board(brd);

                if (evaluate(brd) == 1)
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
                    add_to_board(brd, row, col, PLAYER);
                    print_board(brd);

                    if (evaluate(brd) == -1)
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
