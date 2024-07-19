#ifndef VIEW_H
#define VIEW_H
#include "board.h"
#include <iostream>

class View {
  char getPieceChar(Piece* p);
  public:
    void displayBoard(const Board &board);
    void update(vector<vector<int>> coords);
};

#endif