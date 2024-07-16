#include "king.h"

int kingPoints = 900;

King::King(const bool isWhite): Piece(isWhite, kingPoints), didFirstMove{false} {};

// get if the King has moved. If true, the King cannot castle
bool King::getDidFirstMove() {
  return didFirstMove;
}

// set the King to have moved
void King::setDidFirstMove() {
  didFirstMove = true;
}

// Check if the move is legal for the King
// all current and to should be guaranteed to be in the board
bool King::isMoveLegal(vector<int> current, vector<int> destination, Board &board) {
  if (!didFirstMove) {
    // TODO: check for castling and return true if it is a castling move
  }
  // false if the destination is same as current location
  if (abs(current[0] - destination[0]) > 1 || abs(current[1] - destination[1]) > 1) {
    return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(destination[0], destination[1]) != nullptr && board.pieceAt(destination[0], destination[1])->getIsWhite() == this->getIsWhite()) {
    return false;
  }
  // TODO: check if the King is in check after the move
  return true;
}

// Get all the legal next moves for the King
// current should be guaranteed to be in the board
vector<vector<int>> King::getLegalMoves(vector<int> current, Board &board) {
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
      // TODO: check if the King is in check after the move
      legalMoves.push_back({newX, newY});
    }
  }
  if (!didFirstMove) {
    // TODO: check for castling and add the legal moves for castling
  }
  return legalMoves;
}
