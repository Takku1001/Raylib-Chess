#ifndef QUEEN_H
#define QUEEN_H

#include "BSAI24066_Piece.h"

class Board;

class Queen : public Piece
{
public:
    Queen(int x, int y, Clr _c, Board* B);
    bool isLegalMove(Position S, Position D) override;
    void move(const Position& S, const Position& D) override;
    void Draw() override;
    bool isQueen() const override;
};

#endif