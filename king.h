#ifndef KING_H
#define KING_H
#include "pieceDecorator.h"

class King : public PieceDecorator {
  bool castlingPossible;
};

#endif