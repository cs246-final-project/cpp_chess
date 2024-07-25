#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "computer.h"

class Computer1 : public Computer {
  int level;
  bool isWhite;
  public:
    Computer1(const bool isWhite);
    ~Computer1() = default;
    vector<vector<int>> getMove(Board &board) override;
};

#endif
