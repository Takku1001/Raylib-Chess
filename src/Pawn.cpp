#include "Pawn.h"
#include "Board.h"
#include <iostream>

using namespace std;

Pawn::Pawn(int x, int y, Clr _c, Board* B) : Piece(x, y, _c, B)
{
}

bool Pawn::isLegalMove(Position S, Position D)
{
    int dx = D.x - S.x;  
    int dy = D.y - S.y;

    if (color == White)
    {
        if (dx == -1 && dy == 0 && board->getPiece(D.x, D.y) == nullptr)
            return true;

        if (S.x == 6 && dx == -2 && dy == 0 &&
            board->getPiece(D.x, D.y) == nullptr &&
            board->getPiece(S.x - 1, S.y) == nullptr)
            return true;

        if (dx == -1 && (dy == -1 || dy == 1) &&
            board->getPiece(D.x, D.y) != nullptr &&
            board->getPiece(D.x, D.y)->getColor() == Black)
            return true;
    }
    else 
    {
        if (dx == 1 && dy == 0 && board->getPiece(D.x, D.y) == nullptr)
            return true;

        if (S.x == 1 && dx == 2 && dy == 0 &&
            board->getPiece(D.x, D.y) == nullptr &&
            board->getPiece(S.x + 1, S.y) == nullptr)
            return true;

        if (dx == 1 && (dy == -1 || dy == 1) &&
            board->getPiece(D.x, D.y) != nullptr &&
            board->getPiece(D.x, D.y)->getColor() == White)
            return true;
    }

    return false;
}

bool Pawn::isPawn() const
{
    return true; 
}

void Pawn::move(const Position& S, const Position& D)
{
    if (isLegalMove(S, D))
    {
        Piece::move(S, D);
    }
}

void Pawn::Draw()
{
    if (color == White)
        cout << "p";
    else
        cout << "P";
}