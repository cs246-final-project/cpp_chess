#ifndef PAWN_H
#define PAWN_H
#include "piece.h"

class Pawn : public Piece {
  bool didFirstMove;
  public:
    Pawn(const bool isWhite);
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
    void setDidFirstMove();
    bool getDidFirstMove();
};

#endif