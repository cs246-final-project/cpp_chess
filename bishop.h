#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
  public:
    Bishop(const bool isWhite);
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif