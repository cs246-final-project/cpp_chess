#ifndef COMPUTER3_H
#define COMPUTER3_H
#include "computer.h"

class Computer3 : public Computer {
  public:
    Computer3(bool isWhite);
    ~Computer3() = default;
    vector<vector<int>> getMove(const Board &board) const override;
};

#endif
