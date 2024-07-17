#ifndef BOARD_H
#define BOARD_H
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "history.h"
#include <vector>
using namespace std;

const int boardWidth = 8;
const int boardLength = 8;

class Board {
	unique_ptr<Piece> board[boardWidth][boardLength];
	vector<vector<int>> aliveWhite;
	vector<vector<int>> aliveBlack;
	unique_ptr<History> history;

	public:
		Piece* pieceAt(int x, int y);

		vector<vector<int>> getAliveWhite();
		vector<vector<int>> getAliveBlack();

		bool movePiece(int x, int y, int toX, int toY);
		bool movePiece(int x, int y, int toX, int toY, char promotion);

		bool validBoard();

		void place(char piece, int posx, int posy);
		void remove(int posx, int posy);

		vector<vector<int>> lastMove();

		bool willCheck(vector<int> from, vector<int> to);

		Board(const Board &other);
		Board();

};

#endif