#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
  public:
    Queen(const bool isWhite);
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif