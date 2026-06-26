#include "BSAI24066_Knight.h"
#include "BSAI24066_Board.h"
#include <iostream>

using namespace std;

Knight::Knight(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool Knight::isLegalMove(Position S, Position D)
{
    int x = S.x - D.x;
    int y = S.y - D.y;
    if ((x * x) + (y * y) == 5)
        return true;
    return false;
}

void Knight::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

bool Knight::isKnight() const
{
    return true;
}

void Knight::Draw()
{
    if (color == White)
        cout << "n";
    else
        cout << "N";
}