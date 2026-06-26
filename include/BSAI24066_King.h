#ifndef KING_H
#define KING_H

#include "BSAI24066_Piece.h"

class Board;

class King : public Piece
{
public:
    King(int x, int y, Clr _c, Board* B);
    bool isLegalMove(Position S, Position D) override;
    void move(const Position& S, const Position& D) override;
    void Draw() override;
    bool isKing() const override;
};

#endif