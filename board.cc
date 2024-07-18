#include "board.h"

Board::Board() : board{boardWidth, vector<std::unique_ptr<Piece>>(boardLength, nullptr)}{}

Piece* Board::pieceAt(int x, int y) const {
  return board[x][y].get();
}

bool Board::validBoard(){
  int numWKings = 0;
  int numBKings = 0;
  for(int i = 0; i < boardWidth; ++i){ // if any pawns in row 0 or row 7
    if(dynamic_cast<Pawn*>(board[0][i].get()) != nullptr || dynamic_cast<Pawn*>(board[7][i].get()) != nullptr){
      return false;
    }
  }
  for(auto piecePos : aliveWhite){ // number of white kings
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)].get()) != nullptr){
      ++numWKings;
    }
  }
  for(auto piecePos : aliveBlack){ // number of black kings
    if(dynamic_cast<King*>(board[piecePos.at(0)][piecePos.at(1)].get()) != nullptr){
      ++numBKings;
    }
  }
  if(numWKings != 1 || numBKings != 1) return false; // if either side does not have exactly one king
  /* 

    CHECK IF KINGS ARE IN CHECK 

  */
}

bool Board::movePiece (int x, int y, int toX, int toY){
  if (pieceAt(x,y) == nullptr) return false;
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this)){
    if (pieceAt(toX, toY) != nullptr){
      Piece *p = pieceAt(toX, toY);
      if (pieceAt(toX, toY)->getIsWhite()){
        // remove vector{toX, toY} from aliveWhite
        aliveWhite.erase(std::remove_if(aliveWhite.begin(), aliveWhite.end(), [&](const vector<int>& pos) {
            return pos == vector<int>{toX, toY};
        }), aliveWhite.end());
      } else {
        // remove vector{toX, toY} from aliveBlack
        aliveBlack.erase(std::remove_if(aliveBlack.begin(), aliveBlack.end(), [&](const vector<int>& pos) {
            return pos == vector<int>{toX, toY};
        }), aliveBlack.end());
      }
    }
    board[toX][toY] = move(board[x][y]);
    return true;
  }
  return false;
}
bool Board::movePiece (int x, int y, int toX, int toY, char promotion){
  return true;
}
void Board::place(unique_ptr<Piece> p, int posx, int posy){
  p->getIsWhite() ? aliveWhite.emplace_back(vector<int>{posx, posy}) : aliveBlack.emplace_back(vector<int>{posx, posy});
  board.at(posx).at(posy) = move(p);
}
void Board::remove(int posx, int posy){

}
vector<vector<int>> Board::lastMove(){
  return history->getLast();
}
bool Board::willCheck(vector<int> from, vector<int> to){
  return true;
}
