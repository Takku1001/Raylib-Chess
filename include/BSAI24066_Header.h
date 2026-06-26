#ifndef HEADER_H
#define HEADER_H

#include <iostream>

void gotoRowCol(int rpos, int cpos);
void get_row_col_by_click(int& rpos, int& cpos);
void color(int k);

enum Clr
{
    Black, White
};

struct Position
{
    int x, y;
};

#endif