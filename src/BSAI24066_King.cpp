#include "BSAI24066_King.h"
#include "BSAI24066_Board.h"
#include <iostream>

using namespace std;

King::King(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool King::isLegalMove(Position S, Position D)
{

    int X = abs(S.x - D.x);
    int Y = abs(S.y - D.y);

    bool isValidMove = (isHorizontalMove(S, D, board) && isHorizontalPC(S, D, board)) ||
        (isVerticalMove(S, D, board) && isVerticalPC(S, D, board)) ||
        (isDiagonalMove(S, D, board) && isDiagonalPC(S, D, board));

    bool isOne = (X <= 1 && Y <= 1);

    return isValidMove && isOne;
}

void King::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

bool King::isKing() const 
{
    return true;
}

void King::Draw()
{
    if (color == White)
        cout << "k";
    else
        cout << "K";
}