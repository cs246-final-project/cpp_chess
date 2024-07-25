#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Board;

class Knight : public Piece {
  public:
    Knight(const bool isWhite);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const override;
    vector<vector<int>> getLegalMoves(vector<int> current, const Board &board) const override;
};

#endif