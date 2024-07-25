#include "computer1.h"

Computer1::Computer1(const bool isWhite): Computer{isWhite, 1} {}

vector<vector<int>> Computer1::getMove(const Board &board) const {
  Board tempBoard = board;
  vector<vector<int>> positions = (isWhite ? tempBoard.getAliveWhite() : tempBoard.getAliveBlack());
  vector<vector<vector<int>>> moves;

  for(auto pos : positions){
    Piece* p = tempBoard.pieceAt(pos[0], pos[1]);
    vector<vector<int>> possibleMoves = p->getLegalMoves(pos, tempBoard);
    for(auto move : possibleMoves){
      tempBoard.movePiece(pos[0], pos[1], move[0], move[1]);
      if(!(tempBoard.colorInCheck(isWhite))){
        moves.push_back({pos, move});
      }
      tempBoard = board;
    }
  }
  if (moves.size() == 0) {
    return {};
  }
  vector<vector<int>> move = moves[rand() % moves.size()];
  return move;
}