#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Rook : public Piece {
  bool didFirstMove;
  public:
    Rook(bool isWhite);
    bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
    void setDidFirstMove();
};

#endif