#ifndef PIECE_H
#define PIECE_H

#include <vector>
using namespace std;

class Board; // forward declaration

class Piece {
  int point;
  bool isWhite;
public:
  Piece(const bool isWhite, const int point);
  virtual ~Piece() = default;
  bool getIsWhite();
  int getPoint();
  virtual vector<vector<int>> getLegalMoves(vector<int> current, Board &board) = 0;
  virtual bool isMoveLegal(int x, int y, int toX, int toY, Board &board) = 0;
};

#endif
