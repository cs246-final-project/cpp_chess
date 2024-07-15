#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include <vector>
using namespace std;

const int boardWidth = 8;
const int boardLength = 8;

class Board {
	Piece* b[boardWidth][boardLength];

	public:
		Piece* pieceAt(int x, int y);
		bool movePiece(int x, int y, int toX, int toY);
		bool movePiece(int x, int y, int toX, int toY, char promotion);

};

#endif