#include "bishop.h"
#include "board.h"

int bishopPoint = 30;

Bishop::Bishop(const bool isWhite) : Piece(isWhite, bishopPoint) {};

unique_ptr<Piece> Bishop::clone() const {
  return make_unique<Bishop>(*this);
}

// Check if the move is legal for the Bishop
// all current and to should be guaranteed to be in the board
bool Bishop::isMoveLegal(int x, int y, int toX, int toY, const Board &board, bool recursive) const {
  // false if the destination is same as current location
  if (x == toX && y == toY) return false;
  // false if the destination is not in the same diagonal
  if (abs(x - toX) != abs(y - toY)) return false;
  // false if there is a piece in between
  int xSign = x < toX ? 1 : -1;
  int ySign = y < toY ? 1 : -1;
  for (int i = 1; i < abs(x - toX); ++i) {
    if (board.pieceAt(x + i * xSign, y + i * ySign) != nullptr) return false;
  }
  // false if the destination has a piece of the same color
  if (board.pieceAt(toX, toY) != nullptr && board.pieceAt(toX, toY)->getIsWhite() == this->getIsWhite()) return false;
  // check if the move would put the king in check
  if (!recursive) {
    Board temp = board;
    temp.movePieceWithoutValidation(x, y, toX, toY);
    if (temp.colorInCheck(this->getIsWhite())) return false;
  }
  return true;
}

// Get all the legal next moves for the Bishop
// current should be guaranteed to be in the board
vector<vector<int>> Bishop::getLegalMoves(vector<int> current, const Board &board, bool checkForCheckmate) const {
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

vector<vector<int>> Bishop::getCaptureMoves(vector<int> current, const Board &board) const {
  vector<vector<int>> legalMoves;
  for (int xSign = -1; xSign <= 1; xSign += 2) {
    for (int ySign = -1; ySign <= 1; ySign += 2) {
      for (int k = 1; k < 8; ++k) {
        int newX = current[0] + k * xSign;
        int newY = current[1] + k * ySign;
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) break;
        if (board.pieceAt(newX, newY) != nullptr && board.pieceAt(newX, newY)->getIsWhite() != this->getIsWhite()) {
          legalMoves.push_back({newX, newY});
          break;
        }
      }
    }
  }
  return legalMoves;
}
