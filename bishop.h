#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Bishop : public Piece {
  public:
    Bishop(const bool isWhite);
    bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif