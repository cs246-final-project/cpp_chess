#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "computer.h"

class Computer2 : public Computer {
  int level;
  bool isWhite;
  public:
    Computer2(const bool isWhite);
    ~Computer2() = default;
    vector<vector<int>> getMove(const Board &board) const override;
};

#endif
