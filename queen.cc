#include "queen.h"
#include "board.h"

int queenPoint = 90;

Queen::Queen(const bool isWhite): Piece(isWhite, queenPoint) {}

unique_ptr<Piece> Queen::clone() const {
  return make_unique<Queen>(new Queen{*this});
}

// Check if the move is legal for the Queen
// all current and to should be guaranteed to be in the board
bool Queen::isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const {
  // false if the destination is same as current location
  if (x == toX && y == toY) return false;
  // check if the move would put the king in check
  if (!recursive && board.willCheck(x, y, toX, toY)) {
    return false;
  }
  if (x == toX || y == toY) {
    // when moving like a rook
    // false if there is a piece in between
    if (x == toX) {
      int sign = y < toY ? 1 : -1;
      for (int i = 1; i < abs(y - toY); ++i) {
        if (board.pieceAt(x, y + i * sign) != nullptr) return false;
      }
    } else {
      int sign = x < toX ? 1 : -1;
      for (int i = 1; i < abs(x - toX); ++i) {
        if (board.pieceAt(x + i * sign, y) != nullptr) return false;
      }
    }
  } else if (abs(x - toX) == abs(y - toY)) {
    // when moving like a bishop
    // false if there is a piece in between
    int xSign = x < toX ? 1 : -1;
    int ySign = y < toY ? 1 : -1;
    for (int i = 1; i < abs(x - toX); ++i) {
      if (board.pieceAt(x + i * xSign, y + i * ySign) != nullptr) return false;
    }
  } else {
    return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(toX, toY) != nullptr && board.pieceAt(toX, toY)->getIsWhite() == this->getIsWhite()) return false;
  return true;
}

// Get all the legal next moves for the Queen
// current should be guaranteed to be in the board
vector<vector<int>> Queen::getLegalMoves(vector<int> current, const Board &board) const {
  vector<vector<int>> legalMoves;
  // Check in the direction in the same columns and rows (like a rook)
    for (int sign = -1; sign <= 1; sign += 2) {
    // Check in the direction in the same columns
    for (int k = 1; k < 8; ++k) {
      int newX = current[0] + k * sign;
      if (newX < 0 || newX >= 8) break;
      if (board.pieceAt(newX, current[1]) == nullptr) {
        // if the destination is empty, add it to legalMoves
        legalMoves.push_back({newX, current[1]});
      } else {
        // if the destination has a piece, add it to legalMoves if it is of different color, and break
        if (board.pieceAt(newX, current[1])->getIsWhite() != this->getIsWhite()) {
          legalMoves.push_back({newX, current[1]});
        }
        break;
      }
    }
    // Check in the direction in the same rows
    for (int k = 1; k < 8; ++k) {
      int newY = current[1] + k * sign;
      if (newY < 0 || newY >= 8) break;
      if (board.pieceAt(current[0], newY) == nullptr) {
        // if the destination is empty, add it to legalMoves
        legalMoves.push_back({current[0], newY});
      } else {
        if (board.pieceAt(current[0], newY)->getIsWhite() != this->getIsWhite()) {
          // if the destination has a piece, add it to legalMoves if it is of different color, and break
          legalMoves.push_back({current[0], newY});
        }
        break;
      }
    }
  }
  // Check in the direction in the diagonals (like a bishop)
  for (int xSign = -1; xSign <= 1; xSign += 2) {
    for (int ySign = -1; ySign <= 1; ySign += 2) {
      for (int k = 1; k < 8; ++k) {
        int newX = current[0] + k * xSign;
        int newY = current[1] + k * ySign;
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) break;
        if (board.pieceAt(newX, newY) == nullptr) {
          // if the destination is empty, add it to legalMoves
          legalMoves.push_back({newX, newY});
        } else {
          // if the destination has a piece, add it to legalMoves if it is of different color, and break
          if (board.pieceAt(newX, newY)->getIsWhite() != this->getIsWhite()) {
            legalMoves.push_back({newX, newY});
          }
          break;
        }
      }
    }
  }
  vector<vector<int>> legalMovesWithoutCheck;
  for (auto move : legalMoves) {
    if (!(board.willCheck(current, move))) {
      legalMovesWithoutCheck.push_back(move);
    }
  }
  return legalMovesWithoutCheck;
}
