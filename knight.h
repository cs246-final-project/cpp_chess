#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Knight : public Piece {
  public:
    Knight(const bool isWhite);
    bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
};

#endif