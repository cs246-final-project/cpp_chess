#include "computer3.h"

Computer3::Computer3(bool isWhite): Computer{isWhite} {};

// get the move of the computer level 3
vector<vector<int>> Computer3::getMove(const Board &board) const {
  Board tempBoard = board;
  int maxScore = -1000000;
  int index = 0;
  vector<int> maxIndex;
  vector<int> checkIndex;
  vector<vector<int>> positions = (getIsWhite() ? tempBoard.getAliveWhite() : tempBoard.getAliveBlack());
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
      if(!(tempBoard.colorInCheck(getIsWhite()))){
        if(tempBoard.colorInCheck(!getIsWhite())){
          checkIndex.push_back(index);
        }
        moves.push_back({pos, move});
        int secondMinPoint;
        int secondIndex = 0;
        bool secondMoveEmpty = true;
        vector<vector<int>> secondPositions = (getIsWhite() ? tempBoard.getAliveBlack() : tempBoard.getAliveWhite());
        for (auto secondPos : secondPositions) {
          Piece* secondP = tempBoard.pieceAt(secondPos[0], secondPos[1]);
          vector<vector<int>> secondPossibleMoves = secondP->getCaptureMoves(secondPos, tempBoard);
          for (auto secondMove : secondPossibleMoves) {
            Board secondTempBoard = tempBoard;
            if (secondTempBoard.checkPromotion(secondPos[0], secondPos[1], secondMove[0], secondMove[1])) {
              secondTempBoard.movePiece(secondPos[0], secondPos[1], secondMove[0], secondMove[1], 'Q');
            } else {
              secondTempBoard.movePiece(secondPos[0], secondPos[1], secondMove[0], secondMove[1]);
            }
            int secondPoint = secondTempBoard.getPoint(getIsWhite());
            if (secondIndex == 0 || secondMoveEmpty) {
              secondMinPoint = secondPoint;
            } else if (secondMinPoint > secondPoint) {
              secondMinPoint = secondPoint;
            } else {
            }
          }
          if (secondPossibleMoves.size() > 0) {
            secondMoveEmpty = false;
          }
          ++secondIndex;
        }
        if (secondMoveEmpty) {
          secondMinPoint = tempBoard.getPoint(getIsWhite());
        }
        if (maxScore < secondMinPoint) {
          maxScore = secondMinPoint;
          maxIndex = {index};
        } else if (maxScore == secondMinPoint) {
          maxIndex.push_back(index);
        }
        ++index;
      }
      tempBoard = board;
    }
  }
  if (moves.size() == 0) {
    return {};
  }
  if (checkIndex.size() > 0) {
    for (auto ele : checkIndex) {
      for (auto ele2 : maxIndex) {
        if (ele == ele2) {
          vector<vector<int>> move = moves[ele];
          return move;
        }
      }
    }
  }
  srand((unsigned int)time(NULL));
  vector<vector<int>> move = moves[maxIndex[rand() % maxIndex.size()]];
  return move;
}
