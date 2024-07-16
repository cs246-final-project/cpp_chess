#include "queen.h"

Queen::Queen(const bool isWhite): Piece(isWhite, 9) {}

// Check if the move is legal for the Queen
// all current and to should be guaranteed to be in the board
bool Queen::isMoveLegal(vector<int> current, vector<int> destination, Board &board) {
  // false if the destination is same as current location
  if (current[0] == destination[0] && current[1] == destination[1]) return false;
  if (current[0] == destination[0] || current[1] == destination[1]) {
    // when moving like a rook
    // false if there is a piece in between
    if (current[0] == destination[0]) {
      int sign = current[1] < destination[1] ? 1 : -1;
      for (int i = 1; i < abs(current[1] - destination[1]); ++i) {
        if (board.pieceAt(current[0], current[1] + i * sign) != nullptr) return false;
      }
    } else {
      int sign = current[0] < destination[0] ? 1 : -1;
      for (int i = 1; i < abs(current[0] - destination[0]); ++i) {
        if (board.pieceAt(current[0] + i * sign, current[1]) != nullptr) return false;
      }
    }
  } else if (abs(current[0] - destination[0]) == abs(current[1] - destination[1])) {
    // when moving like a bishop
    // false if there is a piece in between
    int xSign = current[0] < destination[0] ? 1 : -1;
    int ySign = current[1] < destination[1] ? 1 : -1;
    for (int i = 1; i < abs(current[0] - destination[0]); ++i) {
      if (board.pieceAt(current[0] + i * xSign, current[1] + i * ySign) != nullptr) return false;
    }
  } else {
    return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(destination[0], destination[1]) != nullptr && board.pieceAt(destination[0], destination[1])->getIsWhite() == this->getIsWhite()) return false;
  return true;
}

// Get all the legal next moves for the Queen
// current should be guaranteed to be in the board
vector<vector<int>> Queen::getLegalMoves(vector<int> current, Board &board) {
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
  return legalMoves;
}
