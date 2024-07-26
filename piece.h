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
  bool getIsWhite() const;
  int getPoint() const;
  virtual vector<vector<int>> getLegalMoves(vector<int> current, const Board &board, bool checkForCheckmate) const = 0;
  virtual bool isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const = 0;
  virtual vector<vector<int>> getCaptureMoves(vector<int> current, const Board &board) const = 0;
};

#endif
