#include "piece.h"
#include "board.h"
#include "view.h"

#include <iostream>
#include <memory>
#include <map>

int getRow(char c){
  return 7-(c-49);
}
int getCol(char c){
  if(c < 90) c += 32;
  return c -= 97;
}

int main() {
  bool gameStart = false;
  bool setupMode = false;
  bool isWhiteTurn = true;
  int whitePoints, blackPoints;

  unique_ptr<Board> board = make_unique<Board>();
  unique_ptr<View> view = make_unique<View>();
  // unique_ptr<Player> white;
  // unique_ptr<Player> black;
  
  string command;
  while(cin >> command){
    if(command == "game"){
      string p1, p2;
      cin >> p1 >> p2;
      if(p1 == "human"){
        // white = move(make_unique(human));
      } else if(p1 == "computer1") {
        // white = move(make_unique(cpu1));
      } else if(p1 == "computer2") {
        // white = move(make_unique(cpu2));
      } else if(p1 == "computer3") {
        // white = move(make_unique(cpu3));
      } else if(p1 == "computer4") {
        // white = move(make_unique(cpu4));
      }
      if(p2 == "human"){
        // black = move(make_unique(human));
      } else if(p2 == "computer1") {
        // black = move(make_unique(cpu1));
      } else if(p2 == "computer2") {
        // black = move(make_unique(cpu2));
      } else if(p2 == "computer3") {
        // black = move(make_unique(cpu3));
      } else if(p2 == "computer4") {
        // black = move(make_unique(cpu4));
      }
    } else if(command == "resign") {
      isWhiteTurn ? ++blackPoints : ++whitePoints;
      unique_ptr<Board> temp = make_unique<Board>();
      swap(board, temp);
    } else if(command == "move") {
      
      if(isWhiteTurn){
        if(true/*white.isComputer()*/){
          // white.move()
        } else {
          string from, to;
          cin >> from >> to;
          vector<int> fromPos{from[0], from[1]};
          vector<int> toPos{to[0], to[1]};
          
        }
      } else {
        if(true/*black.isComputer()*/){
          // black.move()
        } else {
          string from, to;
          cin >> from >> to;
          vector<int> fromPos{from[0], from[1]};
          vector<int> toPos{to[0], to[1]};
        }
      }
      view->displayBoard(*board.get());
    } else if(command == "setup"){
      setupMode = true;
      string arg1, arg2;
      while(setupMode && cin >> command){
        if(command == "+"){
          char piece;
          cin >> piece >> arg2;
          unique_ptr<Piece> up;
          switch(piece){ // make new piece based on input
            case 'p':
              up = make_unique<Pawn>(false);
              break;
            case 'r':
              up = make_unique<Rook>(false);
              break;
            case 'n':
              up = make_unique<Knight>(false);
              break;
            case 'b':
              up = make_unique<Bishop>(false);
              break;
            case 'q':
              up = make_unique<Queen>(false);
              break;
            case 'k':
              up = make_unique<King>(false);
              break;
            case 'P':
              up = make_unique<Pawn>(true);
              break;
            case 'R':
              up = make_unique<Rook>(true);
              break;
            case 'N':
              up = make_unique<Knight>(true);
              break;
            case 'B':
              up = make_unique<Bishop>(true);
              break;
            case 'Q':
              up = make_unique<Queen>(true);
              break;
            case 'K':
              up = make_unique<King>(true);
              break;
            default:
              cout << "Invalid input!" << endl;
              break;
          }
          if (up != nullptr) {
            board->place(move(up), getRow(arg2[1]), getCol(arg2[0]));
            view->displayBoard(*board.get());
          }
        } else if(command == "-"){
          cin >> arg1;
          board->remove(getRow(arg2[1]), getCol(arg2[0]));
          view->displayBoard(*board.get());
        } else if(command == "="){
          cin >> arg1;
          arg1 == "white" ? isWhiteTurn = true : isWhiteTurn = false;
        } else if(command == "done"){
          if(board->validBoard()){
            setupMode = false;
          } else {
            cout << "Invalid Board!" << endl;
          }
        }
      }

    }
  }
  
  return 0;
}
