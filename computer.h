#ifndef COMPUTER_H
#define COMPUTER_H

#include "board.h"

class Computer {
  bool isWhite;
  public:
    Computer(bool isWhite);
    ~Computer() = default;
    bool getIsWhite() const;
    virtual vector<vector<int>> getMove(const Board &board) const = 0;
};

#endif
