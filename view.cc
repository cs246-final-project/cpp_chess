#include "view.h"

void View::displayBoard(const Board &board){
  for(int i = 0; i < boardWidth; i++){
    for(int j = 0; j < boardHeight; j++){
      Piece* p = board.pieceAt(i, j);
      if(p == nullptr){
        (i+j)%2 == 0 ? cout << ' ' : cout << '_';
      } else {
        char c = getPieceChar(p);
        if(!p->getIsWhite()) c -= 'a'-'A';
        cout << c;
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
  if(dynamic_cast<Pawn*>(p) != nullptr) return 'p';
  if(dynamic_cast<Rook*>(p) != nullptr) return 'r';
  if(dynamic_cast<Knight*>(p) != nullptr) return 'n';
  if(dynamic_cast<Bishop*>(p) != nullptr) return 'b';
  if(dynamic_cast<Queen*>(p) != nullptr) return 'q';
  if(dynamic_cast<King*>(p) != nullptr) return 'k';
}