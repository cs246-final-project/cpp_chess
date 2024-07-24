#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Board;

class Bishop : public Piece {
  public:
    Bishop(const bool isWhite);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board, bool recursive) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif