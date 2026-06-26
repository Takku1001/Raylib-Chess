#include "BSAI24066_Bishop.h"
#include "BSAI24066_Board.h"
#include <iostream>

using namespace std;

Bishop::Bishop(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool Bishop::isLegalMove(Position S, Position D)
{
    if (!isDiagonalMove(S, D, board))
        return false;

    if ((S.x < D.x && S.y < D.y) || (S.x > D.x && S.y > D.y))
        return isLDiagonalPC(S, D, board);
    else
        return isRDiagonalPC(S, D, board);
}

void Bishop::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

bool Bishop::isBishop() const
{
    return true;
}

void Bishop::Draw()
{
    if (color == White)
        cout << "b";
    else
        cout << "B";
}