#include "computer.h"

Computer::Computer(const bool isWhite, const int level): isWhite{isWhite}, level{level} {};

int Computer::getLevel() {
  return level;
}

bool Computer::getIsWhite() {
  return isWhite;
}
