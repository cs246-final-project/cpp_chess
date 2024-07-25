#ifndef KING_H
#define KING_H
#include "piece.h"

class Board;

class King : public Piece {
  bool didFirstMove;
  public:
    King(bool isWhite, bool didFirstMove = false);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const override;
    vector<vector<int>> getLegalMoves(vector<int> current, const Board &board) const override;
    void setDidFirstMove();
    bool getDidFirstMove() const;
};

#endif