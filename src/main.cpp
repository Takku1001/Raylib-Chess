
#include "raylib.h"
#include "Board.h"
#include "Piece.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Utils.h"
#include <string>
#include <map>
#include <sstream>


const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 900;
const int BOARD_SIZE = SCREEN_HEIGHT;  
const int SQUARE_SIZE = BOARD_SIZE / 8;
const int BOARD_OFFSET_X = (SCREEN_WIDTH - BOARD_SIZE) / 2;
const int BOARD_OFFSET_Y = 0;  
const Color BACKGROUND_COLOR = { 0, 0, 0, 255 };  
const Color TEXT_COLOR = LIME;  


struct ChessTextures 
{
    Texture2D whitePawn;
    Texture2D whiteRook;
    Texture2D whiteKnight;
    Texture2D whiteBishop;
    Texture2D whiteQueen;
    Texture2D whiteKing;
    Texture2D blackPawn;
    Texture2D blackRook;
    Texture2D blackKnight;
    Texture2D blackBishop;
    Texture2D blackQueen;
    Texture2D blackKing;
    Texture2D board;
};


ChessTextures LoadChessTextures() {
    ChessTextures textures;


    textures.board = LoadTexture("assets/ChessBoard.png");


    textures.whitePawn = LoadTexture("assets/White_Pawn.png");
    textures.whiteRook = LoadTexture("assets/White_Rook.png");
    textures.whiteKnight = LoadTexture("assets/White_Knight.png");
    textures.whiteBishop = LoadTexture("assets/White_Bishop.png");
    textures.whiteQueen = LoadTexture("assets/White_Queen.png");
    textures.whiteKing = LoadTexture("assets/White_King.png");


    textures.blackPawn = LoadTexture("assets/Black_Pawn.png");
    textures.blackRook = LoadTexture("assets/Black_Rook.png");
    textures.blackKnight = LoadTexture("assets/Black_Knight.png");
    textures.blackBishop = LoadTexture("assets/Black_Bishop.png");
    textures.blackQueen = LoadTexture("assets/Black_Queen.png");
    textures.blackKing = LoadTexture("assets/Black_King.png");

    return textures;
}

Texture2D GetPieceTexture(Piece* piece, const ChessTextures& textures) {
    if (piece) {
        if (piece->isPawn()) {
            return (piece->getColor() == White) ? textures.whitePawn : textures.blackPawn;
        }
        else if (piece->isRook()) {
            return (piece->getColor() == White) ? textures.whiteRook : textures.blackRook;
        }
        else if (piece->isKnight()) {
            return (piece->getColor() == White) ? textures.whiteKnight : textures.blackKnight;
        }
        else if (piece->isBishop()) {
            return (piece->getColor() == White) ? textures.whiteBishop : textures.blackBishop;
        }
        else if (piece->isQueen()) {
            return (piece->getColor() == White) ? textures.whiteQueen : textures.blackQueen;
        }
        else if (piece->isKing()) {
            return (piece->getColor() == White) ? textures.whiteKing : textures.blackKing;
        }
    }
    return { 0 }; 
}

Rectangle GetSquareRect(int row, int col) {
    Rectangle rect;
    rect.x = BOARD_OFFSET_X + col * SQUARE_SIZE;
    rect.y = BOARD_OFFSET_Y + row * SQUARE_SIZE;
    rect.width = SQUARE_SIZE;
    rect.height = SQUARE_SIZE;
    return rect;
}

Position GetBoardPosition(Vector2 mousePos) {
    Position pos;
    int row = (mousePos.y - BOARD_OFFSET_Y) / SQUARE_SIZE;
    int col = (mousePos.x - BOARD_OFFSET_X) / SQUARE_SIZE;

    
    if (row < 0) row = 0;
    if (row > 7) row = 7;
    if (col < 0) col = 0;
    if (col > 7) col = 7;

    pos.x = row; 
    pos.y = col; 

    return pos;
}


void DrawChessBoard(Board& board, const ChessTextures& textures, bool** highlightMap = nullptr, Position selectedPos = { -1, -1 }) 
{
    
    Rectangle source = { 0, 0, (float)textures.board.width, (float)textures.board.height };
    Rectangle dest = { (float)BOARD_OFFSET_X, (float)BOARD_OFFSET_Y, (float)BOARD_SIZE, (float)BOARD_SIZE };
    DrawTexturePro(textures.board, source, dest, Vector2{ 0, 0 }, 0.0f, WHITE);

    
    if (highlightMap) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (highlightMap[row][col]) {
                    Rectangle rect = GetSquareRect(row, col);
                    DrawRectangleRec(rect, ColorAlpha(GREEN, 0.5f));
                }
            }
        }
    }

    
    if (selectedPos.x != -1 && selectedPos.y != -1) {
        Rectangle rect = GetSquareRect(selectedPos.x, selectedPos.y);
        DrawRectangleRec(rect, ColorAlpha(BLUE, 0.3f));
    }

    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = board.getPiece(row, col);
            if (piece) {
                Texture2D texture = GetPieceTexture(piece, textures);
                if (texture.id != 0) 
                {
                    Rectangle dest = GetSquareRect(row, col);

                    float scale = 0.85f * SQUARE_SIZE / (float)fmax(texture.width, texture.height);

                    float offsetX = (SQUARE_SIZE - texture.width * scale) / 2;
                    float offsetY = (SQUARE_SIZE - texture.height * scale) / 2;


                    Vector2 position = { dest.x + offsetX, dest.y + offsetY };
                    DrawTextureEx(texture, position, 0.0f, scale, WHITE);
                }
            }
        }
    }
}


int ShowPromotionDialog() 
{
    int choice = 1;  
    bool dialogActive = true;

    while (dialogActive) 
    {
        BeginDrawing();
        ClearBackground(ColorAlpha(BLACK, 0.7f));


        Rectangle dialogRect = { SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 125, 300, 250 };
        DrawRectangleRec(dialogRect, LIGHTGRAY);
        DrawRectangleLinesEx(dialogRect, 2, DARKGRAY);


        DrawText("Pawn Promotion", dialogRect.x + 60, dialogRect.y + 20, 20, RED);


        const char* options[] = { "1. Queen", "2. Rook", "3. Bishop", "4. Knight" };
        for (int i = 0; i < 4; i++) {
            Rectangle optionRect = { dialogRect.x + 20, dialogRect.y + 70 + i * 40, 260, 30 };
            DrawRectangleRec(optionRect, (choice == i + 1) ? SKYBLUE : RAYWHITE);
            DrawRectangleLinesEx(optionRect, 1, GRAY);
            DrawText(options[i], optionRect.x + 10, optionRect.y + 5, 20, RED);
        }

        EndDrawing();


        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            for (int i = 0; i < 4; i++) {
                Rectangle optionRect = { dialogRect.x + 20, dialogRect.y + 70 + i * 40, 260, 30 };
                if (CheckCollisionPointRec(mousePos, optionRect)) {
                    choice = i + 1;
                    dialogActive = false;
                    break;
                }
            }
        }

        if (IsKeyPressed(KEY_ONE)) { choice = 1; dialogActive = false; }
        if (IsKeyPressed(KEY_TWO)) { choice = 2; dialogActive = false; }
        if (IsKeyPressed(KEY_THREE)) { choice = 3; dialogActive = false; }
        if (IsKeyPressed(KEY_FOUR)) { choice = 4; dialogActive = false; }
        if (IsKeyPressed(KEY_ENTER)) { dialogActive = false; }
    }

    return choice;
}

void HandlePromotion(Board& board, Position position, Clr turn) {
    Piece* piece = board.getPiece(position.x, position.y);

    if (piece && piece->isPawn()) {
        bool shouldPromote = false;

        if (piece->getColor() == White && position.x == 0) {
            shouldPromote = true;
        }
        else if (piece->getColor() == Black && position.x == 7) {
            shouldPromote = true;
        }


        // NEW

        if (board.isCheck(turn))
        {
            shouldPromote = true;
        }

        if (shouldPromote) {
            int choice = ShowPromotionDialog();
            Clr pieceColor = piece->getColor();


            delete piece;

            
            switch (choice) {
            case 1: 
                board.addPiece(new Queen(position.x, position.y, pieceColor, &board), position.x, position.y);
                break;
            case 2: 
                board.addPiece(new Rook(position.x, position.y, pieceColor, &board), position.x, position.y);
                break;
            case 3: 
                board.addPiece(new Bishop(position.x, position.y, pieceColor, &board), position.x, position.y);
                break;
            case 4: 
                board.addPiece(new Knight(position.x, position.y, pieceColor, &board), position.x, position.y);
                break;
            }
        }
    }
}


using namespace std;

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess Game");
    SetTargetFPS(60);

    Board board;
    Clr turn = White;
    bool gameOver = false;
    bool pieceSelected = false;
    Position selectedPosition = { -1, -1 };
    Position targetPosition = { -1, -1 };
    bool** highlightMap = nullptr;
    string statusMessage = "White's turn";

    ChessTextures textures = LoadChessTextures();

    while (!WindowShouldClose()) 
    {
        if (!gameOver) {
            if (board.SelfCheck(turn) && board.isCheckmate(turn)) {
                string winner = (turn == White) ? "BLACK" : "WHITE";
                string loser = (turn == White) ? "WHITE" : "BLACK";
                statusMessage = loser + " IS CHECKMATED! " + winner + " WINS!";
                gameOver = true;
            }
            else if (!board.SelfCheck(turn) && board.isStalemate(turn)) {
                statusMessage = "STALEMATE! GAME ENDS IN A DRAW!";
                gameOver = true;
            }
        }

        if (!gameOver) {
            Vector2 mousePos = GetMousePosition();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int boardRow = (mousePos.y - BOARD_OFFSET_Y) / SQUARE_SIZE;
                int boardCol = (mousePos.x - BOARD_OFFSET_X) / SQUARE_SIZE;

                if (boardRow >= 0 && boardRow < 8 && boardCol >= 0 && boardCol < 8) {
                    Position boardPos = { boardRow, boardCol };

                    if (!pieceSelected) {
                        if (board.isSourceValid(boardPos, turn)) {
                            selectedPosition = boardPos;
                            pieceSelected = true;
                            highlightMap = board.CalculateHighlight(selectedPosition, turn);


                            cout << selectedPosition.x << " " << selectedPosition.y << endl;


                        }
                        else {
                            statusMessage = "Invalid selection";
                        }
                    }
                    else {
                        targetPosition = boardPos;

                        if (board.isDestValid(selectedPosition, targetPosition, turn)) {
                            Piece* selectedPiece = board.getPiece(selectedPosition.x, selectedPosition.y);
                            if (selectedPiece->isLegalMove(selectedPosition, targetPosition)) {
                                board.movePiece(selectedPosition, targetPosition);

                                if (board.SelfCheck(turn)) {
                                    board.undoMove(selectedPosition, targetPosition);
                                    statusMessage = "ILLEGAL MOVE:\nPUTS YOUR OWN KING\nIN CHECK";
                                }
                                else {
                                    HandlePromotion(board, targetPosition,turn);

                                    if (board.isCheck(turn))
                                    {
                                        string opponent = (turn == White) ? "BLACK" : "WHITE";
                                        statusMessage = opponent + " IN CHECK";
                                    }
                                    else
                                    {
                                        string nextPlayer = (turn == White) ? "Black's" : "White's";
                                        statusMessage = nextPlayer + " turn";
                                    }

                                    board.ChangeTurn(turn);
                                }
                            }
                            else {
                                statusMessage = "Invalid move";
                            }
                        }
                        else {
                            statusMessage = "Invalid destination";
                        }

                        if (highlightMap) {
                            for (int i = 0; i < 8; i++) delete[] highlightMap[i];
                            delete[] highlightMap;
                            highlightMap = nullptr;
                        }

                        pieceSelected = false;
                        selectedPosition = { -1, -1 };
                    }
                }
            }

            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && pieceSelected) {
                if (highlightMap) {
                    for (int i = 0; i < 8; i++) delete[] highlightMap[i];
                    delete[] highlightMap;
                    highlightMap = nullptr;
                }

                pieceSelected = false;
                selectedPosition = { -1, -1 };
                string currentPlayer = (turn == White) ? "White's" : "Black's";
                statusMessage = currentPlayer + " turn";
            }
        }


        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);

        DrawChessBoard(board, textures, highlightMap, pieceSelected ? selectedPosition : Position{ -1, -1 });
        DrawText(statusMessage.c_str(), 10, 10, 20, TEXT_COLOR);
        string turnText = (turn == White) ? "White's turn" : "Black's turn";
        DrawText(turnText.c_str(), SCREEN_WIDTH - 170, 10, 20, TEXT_COLOR);

        if (gameOver) {
            Rectangle msgBg = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 40, 400, 80 };
            DrawRectangleRec(msgBg, ColorAlpha(DARKGRAY, 0.7f));
            DrawRectangleLinesEx(msgBg, 2, WHITE); 
            
            
            int textWidth = MeasureText(statusMessage.c_str(), 20);
            DrawText(statusMessage.c_str(), msgBg.x + (msgBg.width - textWidth) / 2, msgBg.y + 10, 20, RED);
            DrawText("Press ESC to exit", msgBg.x + 100, msgBg.y + 45, 20, RED);

        }

        EndDrawing();
    }

    if (highlightMap) {
        for (int i = 0; i < 8; i++) 
            delete[] highlightMap[i];
        delete[] highlightMap;
    }


    CloseWindow();
    return 0;
}



