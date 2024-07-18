#include "board.h"

Board::Board() : board{boardWidth, vector<std::unique_ptr<Piece>>(boardLength, nullptr)}{}

Piece* Board::pieceAt(int x, int y) const {
  return board[x][y].get();
}

bool Board::colorInCheck(bool isWhite, vector<int> kingPos){
  for(auto pos : (isWhite ? aliveBlack : aliveWhite)){
    if(pos != kingPos){
      if(board[pos[0]][pos[1]].get()->isMoveLegal(pos[0], pos[1], kingPos[0], kingPos[1], *this)) return false;
    }
  }
}

bool Board::validBoard(){
  int numWKings = 0;
  int numBKings = 0;
  vector<int> whiteKingPos;
  vector<int> blackKingPos;
  for(int i = 0; i < boardWidth; ++i){ // if any pawns in row 0 or row 7
    if(dynamic_cast<Pawn*>(board[0][i].get()) != nullptr || dynamic_cast<Pawn*>(board[7][i].get()) != nullptr){
      return false;
    }
  }
  for(auto pos : aliveWhite){ // number of white kings
    if(dynamic_cast<King*>(board[pos[0]][pos[1]].get()) != nullptr){
      whiteKingPos = pos;
      ++numWKings;
    }
  }
  for(auto pos : aliveBlack){ // number of black kings
    if(dynamic_cast<King*>(board[pos[0]][pos[1]].get()) != nullptr){
      blackKingPos = pos;
      ++numBKings;
    }
  }
  if(numWKings != 1 || numBKings != 1) return false; // if either side does not have exactly one king
  if(colorInCheck(true, whiteKingPos) || colorInCheck(false, blackKingPos)) return false;
  return true;
}

bool Board::movePiece (int x, int y, int toX, int toY){
  if (pieceAt(x,y) == nullptr) return false;
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this)){
    if (pieceAt(toX, toY) != nullptr){
      remove(toX, toY);
    }
    removePieceFromAlive(x, y);
    board[toX][toY] = move(board[x][y]);
    addPieceToAlive(toX, toY);
    return true;
  }
  return false;
}
bool Board::movePiece (int x, int y, int toX, int toY, char promotion){
  return true;
}
void Board::place(unique_ptr<Piece> p, int posx, int posy){
  if (pieceAt(posx, posy)) {
    remove(posx, posy);
  }
  addPieceToAlive(posx, posy);
  board.at(posx).at(posy) = move(p);
}
void Board::remove(int posx, int posy){
  removePieceFromAlive(posx, posy);
  board[posx][posy].reset(nullptr);
  
}
vector<vector<int>> Board::lastMove(){
  return history->getLast();
}
bool Board::willCheck(vector<int> from, vector<int> to){
  return true;
}

void Board::removePieceFromAlive(int x, int y) {
  if (pieceAt(x, y)->getIsWhite()){
    // remove vector{toX, toY} from aliveWhite
    aliveWhite.erase(std::remove_if(aliveWhite.begin(), aliveWhite.end(), [&](const vector<int>& pos) {
        return pos == vector<int>{x, y};
    }), aliveWhite.end());
  } else {
    // remove vector{toX, toY} from aliveBlack
    aliveBlack.erase(std::remove_if(aliveBlack.begin(), aliveBlack.end(), [&](const vector<int>& pos) {
        return pos == vector<int>{x, y};
    }), aliveBlack.end());
  }
}

void Board::addPieceToAlive(int x, int y) {
  if (pieceAt(x, y)->getIsWhite()){
    aliveWhite.emplace_back(vector<int>{x, y});
  } else {
    aliveBlack.emplace_back(vector<int>{x, y});
  }
};
