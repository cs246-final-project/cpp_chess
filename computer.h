#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.h"

class Computer {
  int level;
  bool isWhite;
  public:
    Computer(const bool isWhite, const int level);
    ~Computer() = default;
    int getLevel();
    bool getIsWhite();
    virtual vector<vector<int>> getMove(Board &board) = 0;
};

#endif
