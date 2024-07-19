#ifndef BOARD_H
#define BOARD_H
#include "history.h"
#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <vector>
using namespace std;

const int boardWidth = 8;
const int boardHeight = 8;

class Piece; // forward declaration

class Board {
	vector<vector<unique_ptr<Piece>>> board;
	vector<vector<int>> aliveWhite;
	vector<vector<int>> aliveBlack;
	unique_ptr<History> history;
	

	public:
		Board();
		~Board() = default;
		Piece* pieceAt(int x, int y) const;

		vector<vector<int>> getAliveWhite();
		vector<vector<int>> getAliveBlack();

		bool movePiece(int x, int y, int toX, int toY);
		bool movePiece(int x, int y, int toX, int toY, char promotion);

		bool colorInCheck(bool isWhite, vector<int> kingPos);

		bool validBoard();

		void place(unique_ptr<Piece> p, int posx, int posy);
		void remove(int posx, int posy);
		void removePieceFromAlive(int x, int y);
		void addPieceToAlive(int x, int y);

		vector<vector<int>> lastMove();

		bool willCheck(vector<int> from, vector<int> to);

		Board(const Board &other);
};

#endif