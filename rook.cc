#include "rook.h"
#include "board.h"

int rookPoint = 50;

Rook::Rook(const bool isWhite, bool didFirstMove) : Piece{isWhite, rookPoint}, didFirstMove{didFirstMove} {}

unique_ptr<Piece> Rook::clone() const {
  return make_unique<Rook>(new Rook{*this});
}

// get if the Rook has moved. If true, the Rook cannot castle
bool Rook::getDidFirstMove() const {
  return didFirstMove;
}

// set the Rook to have moved
void Rook::setDidFirstMove() {
  didFirstMove = true;
}

// Check if the move is legal for the Rook
// all current and to should be guaranteed to be in the board
bool Rook::isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const {
  // false if the destination is same as current location
  if (x == toX && y == toY) return false;
  // false if the destination is not in the same row or column
  if (x != toX && y != toY) return false;
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
  // false if the destination has a piece of the same color
  if (board.pieceAt(toX, toY) != nullptr && board.pieceAt(toX, toY)->getIsWhite() == this->getIsWhite()) return false;
  // check if the move would put the king in check
  if (!recursive && board.willCheck(x, y, toX, toY)) {
    return false;
  }
  return true;
}

// Get all the legal next moves for the Rook
// current should be guaranteed to be in the board
vector<vector<int>> Rook::getLegalMoves(vector<int> current, const Board &board) const {
  vector<vector<int>> legalMoves;
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
  vector<vector<int>> legalMovesWithoutCheck;
  for (auto move : legalMoves) {
    if (!(board.willCheck(current, move))) {
      legalMovesWithoutCheck.push_back(move);
    }
  }
  return legalMovesWithoutCheck;
}
