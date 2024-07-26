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
#include <iostream>
using namespace std;

const int boardWidth = 8;
const int boardHeight = 8;

const int kingRowPos = 4;

const vector<vector<int>> initialRookPos = {{0, 0}, {7, 0}, {0, 7}, {7, 7}};
const vector<vector<int>> initialKnightPos = {{1, 0}, {6, 0}, {1, 7}, {6, 7}};
const vector<vector<int>> initialBishopPos = {{2, 0}, {5, 0}, {2, 7}, {5, 7}};
const vector<vector<int>> initialQueenPos = {{3, 0}, {3, 7}};
const vector<vector<int>> initialKingPos = {{kingRowPos, 0}, {kingRowPos, 7}};

class Piece; // forward declaration

class Board {
	vector<vector<unique_ptr<Piece>>> board;
	vector<vector<int>> aliveWhite;
	vector<vector<int>> aliveBlack;
	History history;
	

	public:
		Board(bool empty = false);
		~Board() = default;

		Board(const Board &other);
		Board& operator=(const Board &other);
		Board clone() const;

		Piece* pieceAt(int x, int y) const;

		vector<vector<int>> getAliveWhite() const;
		vector<vector<int>> getAliveBlack() const;

		vector<vector<int>> movePiece(int x, int y, int toX, int toY);
		vector<vector<int>> movePiece(int x, int y, int toX, int toY, char promotion);
		void movePieceWithoutValidation(int x, int y, int toX, int toY);

		// use when move is already validated
		bool checkPromotion(int x, int y, int toX, int toY) const;

		bool colorInCheck(bool isWhite, vector<int> kingPos) const;
    bool colorInCheck(bool isWhite) const;
    bool cantMove(bool isWhite) const;

		bool validBoard() const;

		void place(unique_ptr<Piece> p, int posx, int posy);
		void remove(int posx, int posy);
		void removePieceFromAlive(int x, int y);
		void addPieceToAlive(int x, int y);

		vector<vector<int>> lastMove() const;

		bool willCheck(vector<int> from, vector<int> to) const;
};

#endif