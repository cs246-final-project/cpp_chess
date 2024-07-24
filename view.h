#ifndef VIEW_H
#define VIEW_H
#include "board.h"
#include "window.h"
#include <string>
#include <iostream>
#include <X11/Xlib.h>
#include <png.h>

class View {
  unique_ptr<Xwindow> w;
  Board *board;
  char getPieceChar(Piece* p);
  void drawTile(int row, int col, string piece, bool isWhite);
  string getPieceString(Piece* p);
  public:
    View(Board *board);
    void displayBoard();
    void update(vector<vector<int>> coords);
};

#endif