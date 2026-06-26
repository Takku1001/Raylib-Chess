#include "Piece.h"
#include "Board.h"
#include <iostream>

using namespace std;

Piece::Piece(int x, int y, Clr _c, Board* B) : position{ x, y }, color(_c), board(B)
{
}

bool Piece::isHorizontalMove(Position S, Position D, Board* B)
{
	return S.x == D.x;
}

bool Piece::isVerticalMove(Position S, Position D, Board* B)
{
	return S.y == D.y;
}

bool Piece::isDiagonalMove(Position S, Position D, Board* B)
{
	int x = S.x - D.x;
	int y = S.y - D.y;

	return abs(x) == abs(y);
}

bool Piece::isHorizontalPC(Position S, Position D, Board* B)
{
	int start, end;
	if (S.y < D.y)
	{
		start = S.y + 1;
		end = D.y - 1;
	}
	else
	{
		start = D.y + 1;
		end = S.y - 1;
	}
	for (int ci = start; ci <= end; ci++)
	{
		if (B->getPiece(S.x, ci) != nullptr)
			return false;
	}
	return true;
}

bool Piece::isVerticalPC(Position S, Position D, Board* B)
{
	int start, end;
	if (S.x < D.x)
	{
		start = S.x + 1;
		end = D.x - 1;
	}
	else
	{
		start = D.x + 1;
		end = S.x - 1;
	}
	for (int ri = start; ri <= end; ri++)
	{
		if (B->getPiece(ri, S.y) != nullptr)
			return false;
	}
	return true;
}


bool Piece::isLDiagonalPC(Position S, Position D, Board* B)
{
	int diff;
	if (S.x < D.x)
	{
		diff = D.x - S.x - 1;
		for (int n = 1; n <= diff; n++)
		{
			if (B->getPiece(S.x + n, S.y + n) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		diff = S.x - D.x - 1;
		for (int n = 1; n <= diff; n++)
		{
			if (B->getPiece(S.x - n, S.y - n) != nullptr)
				return false;
		}
		return true;
	}
}


bool Piece::isRDiagonalPC(Position S, Position D, Board* B)
{
	int diff;
	if (S.x < D.x)
	{
		diff = D.x - S.x - 1;
		for (int n = 1; n <= diff; n++)
		{
			if (B->getPiece(S.x + n, S.y - n) != nullptr)
				return false;
		}
		return true;
	}
	else
	{
		diff = S.x - D.x - 1;
		for (int n = 1; n <= diff; n++)
		{
			if (B->getPiece(S.x - n, S.y + n) != nullptr)
				return false;
		}
		return true;
	}
}

bool Piece::isDiagonalPC(Position S, Position D, Board* B)
{
	return isLDiagonalPC(S, D, B) || isRDiagonalPC(S, D, B);
}

void Piece::move(const Position& S, const Position& D)
{
	position.x = D.x;
	position.y = D.y;
}