#ifndef BOARD_H
#define BOARD_H

#include "Utils.h"
#include <iostream>

class Piece;
class Rook;
class Knight;
class Bishop;
class Queen;
class King;
class Pawn;

class Board
{
    Piece* pieces[8][8];

    Piece* lastCapturedPiece;
    Position lastCapturePosition;
public:
    Board();
    virtual ~Board();

    void addPiece(Piece* piece, int x, int y);
    Piece* getPiece(int x, int y) const;
    void movePiece(Position S, Position D);
    void undoMove(Position source, Position destination);
    void recordCapture(Piece* capturedPiece, Position position);
    void DisplayBoard();
    void SelectCoordinates(Position& P);
    bool isSourceValid(Position P, int currentPlayerColor) const;
    bool isDestValid(Position S, Position D, int currentPlayerColor) const;
    void TurnMessage(Clr turn);
    void ChangeTurn(Clr& x);
    bool** CalculateHighlight(Position S,Clr X);
    void HighlightValidMoves(bool** HMAP);
    Position findKing(Clr kingColor) const;
    void displayErrorS(const Position& P, int currentPlayerColor);

    bool isCheck(Clr kingColor);
    bool isCheckmate(Clr Turn);
    bool SelfCheck(Clr Turn);
    bool isStalemate(Clr playerColor);

    void checkForPromotion(Position position);
    bool tryTemporaryMove(Position src, Position dst, Clr playerColor);

};

#endif