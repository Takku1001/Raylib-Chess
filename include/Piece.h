#ifndef PIECE_H
#define PIECE_H

#include "Utils.h"

class Board;

class Piece
{
protected:
    Position position;
    Clr color;
    Board* board;

    static bool isHorizontalMove(Position S, Position D, Board* B);
    static bool isVerticalMove(Position S, Position D, Board* B);
    static bool isDiagonalMove(Position S, Position D, Board* B);

    static bool isHorizontalPC(Position S, Position D, Board* B);
    static bool isVerticalPC(Position S, Position D, Board* B);

    static bool isLDiagonalPC(Position S, Position D, Board* B);
    static bool isRDiagonalPC(Position S, Position D, Board* B);
    static bool isDiagonalPC(Position S, Position D, Board* B);

public:
    Piece(int x, int y, Clr _c, Board* B);
    virtual ~Piece() = default;


    Position getPosition() const
    {
        return position;
    }
    Clr getColor() 
    {
        return color;
    }

    virtual bool isLegalMove(Position S, Position D) = 0;
    virtual void move(const Position& S, const Position& D);
    virtual void Draw() = 0;
    virtual bool isKing() const
    {
        return false;
    }

    virtual bool isPawn() const 
    {
        return false; 
    }

    virtual bool isQueen() const
    {
        return false;
    }

    virtual bool isRook() const
    {
        return false;
    }

    virtual bool isBishop() const
    {
        return false;
    }

    virtual bool isKnight() const
    {
        return false;
    }
};

#endif