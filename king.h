#ifndef KING_H
#define KING_H
#include "piece.h"

class Board;

class King : public Piece {
  bool didFirstMove;
  public:
    King(bool isWhite, bool didFirstMove = false);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, Board &board, bool recursive) override;
    vector<vector<int>> getLegalMoves(vector<int> current, Board &board) override;
    void setDidFirstMove();
    bool getDidFirstMove();
};

#endif