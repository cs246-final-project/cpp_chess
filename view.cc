#include "view.h"

View::View(Board *board) : board{board}{
  w = make_unique<Xwindow>(boardWidth*60, boardHeight*60);
}

// display the entire board
void View::displayBoard(){
  for(int i = 0; i < boardHeight; i++){
    cout << 8 - i << " ";
    for(int j = 0; j < boardWidth; j++){
      int posX = j*60;
      int posY = i*60;
      Piece* p = board->pieceAt(j, i);
      if(p == nullptr){
        if((i+j)%2 == 0){
          w->fillRectangle(posX, posY, 60, 60, 0);
        } else {
          w->fillRectangle(posX, posY, 60, 60, 1);
        }
        (i+j)%2 == 0 ? cout << ' ' : cout << '_';
        if((i+j)%2 == 0){
          w->fillRectangle(posX, posY, 60, 60, 0);
        } else {
          w->fillRectangle(posX, posY, 60, 60, 1);
        }
      } else {
        char c = getPieceChar(p);
        cout << c;
        w->drawTile(j, i, getPieceString(p), p->getIsWhite());
      }
    }
    cout << endl;
  }
  cout << "  abcdefgh" << endl;
}

// update the board only for the given coordinates
void View::update(vector<vector<int>> coords){
  for(auto pos : coords){
    int i = pos[1];
    int j = pos[0];
    int posX = j*60;
    int posY = i*60;
    Piece* p = board->pieceAt(j, i);
    if(p == nullptr){
      if((i+j)%2 == 0){
        w->fillRectangle(posX, posY, 60, 60, 0);
      } else {
        w->fillRectangle(posX, posY, 60, 60, 1);
      }
    } else {
      w->drawTile(j, i, getPieceString(p), p->getIsWhite());
    }
  }
  for(int i = 0; i < boardHeight; i++){
    cout << 8 - i << " ";
    for(int j = 0; j < boardWidth; j++){
      Piece* p = board->pieceAt(j, i);
      if(p == nullptr){
        (i+j)%2 == 0 ? cout << ' ' : cout << '_';
      } else {
        char c = getPieceChar(p);
        cout << c;
      }
    }
    cout << endl;
  }
  cout << "  abcdefgh" << endl;
}

// display the winning message
void View::colourWins(bool isWhite){
  w->fillRectangle(50, 170, 380, 140, 3);
  w->fillRectangle(53, 173, 374, 134, 2);
  w->drawString(2, 210, 240, (isWhite ? "White wins." : "Black wins."));
}

// display the stalemate message
void View::draw(){
  w->fillRectangle(50, 170, 380, 140, 3);
  w->fillRectangle(53, 173, 374, 134, 2);
  w->drawString(2, 210, 240, "Stalemate.");
}

// get the character representation of the piece
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

// get the string representation of the piece
string View::getPieceString(Piece* p){
  if(dynamic_cast<Pawn*>(p) != nullptr) return "pawn";
  if(dynamic_cast<Rook*>(p) != nullptr) return "rook";
  if(dynamic_cast<Knight*>(p) != nullptr) return "knight";
  if(dynamic_cast<Bishop*>(p) != nullptr) return "bishop";
  if(dynamic_cast<Queen*>(p) != nullptr) return "queen";
  if(dynamic_cast<King*>(p) != nullptr) return "king";
  return "";
}
