#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Board::Board()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            pieces[i][j] = nullptr;
            if (i == 1)
            {
                pieces[i][j] = new Pawn(i, j, Black, this);
            }
            else if (i == 6)
            {
                pieces[i][j] = new Pawn(i, j, White, this);
            }
            else if (i == 0)
            {
                if (j == 0 || j == 7)
                    pieces[i][j] = new Rook(i, j, Black, this);
                else if (j == 1 || j == 6)
                    pieces[i][j] = new Knight(i, j, Black, this);
                else if (j == 2 || j == 5)
                    pieces[i][j] = new Bishop(i, j, Black, this);
                else if (j == 3)
                    pieces[i][j] = new Queen(i, j, Black, this);
                else if (j == 4)
                    pieces[i][j] = new King(i, j, Black, this);
            }
            else if (i == 7)
            {
                if (j == 0 || j == 7)
                    pieces[i][j] = new Rook(i, j, White, this);
                else if (j == 1 || j == 6)
                    pieces[i][j] = new Knight(i, j, White, this);
                else if (j == 2 || j == 5)
                    pieces[i][j] = new Bishop(i, j, White, this);
                else if (j == 3)
                    pieces[i][j] = new Queen(i, j, White, this);
                else if (j == 4)
                    pieces[i][j] = new King(i, j, White, this);
            }
        }
    }
}

void Board::addPiece(Piece* piece, int x, int y)
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        pieces[x][y] = piece;
    }
}

Piece* Board::getPiece(int x, int y) const
{
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
    {
        return pieces[x][y];
    }
    return nullptr;
}
void Board::movePiece(Position S, Position D)
{
    Piece* piece = getPiece(S.x, S.y);
    if (piece && piece->isLegalMove({ S }, { D }))
    {
        Piece* capturedPiece = getPiece(D.x, D.y);
        if (capturedPiece != nullptr)
        {
            recordCapture(capturedPiece, D);
        }
        else
        {
            lastCapturedPiece = nullptr;
        }

        piece->move({ S }, { D });
        pieces[D.x][D.y] = piece;
        pieces[S.x][S.y] = nullptr;
    }
    checkForPromotion(D);
}


void Board::recordCapture(Piece* capturedPiece, Position position)
{
    if (lastCapturedPiece != nullptr)
    {
        delete lastCapturedPiece;
    }

    lastCapturedPiece = capturedPiece;
    lastCapturePosition = position;
}

void Board::undoMove(Position source, Position destination)
{
    Piece* piece = getPiece(destination.x, destination.y);
    if (piece)
    {
        piece->move({ destination }, { source });
        pieces[source.x][source.y] = piece;

        if (lastCapturedPiece != nullptr &&
            lastCapturePosition.x == destination.x &&
            lastCapturePosition.y == destination.y)
        {
            pieces[destination.x][destination.y] = lastCapturedPiece;
            lastCapturedPiece = nullptr; 
        }
        else
        {
            pieces[destination.x][destination.y] = nullptr;
        }
    }
}

void Board::DisplayBoard()
{
    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            if (pieces[ri][ci] != nullptr)
            {
                pieces[ri][ci]->Draw();
            }
            else
            {
                cout << "_";
            }
        }
        cout << endl;
    }
}

bool Board::isSourceValid(Position P, int currentPlayerColor) const
{
    if (P.x < 0 || P.x >= 8 || P.y < 0 || P.y >= 8)
    {
        return false;
    }

    Piece* piece = getPiece(P.x, P.y);

    if (piece == nullptr)
    {
        return false;
    }

    if (piece->getColor() != currentPlayerColor)
    {
        return false;
    }

    return true;
}

void Board::displayErrorS(const Position& P, int currentPlayerColor)
{
    if (P.x < 0 || P.x >= 8 || P.y < 0 || P.y >= 8)
    {
        cout << "Invalid Source" << endl;
        return;
    }

    Piece* piece = getPiece(P.x, P.y);
    if (piece == nullptr)
    {
        cout << "No Piece Selected" << endl;
        return;
    }

    if (piece->getColor() != currentPlayerColor)
    {
        cout << "Selecting Wrong Piece" << endl;
        return;
    }
}

bool Board::isDestValid(Position P, Position D, int currentPlayerColor) const
{
    if (D.x < 0 || D.x >= 8 || D.y < 0 || D.y >= 8)
    {
        return false;
    }

    Piece* destPiece = getPiece(D.x, D.y);
    if (destPiece == nullptr)
        return true;

    return destPiece->getColor() != currentPlayerColor;
}

bool** Board::CalculateHighlight(Position S, Clr Color)
{
    Position D;
    bool** MAP = new bool* [8];
    for (int i = 0; i < 8; i++)
    {
        MAP[i] = new bool[8] {};
    }
    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            D.x = ri;
            D.y = ci;
            if (isDestValid(S, D, Color) && getPiece(S.x, S.y)->isLegalMove(S, D))
            {
                MAP[ri][ci] = true;
            }
            else
            {
                MAP[ri][ci] = false;
            }
        }
    }
    return MAP;
}

Position Board::findKing(Clr kingColor) const
{
    Position kingPos = { -1, -1 };
    for (int ri = 0; ri < 8; ri++) 
    {
        for (int ci = 0; ci < 8; ci++)
        {
            Piece* piece = getPiece(ri, ci);
            if (piece && piece->isKing() && piece->getColor() == kingColor) {
                kingPos.x = ri;
                kingPos.y = ci;
                return kingPos;
            }
        }
    }
    return kingPos;
}

bool Board::isCheck(Clr PlayerColor)
{
    ChangeTurn(PlayerColor);
    Position opponentKingPos = findKing(PlayerColor);
    ChangeTurn(PlayerColor);

    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            Position src = { ri, ci };

            if (isSourceValid(src, PlayerColor))
            {
                if (isDestValid(src, opponentKingPos, PlayerColor) &&
                    getPiece(src.x, src.y)->isLegalMove(src, opponentKingPos))
                {
                    return true; 
                }
            }
        }
    }

    return false; 
}

bool Board::isCheckmate(Clr playerColor)
{
    if (!SelfCheck(playerColor))
    {
        return false;  
    }

    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            Position src = { ri, ci };

            if (isSourceValid(src, playerColor))
            {
                for (int di = 0; di < 8; di++)
                {
                    for (int dj = 0; dj < 8; dj++)
                    {
                        Position dest = { di, dj };

                        if (isDestValid(src, dest, playerColor))
                        {
                            Piece* selectedPiece = getPiece(src.x, src.y);

                            if (selectedPiece->isLegalMove(src, dest))
                            {
                                movePiece(src, dest);

                                bool stillInCheck = SelfCheck(playerColor);

                                undoMove(src, dest);

                                if (!stillInCheck)
                                {
                                    return false;  
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Board::isStalemate(Clr playerColor)
{
    if (SelfCheck(playerColor))
    {
        return false; 
    }

    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            Position src = { ri, ci };

            if (isSourceValid(src, playerColor))
            {
                for (int di = 0; di < 8; di++)
                {
                    for (int dj = 0; dj < 8; dj++)
                    {
                        Position dest = { di, dj };

                        if (isDestValid(src, dest, playerColor))
                        {
                            Piece* selectedPiece = getPiece(src.x, src.y);

                            if (selectedPiece->isLegalMove(src, dest))
                            {
                                movePiece(src, dest);

                                bool putsSelfInCheck = SelfCheck(playerColor);

                                undoMove(src, dest);

                                if (!putsSelfInCheck)
                                {
                                    return false;  
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}


bool Board::SelfCheck(Clr Turn)
{
    ChangeTurn(Turn);
    return isCheck(Turn);
}

bool Board::tryTemporaryMove(Position src, Position dst, Clr playerColor)
{
    Piece* movingPiece = getPiece(src.x, src.y);
    Piece* capturedPiece = getPiece(dst.x, dst.y);

    pieces[dst.x][dst.y] = movingPiece;
    pieces[src.x][src.y] = nullptr;

    bool stillInCheck = isCheck(playerColor);

    pieces[src.x][src.y] = movingPiece;
    pieces[dst.x][dst.y] = capturedPiece;

    return !stillInCheck;
}



void Board::HighlightValidMoves(bool** HMAP)
{
    for (int ri = 0; ri < 8; ri++)
    {
        for (int ci = 0; ci < 8; ci++)
        {
            if (HMAP[ri][ci])
            {
                color(12);

                if (pieces[ri][ci] != nullptr)
                {
                    pieces[ri][ci]->Draw();
                }
                else
                {
                    cout << "_";
                }

                color(7);
            }
            else
            {
                if (pieces[ri][ci] != nullptr)
                {
                    pieces[ri][ci]->Draw();
                }
                else
                {
                    cout << "_";
                }
            }
        }
        cout << endl;
    }
}


void Board::SelectCoordinates(Position& P)
{
    get_row_col_by_click(P.x, P.y);
}

void Board::TurnMessage(Clr turn)
{
    if (turn == White)
        cout << "White's turn(a-z)" << endl;
    else
        cout << "Black's turn(A-Z)" << endl;
}

void Board::ChangeTurn(Clr& x)
{
    if (x == White)
        x = Black;
    else
        x = White;
}



void Board::checkForPromotion(Position position)
{
    Piece* piece = getPiece(position.x, position.y);

    if (piece && piece->isPawn())
    {
        bool shouldPromote = false;

        if (piece->getColor() == White && position.x == 0)
        {
            shouldPromote = true;
        }
        else if (piece->getColor() == Black && position.x == 7)
        {
            shouldPromote = true;
        }

        if (shouldPromote)
        {
            int choice = 0;
            Clr pieceColor = piece->getColor();

            cout << "Pawn Promotion!" << endl;
            cout << "Choose a piece to promote to:" << endl;
            cout << "1. Queen" << endl;
            cout << "2. Rook" << endl;
            cout << "3. Bishop" << endl;
            cout << "4. Knight" << endl;

            do 
            {
                cin >> choice;
                if (choice < 1 || choice > 4)
                    cout << "Invalid choice. Enter 1-4: ";
            } while (choice < 1 || choice > 4);

            delete piece;

            switch (choice)
            {
            case 1:
                pieces[position.x][position.y] = new Queen(position.x, position.y, pieceColor, this);
                break;
            case 2:
                pieces[position.x][position.y] = new Rook(position.x, position.y, pieceColor, this);
                break;
            case 3:
                pieces[position.x][position.y] = new Bishop(position.x, position.y, pieceColor, this);
                break;
            case 4:
                pieces[position.x][position.y] = new Knight(position.x, position.y, pieceColor, this);
                break;
            }

            cout << "Pawn promoted successfully!" << endl;
        }
    }
}


Board::~Board()
{

}