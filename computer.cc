#include "computer.h"

Computer::Computer(const bool isWhite, const int level): isWhite{isWhite}, level{level} {};

int Computer::getLevel() const {
  return level;
}

bool Computer::getIsWhite() const {
  return isWhite;
}
