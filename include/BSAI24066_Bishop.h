#ifndef BISHOP_H
#define BISHOP_H

#include "BSAI24066_Piece.h"

class Bishop : public Piece
{
public:
    Bishop(int x, int y, Clr _c, Board* B);
    bool isLegalMove(Position S, Position D) override;
    void move(const Position& S, const Position& D) override;
    void Draw() override;
    bool isBishop() const override;
};

#endif