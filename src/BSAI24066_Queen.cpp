#include "BSAI24066_Queen.h"
#include "BSAI24066_Board.h"
#include <iostream>

using namespace std;

Queen::Queen(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool Queen::isLegalMove(Position S, Position D)
{
    bool rookMove = (isHorizontalMove(S, D, board) && isHorizontalPC(S, D, board)) ||
        (isVerticalMove(S, D, board) && isVerticalPC(S, D, board));

    bool bishopMove = false;
    if (isDiagonalMove(S, D, board)) 
    {
        if ((S.x < D.x && S.y < D.y) || (S.x > D.x && S.y > D.y))
            bishopMove = isLDiagonalPC(S, D, board);
        else
            bishopMove = isRDiagonalPC(S, D, board);
    }

    return rookMove || bishopMove;
}

void Queen::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

bool Queen::isQueen() const
{
    return true;
}

void Queen::Draw()
{
    if (color == White)
        cout << "q";
    else
        cout << "Q";
}