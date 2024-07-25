#include "piece.h"
#include "board.h"

Piece::Piece(const bool isWhite, const int point): isWhite(isWhite), point(point) {};

bool Piece::getIsWhite() const {
  return isWhite;
}

int Piece::getPoint() const {
  return point;
}
