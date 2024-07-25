#include "computer1.h"

Computer1::Computer1(const bool isWhite): Computer{isWhite, 1} {};

vector<vector<int>> Computer1::getMove(const Board &board) const {
  vector<vector<vector<int>>> possibleMoves = board.getAllPossibleMoves(isWhite);
  if (possibleMoves.size() == 0) {
    return {};
  }
  int random = rand() % possibleMoves.size();
  vector<vector<int>> move = possibleMoves[random];
  return move;
}
