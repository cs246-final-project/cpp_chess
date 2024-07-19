#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Board;

class Knight : public Piece {
  public:
    Knight(const bool isWhite);
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif