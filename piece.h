#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include "board.h"

class Piece {
  int point;
  bool isWhite;
public:
  Piece(const bool isWhite, const int point);
  virtual ~Piece() = default;
  bool getIsWhite();
  int getPoint();
  virtual vector<vector<int>> getLegalMoves(vector<int> current, Board &board) = 0;
  virtual bool isMoveLegal(vector<int> current, vector<int> destination, Board &board) = 0;
};

#endif
