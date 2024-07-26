#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Board;

class Bishop : public Piece {
  public:
    Bishop(const bool isWhite);
    unique_ptr<Piece> clone() const override;
    bool isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const override;
    vector<vector<int>> getLegalMoves(vector<int> current, const Board &board, bool checkForCheckmate) const override;
    vector<vector<int>> getCaptureMoves(vector<int> current, const Board &board) const override;
};

#endif