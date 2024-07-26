#include "computer1.h"

Computer1::Computer1(bool isWhite): Computer{isWhite} {};

// get the move of the computer level 1
vector<vector<int>> Computer1::getMove(const Board &board) const {
  Board tempBoard = board;
  vector<vector<int>> positions = (getIsWhite() ? tempBoard.getAliveWhite() : tempBoard.getAliveBlack());
  vector<vector<vector<int>>> moves;

  for(auto pos : positions){
    Piece* p = tempBoard.pieceAt(pos[0], pos[1]);
    vector<vector<int>> possibleMoves = p->getLegalMoves(pos, tempBoard, false);
    for(auto move : possibleMoves){
      tempBoard.movePiece(pos[0], pos[1], move[0], move[1]);
      if(!(tempBoard.colorInCheck(getIsWhite()))){
        moves.push_back({pos, move});
      }
      tempBoard = board;
    }
  }
  if (moves.size() == 0) {
    return {};
  }
  srand((unsigned int)time(NULL));
  vector<vector<int>> move = moves[rand() % moves.size()];
  return move;
}
