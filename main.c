#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./board/board.h"
#include "./helpers/helpers.h"
#include "./play/play.h"
#include "./gfx/gfx.h"
#include <unistd.h>

#define width 500
#define height 500
#define EPS 30
void draw_cercle(struct gfx_context_t *ctxt, int column, int row, uint32_t radius, uint32_t color)
{
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  8 octant de notre cercle
        gfx_putpixel(ctxt, row + x, column - y, color);
        gfx_putpixel(ctxt, row + x, column + y, color);
        gfx_putpixel(ctxt, row - x, column - y, color);
        gfx_putpixel(ctxt, row - x, column + y, color);
        gfx_putpixel(ctxt, row + y, column - x, color);
        gfx_putpixel(ctxt, row + y, column + x, color);
        gfx_putpixel(ctxt, row - y, column - x, color);
        gfx_putpixel(ctxt, row - y, column + x, color);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 3;
        }
        else
        {
            --x;
            tx += 3;
            error += (tx - diameter);
        }
    }
}
int capture_event_addr(int x, int y)
{
    if (x <= (width / 3) && y <= (height / 3))
        return 1;
    else if (x <= (width / 3) && y > (height / 3) && y <= (height / 3) * 2)
    {
        return 4;
    }
    else if (x <= (width / 3) && y > (height / 3) * 2)
    {
        return 7;
    }

    if ((x > (width / 3) && x <= (width / 3) * 2) && y <= (height / 3))
        return 2;

    else if ((x > (width / 3) && x <= (width / 3) * 2) && y > (height / 3) && y <= (height / 3) * 2)
    {
        return 5;
    }
    else if ((x > (width / 3) && x <= (width / 3) * 2) && y > (height / 3) * 2 && y <= height)
    {
        return 8;
    }

    if (x > (width / 3 * 2) && y <= (height / 3))
        return 3;

    else if (x > (width / 3 * 2) && y > (height / 3) && y <= (height / 3 * 2))
    {
        return 6;
    }
    else if (x > (width / 3 * 2) && y > (height / 3 * 2) && y <= height)
    {
        return 9;
    }
    return 0;
}

void display()
{
    struct gfx_context_t *ctxt = gfx_create("TIC_TAC_TEO", width, height);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        // return EXIT_FAILURE;
    }

    SDL_ShowCursor(true);

    SDL_SetRenderDrawColor(ctxt->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctxt->renderer);
    SDL_SetRenderDrawColor(ctxt->renderer, 255, 255, 255, 255);
    // int reponse = SDL_RenderDrawLine(ctxt->renderer, 0, 166, 500, 166);

    // two horizontal lines
    SDL_RenderDrawLine(ctxt->renderer, 0, width / 3, height, width / 3);
    SDL_RenderDrawLine(ctxt->renderer, 0, 2 * (width / 3), width, 2 * (width / 3));

    // two vertical line
    SDL_RenderDrawLine(ctxt->renderer, (width / 3), 0, (width / 3), height);
    SDL_RenderDrawLine(ctxt->renderer, 2 * (width / 3), 0, 2 * (width / 3), height);

    // load image
    // SDL_Surface *lettuce_sur = IMG_Load("lettuce.png");
    // load image
    // SDL_Event e;
    SDL_RenderPresent(ctxt->renderer);

    int x, y;
    while (gfx_keypressed() != SDLK_ESCAPE)
    {
        // gfx_present(ctxt);

        Uint32 button;

        // button = SDL_GetRelativeMouseState(&y, &x);
        button = SDL_GetMouseState(&x, &y);
        if (button == SDL_BUTTON_LMASK)
        {
            int dd = capture_event_addr(x, y);

            if (dd == 1)
            {
                SDL_SetRenderDrawColor(ctxt->renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(ctxt->renderer, 0 + EPS, 0 + EPS, (height / 3) - EPS, (width / 3) - EPS);
                SDL_RenderDrawLine(ctxt->renderer, 0 + EPS, (height / 3) - EPS, (width / 3) - EPS, 0 + EPS);

                // SDL_RenderClear(ctxt->renderer);
                // draw_cercle(ctxt, 75, 75, 50, COLOR_RED);
                SDL_RenderPresent(ctxt->renderer);
                printf("case numéro : %d\n", dd);
            }
            // sleep(0.2);
        }
        // sleep(0.5);
    }
    // SDL_RenderPresent(ctxt->renderer);
    gfx_destroy(ctxt);
    // return EXIT_SUCCESS;
}
int main()
{

    // display();
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
        smart_ai_min_max(brd);
        break;
    default:
        break;
    }

    board_destroy(brd);

    return 0;
}