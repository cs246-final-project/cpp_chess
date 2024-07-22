#include "pawn.h"
#include "board.h"

int pawnPoint = 10;

Pawn::Pawn(const bool isWhite, bool didFirstMove): Piece(isWhite, pawnPoint), didFirstMove{didFirstMove} {};

// get if the Pawn has moved. If true, the Pawn cannot move 2 squares
bool Pawn::getDidFirstMove() {
  return didFirstMove;
}

// set the Pawn to have moved
void Pawn::setDidFirstMove() {
  didFirstMove = true;
}

// Check if the move is legal for the Pawn
// all current and to should be guaranteed to be in the board
bool Pawn::isMoveLegal(int x, int y, int toX, int toY, Board &board) {
  // false if the destination is same as current location
  if (x == toX && y == toY) return false;
  // TODO: check for en passant
  // false if the destination has a piece of the same color
  if (board.pieceAt(toX, toY) != nullptr && board.pieceAt(toX, toY)->getIsWhite() == this->getIsWhite()) return false;
  // false if the destination is backward
  if (getIsWhite() && x < toX) return false;
  if (!getIsWhite() && x > toX) return false;
  if (x == toX) {
    // moving forward logic
    if (abs(y - toY) == 2) {
      // when moving 2 squares
      if (didFirstMove) return false;
      // if there is a piece at destination, return false
      if (board.pieceAt(toX, toY) != nullptr) {
        return false;
      }
      // if there is a piece in between, return false
      if (board.pieceAt(x, y + (toY - y) / 2) != nullptr) {
        return false;
      }
    } else if (abs(y - toY) == 1) {
      // if there is a piece at destination, return false
      if (board.pieceAt(toX, toY) != nullptr) {
        return false;
      }
    } else {
      // if the destination is not 1 or 2 squares away, return false
      return false;
    }
  } else if (abs(x - toX) == 1 && abs(y - toY) == 1){
    // capturing logic
    // if no piece at destination, return false
    if (board.pieceAt(toX, toY) == nullptr) {
      return false;
    }
  } else {
    return false;
  }
  return true;
}

// Get all the legal next moves for the Pawn
// current should be guaranteed to be in the board
vector<vector<int>> Pawn::getLegalMoves(vector<int> current, Board &board) {
  vector<vector<int>> legalMoves;
  int direction = getIsWhite() ? -1 : 1;
  if (current[1] + direction >= 0 && current[1] + direction < 8) {
    // moving forward logic
    if (board.pieceAt(current[0], current[1] + direction) == nullptr) {
      legalMoves.push_back({current[0], current[1] + direction});
      // when moving 2 squares
      if (!didFirstMove && board.pieceAt(current[0], current[1] + 2 * direction) == nullptr) {
        legalMoves.push_back({current[0], current[1] + 2 * direction});
      }
    }
    // capturing logic
    if (current[0] + 1 >= 0 && current[0] + 1 < 8 && board.pieceAt(current[0] + 1, current[1] + direction) != nullptr && board.pieceAt(current[0] + 1, current[1] + direction)->getIsWhite() != getIsWhite()) {
      legalMoves.push_back({current[0] + direction, current[1] + 1});
    }
    if (current[1] - 1 >= 0 && current[1] - 1 < 8 && board.pieceAt(current[0] - 1, current[1] + direction) != nullptr && board.pieceAt(current[0] - 1, current[1] + direction)->getIsWhite() != getIsWhite()) {
      legalMoves.push_back({current[0] + direction, current[1] - 1});
    }
    // TODO: check for en passant
  }
  return legalMoves;
}
