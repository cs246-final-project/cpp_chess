#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Queen : public Piece {
  public:
    Queen(const bool isWhite);
    bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif