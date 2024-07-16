#ifndef KING_H
#define KING_H
#include "piece.h"

class King : public Piece {
  bool didFirstMove;
  public:
    King(bool isWhite);
    bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
    void setDidFirstMove();
    bool getDidFirstMove();
};

#endif