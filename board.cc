#include "board.h"

Board::Board() {
  for (int i = 0; i < boardWidth; ++i) {
    std::vector<std::unique_ptr<Piece>> row(boardHeight); // Create a row with boardLength elements
    for (int j = 0; j < boardHeight; ++j) {
      row[j] = nullptr; // Initialize each element as nullptr
    }
    board.push_back(std::move(row)); // Move the row into the board
  }
}

Piece* Board::pieceAt(int x, int y) const {
  return board[y][x].get();
}

bool Board::colorInCheck(bool isWhite, vector<int> kingPos){
  for(auto pos : (isWhite ? aliveBlack : aliveWhite)){
    if(pieceAt(pos[0], pos[1])->isMoveLegal(pos[0], pos[1], kingPos[0], kingPos[1], *this)) return true;
  }
  return false;
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
  if(colorInCheck(true, blackKingPos) || colorInCheck(false, whiteKingPos)) return false;
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

void Board::place(unique_ptr<Piece> p, int posX, int posY){
  if (pieceAt(posX, posY)) {
    remove(posX, posY);
  }
  board[posX][posY] = move(p);
  addPieceToAlive(posX, posY);

}

void Board::remove(int posX, int posY){
  removePieceFromAlive(posX, posY);
  board[posX][posY].reset(nullptr);
  
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
    aliveWhite.erase(remove_if(aliveWhite.begin(), aliveWhite.end(), [&](const vector<int>& pos) {
        return pos == vector<int>{x, y};
    }), aliveWhite.end());
  } else {
    // remove vector{toX, toY} from aliveBlack
    aliveBlack.erase(remove_if(aliveBlack.begin(), aliveBlack.end(), [&](const vector<int>& pos) {
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
