#include "computer.h"

Computer::Computer(bool isWhite): isWhite{isWhite} {};

bool Computer::getIsWhite() const {
  return isWhite;
}
