#include "piece.h"
#include "board.h"

#include <iostream>
#include <memory>
#include <map>

int main() {
  bool gameStart = false;
  bool setupMode = false;
  bool isWhiteTurn = true;

  map<char, int> xMap;
  map<char, int> yMap;
  xMap.insert({'1', 0});
  xMap.insert({'2', 1});
  xMap.insert({'3', 2});
  xMap.insert({'4', 3});
  xMap.insert({'5', 4});
  xMap.insert({'6', 5});
  xMap.insert({'7', 6});
  xMap.insert({'8', 7});
  yMap.insert({'a', 0});
  yMap.insert({'b', 1});
  yMap.insert({'c', 2});
  yMap.insert({'d', 3});
  yMap.insert({'e', 4});
  yMap.insert({'f', 5});
  yMap.insert({'g', 6});
  yMap.insert({'h', 7});

  int whitePoints, blackPoints;

  unique_ptr<Board> board = make_unique<Board>();
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
          vector<int> fromPos{from.at(0), from.at(1)};
          vector<int> toPos{to.at(0), to.at(1)};
        }
      }
    } else if(command == "setup"){
      setupMode = true;
      string arg1, arg2;
      while(setupMode && cin >> command){
        if(command == "+"){
          char piece;
          cin >> piece >> arg2;
          Piece* p;
          switch(piece){ // make new piece based on input
            case 'p':
              p = new Pawn{false};
              break;
            case 'r':
              p = new Rook{false};
              break;
            case 'n':
              p = new Knight{false};
              break;
            case 'b':
              p = new Bishop{false};
              break;
            case 'q':
              p = new Queen{false};
              break;
            case 'k':
              p = new King{false};
              break;
            case 'P':
              p = new Pawn{true};
              break;
            case 'R':
              p = new Rook{true};
              break;
            case 'N':
              p = new Knight{true};
              break;
            case 'B':
              p = new Bishop{true};
              break;
            case 'Q':
              p = new Queen{true};
              break;
            case 'K':
              p = new King{true};
              break;
            default:
              throw "Invalid input!";
              break;
          }
          unique_ptr<Piece> temp{p};
          board->place(move(temp), xMap.at(arg2[0]), yMap.at(arg2[1]));
        } else if(command == "-"){
          cin >> arg1;
          board->remove(xMap.at(arg1[0]), yMap.at(arg1[1]));
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
