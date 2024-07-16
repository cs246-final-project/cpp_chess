#include "board.h"

bool Board::validBoard(){
  int numWKings = 0;
  int numBKings = 0;
  for(int i = 0; i < boardWidth; ++i){
    if(dynamic_cast<Pawn*>(board[0][i]) != nullptr || dynamic_cast<Pawn*>(board[7][i]) != nullptr){
      return false;
    }
  }
  for(auto piecePos : aliveWhite){
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)]) != nullptr){
      ++numWKings;
    }
  }
  for(auto piecePos : aliveBlack){
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)]) != nullptr){
      ++numBKings;
    }
  }
  if(numWKings != 1 || numBKings != 1) return false;
  /* CHECK IF KINGS ARE IN CHECK */
}
void Board::place(char piece, int posx, int posy){
  
}
void Board::remove(int posx, int posy){

}

