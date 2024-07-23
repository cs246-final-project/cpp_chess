#include "view.h"

View::View(Board *board) : board{board}{
  w = make_unique<Xwindow>(boardWidth*60, boardHeight*60);
}

void View::displayBoard(const Board &board){
  for(int i = 0; i < boardWidth; i++){
    for(int j = 0; j < boardHeight; j++){
      int posX = i*60;
      int posY = j*60;
      if((i+j)%2 == 0){
        w->fillRectangle(posX, posY, 60, 60, 0);
      } else {
        w->fillRectangle(posX, posY, 60, 60, 1);
      }
      Piece* p = board.pieceAt(i, j);
      if(p == nullptr){
        (i+j)%2 == 0 ? cout << ' ' : cout << '_';
      } else {
        char c = getPieceChar(p);
        cout << c;
        w->drawTile(j, i, getPieceString(p), p->getIsWhite());
      }
    }
    cout << endl;
  }
}
void View::update(vector<vector<int>> coords){
  for(auto pos : coords){
    
  }
}

char View::getPieceChar(Piece* p){
  char c;
  if(dynamic_cast<Pawn*>(p) != nullptr) c = 'p';
  if(dynamic_cast<Rook*>(p) != nullptr) c = 'r';
  if(dynamic_cast<Knight*>(p) != nullptr) c = 'n';
  if(dynamic_cast<Bishop*>(p) != nullptr) c = 'b';
  if(dynamic_cast<Queen*>(p) != nullptr) c = 'q';
  if(dynamic_cast<King*>(p) != nullptr) c = 'k';
  if(p->getIsWhite()) c -= 'a' - 'A';
  return c;
}

string View::getPieceString(Piece* p){
  if(dynamic_cast<Pawn*>(p) != nullptr) return "pawn";
  if(dynamic_cast<Rook*>(p) != nullptr) return "rook";
  if(dynamic_cast<Knight*>(p) != nullptr) return "knight";
  if(dynamic_cast<Bishop*>(p) != nullptr) return "bishop";
  if(dynamic_cast<Queen*>(p) != nullptr) return "queen";
  if(dynamic_cast<King*>(p) != nullptr) return "king";
}
