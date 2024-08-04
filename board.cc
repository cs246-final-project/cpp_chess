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

// clone the board
Board Board::clone() const {
  Board newBoard(*this);
  return newBoard;
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

vector<vector<int>> Board::getAliveWhite() const {
  return aliveWhite;
};
vector<vector<int>> Board::getAliveBlack() const {
  return aliveBlack;
};

// get the piece at the given position
Piece* Board::pieceAt(int x, int y) const {
  return board[y][x].get();
}

// check if the color is in check
bool Board::colorInCheck(bool isWhite, vector<int> kingPos) const {
  for(auto pos : (isWhite ? aliveBlack : aliveWhite)){
    if(pieceAt(pos[0], pos[1])->isMoveLegal(pos[0], pos[1], kingPos[0], kingPos[1], *this, true)) return true;
  }
  return false;
}

// check if the color is in check
bool Board::colorInCheck(bool isWhite) const {
  vector<int> kingPos;
  for(auto pos : (isWhite ? aliveWhite : aliveBlack)){
    if(dynamic_cast<King*>(pieceAt(pos[0], pos[1])) != nullptr){
      kingPos = pos;
      break;
    }
  }
  return colorInCheck(isWhite, kingPos);
}

// check if the color is in checkmate or stalemate
bool Board::cantMove(bool isWhite) const {
  Board tempBoard = *this;
  vector<vector<int>> positions = (isWhite ? tempBoard.aliveWhite : tempBoard.aliveBlack);

  for(auto pos : positions){
    Piece* p = pieceAt(pos[0], pos[1]);
    vector<vector<int>> possibleMoves = p->getLegalMoves(pos, tempBoard, true);
    for(auto move : possibleMoves){
      tempBoard.movePieceWithoutValidation(pos[0], pos[1], move[0], move[1]);
      if(!(tempBoard.colorInCheck(isWhite))){
        return false;
      }
      tempBoard = *this;
    }
  }
  return true;
}

// check if it is a valid board
bool Board::validBoard() const {
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
    if(dynamic_cast<King*>(board[pos[1]][pos[0]].get()) != nullptr){
      whiteKingPos = pos;
      ++numWKings;
    }
  }
  for(auto pos : aliveBlack){ // number of black kings
    if(dynamic_cast<King*>(board[pos[1]][pos[0]].get()) != nullptr){
      blackKingPos = pos;
      ++numBKings;
    }
  }
  if(numWKings != 1 || numBKings != 1){
    return false; // if either side does not have exactly one king
  }
  if(colorInCheck(true, whiteKingPos) || colorInCheck(false, blackKingPos)){
    return false;
  }
  return true;
}

// move the piece from (x, y) to (toX, toY)
vector<vector<int>> Board::movePiece (int x, int y, int toX, int toY){
  if (pieceAt(x,y) == nullptr) return {};
  if (x == toX && y == toY) return {};
  vector<vector<int>> changedPositions = {{x, y}, {toX, toY}};
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this, false)){
    if (pieceAt(toX, toY) != nullptr){
      remove(toX, toY);
    } else if (dynamic_cast<Pawn*>(pieceAt(x, y)) != nullptr && abs(x - toX) > 0 && pieceAt(toX, toY) == nullptr){
      remove(toX, y);
      changedPositions.push_back({toX, y});
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
    // if the move is castling, move the rook
    if (dynamic_cast<King*>(pieceAt(toX, toY)) != nullptr && abs(x - toX) == 2){
      if (toX > x){
        removePieceFromAlive(7, toY);
        board[toY][toX - 1] = move(board[toY][7]);
        addPieceToAlive(toX - 1, toY);
        changedPositions.push_back({toX - 1, toY});
        changedPositions.push_back({7, toY});
      } else {
        removePieceFromAlive(0, toY);
        board[toY][toX + 1] = move(board[toY][0]);
        addPieceToAlive(toX + 1, toY);
        changedPositions.push_back({toX + 1, toY});
        changedPositions.push_back({0, toY});
      }
    }
    return changedPositions;
  }
  return {};
}

// move the piece from (x, y) to (toX, toY) with promotion
vector<vector<int>> Board::movePiece (int x, int y, int toX, int toY, char promotion){
  if (pieceAt(x,y) == nullptr) return {};
  if (x == toX && y == toY) return {};
  vector<vector<int>> changedPositions = {{x, y}, {toX, toY}};
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this, false)){
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
    return changedPositions;
  }
  return {};
}

// move the piece from (x, y) to (toX, toY) without validation. For computer or checking for checkmate usage only.
// risky to use this function as it does not check if the move is legal
void Board::movePieceWithoutValidation(int x, int y, int toX, int toY) {
  if (pieceAt(toX, toY) != nullptr){
    remove(toX, toY);
  } else if (dynamic_cast<Pawn*>(pieceAt(x, y)) != nullptr && abs(x - toX) > 0 && pieceAt(toX, toY) == nullptr){
    remove(toX, y);
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
  // if the move is castling, move the rook
  if (dynamic_cast<King*>(pieceAt(toX, toY)) != nullptr && abs(x - toX) == 2){
    if (toX > x){
      board[toY][toX - 1] = move(board[toY][7]);
    } else {
      board[toY][toX + 1] = move(board[toY][0]);
    }
  }
}

// check if the move is a promotion move
bool Board::checkPromotion(int x, int y, int toX, int toY) const {
  if (pieceAt(x, y) == nullptr) return false;
  if (dynamic_cast<Pawn*>(pieceAt(x, y)) == nullptr) return false;
  if (pieceAt(x, y)->getIsWhite() && toY == 0) {
    return true;
  }
  if (!(pieceAt(x, y)->getIsWhite()) && toY == boardHeight - 1) {
    return true;
  }
  return false;
}

// place the piece at the given position
void Board::place(unique_ptr<Piece> p, int posX, int posY){
  if (pieceAt(posX, posY)) {
    remove(posX, posY);
  }
  board[posY][posX] = move(p);
  addPieceToAlive(posX, posY);
}

// remove the piece at the given position
void Board::remove(int posX, int posY){
  if(!board[posY][posX]) return;
  removePieceFromAlive(posX, posY);
  board[posY][posX].reset(nullptr);
}

// get the last move from history
vector<vector<int>> Board::lastMove() const {
  return history.getLast();
}

// check if the move will put the king in check
bool Board::willCheck(vector<int> from, vector<int> to) const {
  return true;
}

// remove the piece from alive vector
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

// add the piece to alive vector
void Board::addPieceToAlive(int x, int y) {
  if (pieceAt(x, y)->getIsWhite()){
    aliveWhite.emplace_back(vector<int>{x, y});
  } else {
    aliveBlack.emplace_back(vector<int>{x, y});
  }
};

// get the point of the board
int Board::getPoint(bool isWhite) const {
  int point = 0;
  for(auto pos : (isWhite ? aliveWhite : aliveBlack)){
    point += pieceAt(pos[0], pos[1])->getPoint();
  }
  for(auto pos : (isWhite ? aliveBlack : aliveWhite)){
    point -= pieceAt(pos[0], pos[1])->getPoint();
  }
  return point;
};
