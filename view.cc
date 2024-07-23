#include "view.h"

void View::displayBoard(const Board &board){
  for(int i = 0; i < boardHeight; i++){
    cout << 8 - i << ' ';
    for(int j = 0; j < boardWidth; j++){
      Piece* p = board.pieceAt(j, i);
      if(p == nullptr){
        (j)%2 == 0 ? cout << '_' : cout << ' ';
      } else {
        char c = getPieceChar(p);
        if(p->getIsWhite()) c -= 'a'-'A';
        cout << c;
      }
    }
    cout << endl;
  }
  cout << "  abcdefgh" << endl;
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