#include "helpers.h"

void printInColor(char *color, char *text)
{
    if (strcmp(color, "black") == 0)
        printf("\033[0;30m");

    if (strcmp(color, "red") == 0)
        printf("\033[1;31m");

    if (strcmp(color, "green") == 0)
        printf("\033[0;32m");

    if (strcmp(color, "yellow") == 0)
        printf("\033[1;33m");

    if (strcmp(color, "blue") == 0)
        printf("\033[0;34m");

    if (strcmp(color, "purple") == 0)
        printf("\033[0;35m");

    if (strcmp(color, "cyan") == 0)
        printf("\033[0;36m");

    if (strcmp(color, "white") == 0)
        printf("\033[0;37m");

    printf("%s", text);
}

void flush_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}
void request_cofig(int *size, int *mode)
{
    printInColor("blue", "\n\n---------------------------------------------------------------------------\n");
    printf(" [TP] MIN_MAX ALGORITHM & TIC_TAC_TEO \n");
    printf("---------------------------------------------------------------------------\n");

    printInColor("white", "please choose the board size (3 for 3x3) :\n");

    scanf("%d", size);
    while (*size <= 2)
    {
        printf("- board size should be greather than 2 ! \n");
        printf("please reenter the board size :\n ");
        scanf("%d", size);
    }

    printInColor("green", "");
    printf("board size is set to [%dX%d] \n\n", *size, *size);

    printInColor("blue", "---------------------------------------------------------------------------\n");
    printf(" [TP] GAME MODE \n");
    printf("---------------------------------------------------------------------------\n");

    printInColor("white", "please choose game mode:\n");
    printf("-[1] for player vs player normal mode\n");
    printf("-[2] for player vs computer normal mode \n");
    printf("-[3] for player vs computer smartAI Machine start the game (MIN_MAX)\n");
    printf("-[4] for player vs computer smartAI Player start the game (MIN_MAX)\n");
    printf("---------------------------------------------------------------------------\n");
    scanf("%d", mode);

    while (*mode <= 0 || *mode > 5)
    {
        printInColor("red", "please choose the correct option ! \n");
        printInColor("white", " ");
        scanf("%d", mode);
    }

    printInColor("green", "");
    printf("MODE set to No:[%d]\n", *mode);
    printInColor("white", "");
}

int generate_random(int upper, int lower)
{
    return (rand() % (upper - lower + 1) + lower);
}