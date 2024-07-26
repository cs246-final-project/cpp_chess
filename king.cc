#include "king.h"
#include "board.h"

int kingPoints = 900;

King::King(const bool isWhite, bool didFirstMove): Piece(isWhite, kingPoints), didFirstMove{didFirstMove} {};

unique_ptr<Piece> King::clone() const {
  return make_unique<King>(*this);
}

// get if the King has moved. If true, the King cannot castle
bool King::getDidFirstMove() const {
  return didFirstMove;
}

// set the King to have moved
// TODO: if King is checked, set didFirstMove to true
void King::setDidFirstMove() {
  didFirstMove = true;
}

// Check if the move is legal for the King
// all current and to should be guaranteed to be in the board
bool King::isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const {
  if (x == toX && y == toY) return false;
  // check if the move would put the king in check
  if (!recursive) {
    Board temp = board;
    temp.movePieceWithoutValidation(x, y, toX, toY);
    if (temp.colorInCheck(this->getIsWhite(), {toX, toY})) return false;
  }
  // check if the move is castling
  if (!didFirstMove && y == toY && abs(x - toX) == 2) {
    if (board.colorInCheck(this->getIsWhite(), {x, y})) return false;
    if (toX > x) {
      for (int i = x + 1; i < boardWidth - 1; ++i) {
        if (board.pieceAt(i, y) != nullptr) {
          return false;
        }
        // check if the move would put the king in check
        if (!recursive) {
          Board temp = board;
          temp.movePieceWithoutValidation(x, y, i, toY);
          if (temp.colorInCheck(this->getIsWhite(), {i, toY})) return false;
        }
      }
      if (dynamic_cast<Rook*>(board.pieceAt(boardWidth - 1, y)) != nullptr && !(dynamic_cast<Rook*>(board.pieceAt(boardWidth - 1, y))->getDidFirstMove())){
        return true;
      }
    } else {
      for (int i = x - 1; i > 0; --i) {
        if (board.pieceAt(i, y) != nullptr) {
          return false;
        }
      }
      if (dynamic_cast<Rook*>(board.pieceAt(0, y)) != nullptr && !(dynamic_cast<Rook*>(board.pieceAt(0, y))->getDidFirstMove())){
        return true;
      }
    }
  }
  // false if the destination is same as current location
  if (abs(x - toX) > 1 || abs(y - toY) > 1) {
    return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(toX, toY) != nullptr && board.pieceAt(toX, toY)->getIsWhite() == this->getIsWhite()) {
    return false;
  }
  return true;
}

// Get all the legal next moves for the King
// current should be guaranteed to be in the board
vector<vector<int>> King::getLegalMoves(vector<int> current, const Board &board, bool checkForCheckmate) const {
  vector<vector<int>> legalMoves;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      // skip the current position
      if (i == 0 && j == 0) continue;
      int newX = current[0] + i;
      int newY = current[1] + j;
      if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) continue;
      // false if the destination has a piece of the same color
      if (board.pieceAt(newX, newY) != nullptr && board.pieceAt(newX, newY)->getIsWhite() == this->getIsWhite()) continue;
      legalMoves.push_back({newX, newY});
    }
  }
  if (!didFirstMove) {
    if (board.pieceAt(0, current[1]) != nullptr && dynamic_cast<Rook*>(board.pieceAt(0, current[1])) != nullptr && !(dynamic_cast<Rook*>(board.pieceAt(0, current[1]))->getDidFirstMove())) {
      bool canCastle = true;
      for (int i = 1; i < current[0]; ++i) {
        if (board.pieceAt(i, current[1]) != nullptr) {
          canCastle = false;
          break;
        }
      }
      if (canCastle) {
        legalMoves.push_back({current[0] - 2, current[1]});
      }
    }
    if (board.pieceAt(boardWidth - 1, current[1]) != nullptr && dynamic_cast<Rook*>(board.pieceAt(boardWidth - 1, current[1])) != nullptr && !(dynamic_cast<Rook*>(board.pieceAt(boardWidth - 1, current[1]))->getDidFirstMove())) {
      bool canCastle = true;
      for (int i = current[0] + 1; i < boardWidth - 1; ++i) {
        if (board.pieceAt(i, current[1]) != nullptr) {
          canCastle = false;
          break;
        }
      }
      if (canCastle) {
        legalMoves.push_back({current[0] + 2, current[1]});
      }
    }
  }
  if (checkForCheckmate) {
    return legalMoves;
  }
  vector<vector<int>> legalMovesWithoutCheck;
  for (auto ele: legalMoves) {
    Board temp = board;
    temp.movePieceWithoutValidation(current[0], current[1], ele[0], ele[1]);
    if (!temp.colorInCheck(this->getIsWhite())) {
      legalMovesWithoutCheck.push_back(ele);
    }
  }
  return legalMovesWithoutCheck;
}

vector<vector<int>> King::getCaptureMoves(vector<int> current, const Board &board) const {
  vector<vector<int>> legalMoves;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      // skip the current position
      if (i == 0 && j == 0) continue;
      int newX = current[0] + i;
      int newY = current[1] + j;
      if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) continue;
      if (board.pieceAt(newX, newY) != nullptr && board.pieceAt(newX, newY)->getIsWhite() != this->getIsWhite()) {
        legalMoves.push_back({newX, newY});
      }
    }
  }
  return legalMoves;
}
