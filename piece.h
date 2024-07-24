#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
using namespace std;

class Board; // forward declaration

class Piece {
  bool isWhite;
  int point;
public:
  Piece(const bool isWhite, const int point);
  virtual ~Piece() = default;
  virtual unique_ptr<Piece> clone() const = 0;
  bool getIsWhite();
  int getPoint();
  virtual vector<vector<int>> getLegalMoves(vector<int> current, Board &board) = 0;
  virtual bool isMoveLegal(int x, int y, int toX, int toY, Board &board, bool recursive) = 0;
};

#endif
