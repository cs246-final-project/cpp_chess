#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.h"

class Computer {
  bool isWhite;
  int level;
  public:
    Computer(const bool isWhite, const int level);
    ~Computer() = default;
    int getLevel() const;
    bool getIsWhite() const;
    virtual vector<vector<int>> getMove(const Board &board) const = 0;
};

#endif
