#include "bishop.h"

int bishopPoint = 30;

Bishop::Bishop(const bool isWhite) : Piece(isWhite, bishopPoint) {};

// Check if the move is legal for the Bishop
// all current and to should be guaranteed to be in the board
bool Bishop::isMoveLegal(vector<int> current, vector<int> destination, Board &board) {
  // false if the destination is same as current location
  if (current[0] == destination[0] && current[1] == destination[1]) return false;
  // false if the destination is not in the same diagonal
  if (abs(current[0] - destination[0]) != abs(current[1] - destination[1])) return false;
  // false if there is a piece in between
  int xSign = current[0] < destination[0] ? 1 : -1;
  int ySign = current[1] < destination[1] ? 1 : -1;
  for (int i = 1; i < abs(current[0] - destination[0]); ++i) {
    if (board.pieceAt(current[0] + i * xSign, current[1] + i * ySign) != nullptr) return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(destination[0], destination[1]) != nullptr && board.pieceAt(destination[0], destination[1])->getIsWhite() == this->getIsWhite()) return false;
  return true;
}

// Get all the legal next moves for the Bishop
// current should be guaranteed to be in the board
vector<vector<int>> Bishop::getLegalMoves(vector<int> current, Board &board) {
  vector<vector<int>> legalMoves;
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
