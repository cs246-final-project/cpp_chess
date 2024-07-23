#include "board.h"

Board::Board(bool empty) {
  for (int i = 0; i < boardHeight; ++i) {
    vector<unique_ptr<Piece>> row(boardWidth); // Create a row with boardLength elements
    for (int j = 0; j < boardWidth; ++j) {
      row[j] = nullptr; // Initialize each element as nullptr
    }
    board.push_back(move(row)); // Move the row into the board
  }
  // if setup mode, return empty board
  if (empty) return;
  // place pieces for initial board
  for (int i = 0; i < boardWidth; ++i) {
    unique_ptr<Piece> pBlack = make_unique<Pawn>(false);
    place(move(pBlack), i, 1);
    unique_ptr<Piece> pWhite = make_unique<Pawn>(true);
    place(move(pWhite), i, boardHeight - 2);
  }
  for (auto ele : initialRookPos) {
    unique_ptr<Piece> pRook = ele[1] == 0 ? make_unique<Rook>(false) : make_unique<Rook>(true);
    place(move(pRook), ele[0], ele[1]);
  }
  for (auto ele : initialKnightPos) {
    unique_ptr<Piece> pKnight = ele[1] == 0 ? make_unique<Knight>(false) : make_unique<Knight>(true);
    place(move(pKnight), ele[0], ele[1]);
  }
  for (auto ele : initialBishopPos) {
    unique_ptr<Piece> pBishop = ele[1] == 0 ? make_unique<Bishop>(false) : make_unique<Bishop>(true);
    place(move(pBishop), ele[0], ele[1]);
  }
  for (auto ele : initialQueenPos) {
    unique_ptr<Piece> pQueen = ele[1] == 0 ? make_unique<Queen>(false) : make_unique<Queen>(true);
    place(move(pQueen), ele[0], ele[1]);
  }
  for (auto ele : initialKingPos) {
    unique_ptr<Piece> pKing = ele[1] == 0 ? make_unique<King>(false) : make_unique<King>(true);
    place(move(pKing), ele[0], ele[1]);
  }
}

Board::Board(const Board &other) 
  : aliveWhite(other.aliveWhite), aliveBlack(other.aliveBlack) {
  for (int i = 0; i < boardHeight; ++i) {
    vector<unique_ptr<Piece>> row(boardWidth);
    for (int j = 0; j < boardWidth; ++j) {
      if (other.board[i][j]) {
        row[j] = other.board[i][j]->clone();
      }
    }
    board.push_back(move(row));
  }
  history = other.history;
}

Board& Board::operator=(const Board &other) {
  if (this == &other) {
    return *this;
  }
  Board temp(other);
  swap(board, temp.board);
  swap(aliveWhite, temp.aliveWhite);
  swap(aliveBlack, temp.aliveBlack);
  swap(history, temp.history);
  return *this;
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
    board[toY][toX] = move(board[y][x]);
    addPieceToAlive(toX, toY);
    if (dynamic_cast<Pawn*>(pieceAt(toX,toY)) != nullptr){
      dynamic_cast<Pawn*>(pieceAt(toX,toY))->setDidFirstMove();
    } else if (dynamic_cast<Rook*>(pieceAt(toX,toY)) != nullptr) {
      dynamic_cast<Rook*>(pieceAt(toX,toY))->setDidFirstMove();
    } else if (dynamic_cast<King*>(pieceAt(toX,toY)) != nullptr) {
      dynamic_cast<King*>(pieceAt(toX,toY))->setDidFirstMove();
    }
    history.addMove({x,y}, {toX, toY});
    return true;
  }
  return false;
}

bool Board::movePiece (int x, int y, int toX, int toY, char promotion){
  if (pieceAt(x,y) == nullptr) return false;
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this)){
    unique_ptr<Piece> p;
    switch (promotion){
      case 'Q':
        p = make_unique<Queen>(pieceAt(x, y)->getIsWhite());
        break;
      case 'R':
        p = make_unique<Rook>(pieceAt(x, y)->getIsWhite(), true);
        break;
      case 'N':
        p = make_unique<Knight>(pieceAt(x, y)->getIsWhite());
        break;
      case 'B':
        p = make_unique<Bishop>(pieceAt(x, y)->getIsWhite());
        break;
      default:
        throw "Invalid promotion!";
    }
    remove(x, y);
    place(move(p), toX, toY);
    history.addMove({x,y}, {toX, toY});
    return true;
  }
  return false;
}

bool Board::checkPromotion(int x, int y, int toX, int toY) {
  if (pieceAt(x, y) == nullptr) return false;
  if (dynamic_cast<Pawn*>(pieceAt(x, y)) == nullptr) return false;
  if (pieceAt(x, y)->getIsWhite() && toY == 0) {
    return true;
  }
  if (!(pieceAt(x, y)->getIsWhite()) && toY == boardHeight - 1) {
    return true;
  }
}

void Board::place(unique_ptr<Piece> p, int posX, int posY){
  if (pieceAt(posX, posY)) {
    remove(posX, posY);
  }
  board[posY][posX] = move(p);
  addPieceToAlive(posX, posY);
}

void Board::remove(int posX, int posY){
  removePieceFromAlive(posX, posY);
  board[posY][posX].reset(nullptr);
}

vector<vector<int>> Board::lastMove(){
  return history.getLast();
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
