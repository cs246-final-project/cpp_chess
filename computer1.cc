#include "computer1.h"

Computer1::Computer1(const bool isWhite): Computer{isWhite, 1} {};

vector<vector<int>> Computer1::getMove(Board &board) {
  vector<vector<vector<int>>> possibleMoves;
  for (auto ele : isWhite ? board.getAliveWhite() : board.getAliveBlack()) {
    Piece *piece = board.pieceAt(ele[0], ele[1]);
    vector<vector<int>> moves = piece->getLegalMoves({ele[0], ele[1]}, board);
    for (auto move : moves) {
      possibleMoves.push_back({ele, move});
    }
  }
  int random = rand() % possibleMoves.size();
  vector<vector<int>> move = possibleMoves[random];
  return move;
}
