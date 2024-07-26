#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Board;

class Queen : public Piece {
  public:
    Queen(const bool isWhite);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const override;
    vector<vector<int>> getLegalMoves(vector<int> current, const Board &board, bool checkForCheckmate) const override;
};

#endif