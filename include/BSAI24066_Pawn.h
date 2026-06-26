#ifndef PAWN_H
#define PAWN_H

#include "BSAI24066_Piece.h"

class Board;

class Pawn : public Piece
{
public:
    Pawn(int x, int y, Clr _c, Board* B);
    bool isLegalMove(Position S, Position D) override;
    void move(const Position& S, const Position& D) override;
    void Draw() override;
    bool isPawn() const override;
};

#endif