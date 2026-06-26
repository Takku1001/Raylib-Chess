#include "Rook.h"
#include "Board.h"
#include <iostream>

using namespace std;

Rook::Rook(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool Rook::isLegalMove(Position S, Position D)
{
    // A rook moves any number of squares along a rank or file,
    // and may not jump over intervening pieces.
    return (isHorizontalMove(S, D, board) && isHorizontalPC(S, D, board)) ||
        (isVerticalMove(S, D, board) && isVerticalPC(S, D, board));
}

void Rook::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

bool Rook::isRook() const
{
    return true;
}

void Rook::Draw()
{
    if (color == White)
        cout << "r";
    else
        cout << "R";
}
