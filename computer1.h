#ifndef COMPUTER1_H
#define COMPUTER1_H
#include "computer.h"

class Computer1 : public Computer {
  public:
    Computer1(const bool isWhite);
    ~Computer1() = default;
    vector<vector<int>> getMove(const Board &board) const override;
};

#endif
