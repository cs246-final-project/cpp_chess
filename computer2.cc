#include "computer2.h"

Computer2::Computer2(const bool isWhite): Computer{isWhite, 2} {}

vector<vector<int>> Computer2::getMove(const Board &board) const {
  Board tempBoard = board;
  vector<vector<int>> positions = (isWhite ? tempBoard.getAliveWhite() : tempBoard.getAliveBlack());
  vector<vector<vector<int>>> moves;

  for(auto pos : positions){
    Piece* p = tempBoard.pieceAt(pos[0], pos[1]);
    vector<vector<int>> possibleMoves = p->getLegalMoves(pos, tempBoard, false);
    for(auto move : possibleMoves){
      if (tempBoard.checkPromotion(pos[0], pos[1], move[0], move[1])) {
        tempBoard.movePiece(pos[0], pos[1], move[0], move[1], 'Q');
      } else {
        tempBoard.movePiece(pos[0], pos[1], move[0], move[1]);
      }
      if(!(tempBoard.colorInCheck(isWhite))){
        moves.push_back({pos, move});
      }
      tempBoard = board;
    }
  }
  if (moves.size() == 0) {
    return {};
  }
  int maxScore;
  vector<int> maxIndex;
  int index = 0;
  for (auto move : moves) {
    Board tempBoard = board;
    if (tempBoard.checkPromotion(move[0][0], move[0][1], move[1][0], move[1][1])) {
      tempBoard.movePiece(move[0][0], move[0][1], move[1][0], move[1][1], 'Q');
    } else {
      tempBoard.movePiece(move[0][0], move[0][1], move[1][0], move[1][1]);
    }
    int point = tempBoard.getPoint(isWhite);
    if (index == 0) {
      maxScore = point;
      maxIndex.push_back(index);
    }
    if (maxScore < point) {
      maxScore = point;
      maxIndex = {index};
    } else if (maxScore == point) {
      maxIndex.push_back(index);
    }
    ++index;
  }
  vector<vector<int>> move = moves[maxIndex[rand() % maxIndex.size()]];
  return move;
}