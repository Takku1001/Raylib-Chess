#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Board;

class Knight : public Piece
{
public:
    Knight(int x, int y, Clr _c, Board* B);
    bool isLegalMove(Position S, Position D) override;
    void move(const Position& S, const Position& D) override;
    void Draw() override;
    bool isKnight() const override;
};

#endif