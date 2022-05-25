
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifndef _HELPERS_
#define _HELPERS_

void printInColor(char *color, char *text);
void flush_input();

void request_cofig(int *size, int *mode);

int generate_random(int upper, int lower);

#endif