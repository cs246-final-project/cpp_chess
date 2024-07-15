#ifndef PIECEDECORATOR_H
#define PIECEDECORATOR_H
#include "piece.h"

class PieceDecorator : public Piece {
  Piece* piece;

public:
  PieceDecorator(Piece* p) : piece(p) {}
  virtual ~PieceDecorator() { delete piece; }
};

#endif
