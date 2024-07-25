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
      if (other.board[j][i]) {
        row[j] = other.board[j][i]->clone();
      }
    }
    board.push_back(move(row));
  }
  history = other.history;
}

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

Piece* Board::pieceAt(int x, int y) const {
  return board[y][x].get();
}

bool Board::colorInCheck(bool isWhite, vector<int> kingPos) const {
  for(auto pos : (isWhite ? aliveBlack : aliveWhite)){
    if(pieceAt(pos[0], pos[1])->isMoveLegal(pos[0], pos[1], kingPos[0], kingPos[1], *this, true)) return true;
  }
  return false;
}

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

bool Board::isCheckMate(bool checkWhite) const {
  Board tempBoard = *this;
  vector<vector<int>> positions = (checkWhite ? tempBoard.aliveWhite : tempBoard.aliveBlack);
  int moveCount = 0;

  std::cout << positions.size() << " pieces" << endl;

  for(auto pos : positions){
    Piece* p = tempBoard.pieceAt(pos[0], pos[1]);
    vector<vector<int>> possibleMoves = p->getLegalMoves(pos, tempBoard);
    std::cout << "piecePos: " << pos[0] << " " << pos[1] << endl;
    for(auto move : possibleMoves){
      ++moveCount;
      std::cout << "possible move: " << move[0] << " " << move[1] << endl;
      tempBoard.movePiece(pos[0], pos[1], move[0], move[1]);
      if(!(tempBoard.colorInCheck(checkWhite))){
        return false;
      }
      tempBoard = *this;
    }
  }
  std::cout << moveCount << " moves" << endl;
  return true;
}

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

vector<vector<int>> Board::movePiece (int x, int y, int toX, int toY){
  if (pieceAt(x,y) == nullptr) return {};
  if (x == toX && y == toY) return {};
  vector<vector<int>> changedPositions = {{x, y}, {toX, toY}};
  if (pieceAt(x,y)->isMoveLegal(x, y, toX, toY, *this, false)){
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
    // if the move is castling, move the rook
    if (dynamic_cast<King*>(pieceAt(toX, toY)) != nullptr && abs(x - toX) == 2){
      if (toX > x){
        board[toY][toX - 1] = move(board[toY][7]);
        changedPositions.push_back({toX - 1, toY});
        changedPositions.push_back({7, toY});
      } else {
        board[toY][toX + 1] = move(board[toY][0]);
        changedPositions.push_back({toX + 1, toY});
        changedPositions.push_back({0, toY});
      }
    }
    return changedPositions;
  }
  return {};
}

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

void Board::movePieceWithoutValidation(int x, int y, int toX, int toY) {
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
  // if the move is castling, move the rook
  if (dynamic_cast<King*>(pieceAt(toX, toY)) != nullptr && abs(x - toX) == 2){
    if (toX > x){
      board[toY][toX - 1] = move(board[toY][7]);
    } else {
      board[toY][toX + 1] = move(board[toY][0]);
    }
  }
}

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

vector<vector<int>> Board::lastMove() const {
  return history.getLast();
}

bool Board::willCheck(int x, int y, int toX, int toY) const {
  Board temp = *this;
  temp.movePieceWithoutValidation(x, y, toX, toY);
  if (temp.colorInCheck(pieceAt(x, y)->getIsWhite())) return true;
  return false;
}

bool Board::willCheck(vector<int> from, vector<int> to) const {
  return willCheck(from[0], from[1], to[0], to[1]);
}

vector<vector<int>> Board::getAliveWhite() const {
  return aliveWhite;
};
vector<vector<int>> Board::getAliveBlack() const {
  return aliveBlack;
};

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

vector<vector<vector<int>>> Board::getAllPossibleMoves(const bool isWhite) const {
  vector<vector<vector<int>>> possibleMoves;
  for (auto ele : (isWhite ? aliveWhite : aliveBlack)) {
    cout << ele[0] << "," << ele[1] << endl;
    if (pieceAt(ele[0], ele[1])) {
      vector<vector<int>> moves = pieceAt(ele[0], ele[1])->getLegalMoves({ele[1], ele[0]}, &board);
      for (auto move : moves) {
        possibleMoves.push_back({ele, move});
      }
    } else {
      cout << "no piece in the pointer" << endl;
    }
  }
  return possibleMoves;
}
