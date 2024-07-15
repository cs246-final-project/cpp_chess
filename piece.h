#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece {
  int point;
  bool isWhite;
public:
  Piece();
  bool getIsWhite();
  int getPoint();
  virtual ~Piece() = 0;
  virtual std::vector<std::vector<int>> getPossibleMoves(std::vector<int> current) = 0;
  virtual bool isMovePossible(std::vector<int> current, std::vector<int> to) = 0;
};

#endif
