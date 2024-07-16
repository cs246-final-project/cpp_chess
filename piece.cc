#include "piece.h"

Piece::Piece(const bool isWhite, const int point): isWhite(isWhite), point(point) {};

Piece::~Piece() {}

bool Piece::getIsWhite() {
  return isWhite;
}

int Piece::getPoint() {
  return point;
}
