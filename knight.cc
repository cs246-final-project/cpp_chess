#include "knight.h"

int knightPoint = 30;

Knight::Knight(const bool isWhite): Piece(isWhite, knightPoint) {}

// Check if the move is legal for the Knight
// all current and to should be guaranteed to be in the board
bool Knight::isMoveLegal(vector<int> current, vector<int> destination, Board &board) {
  // false if the destination is same as current location or the destination is in the same row or column
  if (current[0] == destination[0] || current[1] == destination[1]) return false;
  // false if the destination is not in the L shape
  if (abs(current[0] - destination[0]) + abs(current[1] - destination[1]) != 3) return false;
  // false if the destination has a piece of the same color
  if (board.pieceAt(destination[0], destination[1]) != nullptr && board.pieceAt(destination[0], destination[1])->getIsWhite() == this->getIsWhite()) return false;
  return true;
}

// Get all the legal next moves for the Knight
// current should be guaranteed to be in the board
vector<vector<int>> Knight::getLegalMoves(vector<int> current, Board &board) {
  vector<vector<int>> legalMoves;
  for (int i = -2; i <= 2; i += 4) {
    for (int j = -1; j <= 1; j += 2) {
      if (current[0] + i >= 0 && current[0] + i < 8 && current[1] + j >= 0 && current[1] + j < 8) {
        if (board.pieceAt(current[0] + i, current[1] + j) == nullptr || board.pieceAt(current[0] + i, current[1] + j)->getIsWhite() != this->getIsWhite()) {
          legalMoves.push_back({current[0] + i, current[1] + j});
        }
      }
      if (current[0] + j >= 0 && current[0] + j < 8 && current[1] + i >= 0 && current[1] + i < 8) {
        if (board.pieceAt(current[0] + j, current[1] + i) == nullptr || board.pieceAt(current[0] + j, current[1] + i)->getIsWhite() != this->getIsWhite()) {
          legalMoves.push_back({current[0] + j, current[1] + i});
        }
      }
    }
  }
  return legalMoves;
}
