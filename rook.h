#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Board;

class Rook : public Piece {
  bool didFirstMove;
  public:
    Rook(bool isWhite);
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
    void setDidFirstMove();
    bool getDidFirstMove();
};

#endif