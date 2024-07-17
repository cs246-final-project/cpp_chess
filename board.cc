#include "board.h"

Piece* Board::pieceAt(int x, int y){
  return board[x][y].get();
}

bool Board::validBoard(){
  int numWKings = 0;
  int numBKings = 0;
  for(int i = 0; i < boardWidth; ++i){
    if(dynamic_cast<Pawn*>(board[0][i].get()) != nullptr || dynamic_cast<Pawn*>(board[7][i].get()) != nullptr){
      return false;
    }
  }
  for(auto piecePos : aliveWhite){
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)].get()) != nullptr){
      ++numWKings;
    }
  }
  for(auto piecePos : aliveBlack){
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)].get()) != nullptr){
      ++numBKings;
    }
  }
  if(numWKings != 1 || numBKings != 1) return false;
  /* CHECK IF KINGS ARE IN CHECK */
}
bool Board::movePiece (int x, int y, int toX, int toY){
  if (pieceAt(x,y) == nullptr) return false;

  return true;
}
bool Board::movePiece (int x, int y, int toX, int toY, char promotion){
  return true;
}
void Board::place(char piece, int posx, int posy){

  switch(piece){
    case 'p':
      
      break;
    case 'r':
      break;
    case 'n':
      break;
    case 'b':
      break;
    case 'q':
      break;
    case 'k':
      break;
    case 'P':
      break;
    case 'R':
      break;
    case 'N':
      break;
    case 'B':
      break;
    case 'Q':
      break;
    case 'K':
      break;
  }
}
void Board::remove(int posx, int posy){

}
vector<vector<int>> Board::lastMove(){
  return history->getLast();
}
bool Board::willCheck(vector<int> from, vector<int> to){
  return true;
}
