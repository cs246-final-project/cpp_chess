#include "piece.h"
#include "board.h"
#include "view.h"

#include <iostream>
#include <memory>
#include <map>

// cast string input to vector of int (position)
vector<int> getInputPosition(string arg) {
  if (arg.length() != 2) return vector<int> {};
  if (arg[1] < 49 || arg[1] > 56) return vector<int> {};
  if (arg[0] >= 65 && arg[0] <= 72) return {arg[0] - 65, 7 - (arg[1] - 49)};
  else if (arg[0] >= 97 && arg[0 <= 104]) return {arg[0] - 97, 7 - (arg[1] - 49)};
  else {
    return vector<int> {};
  }
};

// cast string input "from" and "to" to vector of position
vector<vector<int>> getInputMovePosition(string from, string to) {
  vector<vector<int>> pos;
  // cast string input "from" to vector of position
  vector<int> fromPos = getInputPosition(from);
  if (fromPos.empty()) return vector<vector<int>> {};
  pos.push_back(fromPos);
  // cast string input "to" to vector of position
  vector<int> toPos = getInputPosition(to);
  if (toPos.empty()) return vector<vector<int>> {};
  pos.push_back(toPos);
  return pos;
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
      bool p1Valid, p2Valid = false;
      cin >> p1 >> p2;
      if(p1 == "human"){
        p1Valid = true;
        // white = move(make_unique(human));
      } else if(p1 == "computer1") {
        p1Valid = true;
        // white = move(make_unique(cpu1));
      } else if(p1 == "computer2") {
        p1Valid = true;
        // white = move(make_unique(cpu2));
      } else if(p1 == "computer3") {
        p1Valid = true;
        // white = move(make_unique(cpu3));
      } else if(p1 == "computer4") {
        p1Valid = true;
        // white = move(make_unique(cpu4));
      }
      if(p2 == "human"){
        p2Valid = true;
        // black = move(make_unique(human));
      } else if(p2 == "computer1") {
        p2Valid = true;
        // black = move(make_unique(cpu1));
      } else if(p2 == "computer2") {
        p2Valid = true;
        // black = move(make_unique(cpu2));
      } else if(p2 == "computer3") {
        p2Valid = true;
        // black = move(make_unique(cpu3));
      } else if(p2 == "computer4") {
        p2Valid = true;
        // black = move(make_unique(cpu4));
      }
      if (p1Valid && p2Valid) {
        gameStart = true;
        view->displayBoard(*board.get());
      } else {
        cout << "Not valid player" << endl;
      }
    } else if(command == "resign") {
      isWhiteTurn ? ++blackPoints : ++whitePoints;
      unique_ptr<Board> temp = make_unique<Board>();
      swap(board, temp);
      gameStart = false;
    } else if(command == "move") {
      string from, to;
      cin >> from >> to;
      if (!gameStart) {
        cout << "Game not started!" << endl;
        continue;
      }
      vector<vector<int>> pos = getInputMovePosition(from, to);
      if (pos.empty()) {
        cout << "Invalid input!" << endl;
        continue;
      }
      if (board->pieceAt(pos[0][0], pos[0][1]) == nullptr){
        cout << "Invalid Move! (No Piece at the Position!)" << endl;
        continue;
      } else if (board->pieceAt(pos[0][0], pos[0][1])->getIsWhite() != isWhiteTurn){
        cout << "Invalid Move! (Not Your Piece)" << endl;
        continue;
      }
      if (board->checkPromotion(pos[0][0], pos[0][1], pos[1][0], pos[1][1])){
        // when promotion move
        string promotion;
        char promoChar;
        cin >> promotion;
        if (promotion.length() < 1) {
          cout << "Need to specify promotion!" << endl;
          continue;
        }
        if (promotion[0] >= 'a') {
          promoChar = promotion[0] - ('a' - 'A');
        } else {
          promoChar = promotion[0];
        }
        if (promoChar != 'Q' && promoChar != 'R' && promoChar != 'B' && promoChar != 'N'){
          cout << "Invalid promotion input!" << endl;
          continue;
        }
        if (board->movePiece(pos[0][0], pos[0][1], pos[1][0], pos[1][1], promoChar)){
          isWhiteTurn = !isWhiteTurn;
        } else {
          cout << "Invalid Move!" << endl;
          continue;
        }
      } else {
        // when normal move
        if (board->movePiece(pos[0][0], pos[0][1], pos[1][0], pos[1][1])){
          isWhiteTurn = !isWhiteTurn;
        } else {
          cout << "Invalid Move!" << endl;
          continue;
        }
      }
      view->displayBoard(*board.get());
    } else if(command == "setup"){
      if (gameStart) {
        cout << "Cannot enter setup mode while game is played" << endl;
        continue;
      }
      setupMode = true;
      board = make_unique<Board>(true);
      string arg;
      while(setupMode && cin >> command){
        if(command == "+"){
          char piece;
          cin >> piece >> arg;
          unique_ptr<Piece> up;
          vector<int> pos = getInputPosition(arg);
          if (pos.empty()) {
            cout << "Invalid input!" << endl;
            break;
          }
          switch(piece){ // make new piece based on input
            case 'p':
              if (pos[1] == 0) {
                up = make_unique<Pawn>(false);
              } else {
                up = make_unique<Pawn>(false, true);
              }
              break;
            case 'r':
              if (pos[1] == 0 && (pos[0] == 0 || pos[0] == boardWidth - 1)) {
                up = make_unique<Rook>(false);
              } else {
                up = make_unique<Rook>(false, true);
              }
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
              if (pos[1] == 0 && pos[0] == kingRowPos) {
                up = make_unique<King>(false);
              } else {
                up = make_unique<King>(false, true);
              }
              break;
            case 'P':
              if (pos[1] == boardHeight - 1) {
                up = make_unique<Pawn>(true);
              } else {
                up = make_unique<Pawn>(true, true);
              }
              break;
            case 'R':
              if (pos[1] == boardHeight - 1 && (pos[0] == 0 || pos[0] == boardWidth - 1)) {
                up = make_unique<Rook>(true);
              } else {
                up = make_unique<Rook>(true, true);
              }
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
              if (pos[1] == boardHeight - 1 && pos[0] == kingRowPos) {
                up = make_unique<King>(true);
              } else {
                up = make_unique<King>(true, true);
              }
              break;
            default:
              cout << "Invalid input!" << endl;
              break;
          }
          if (up != nullptr) {
            board->place(move(up), pos[0], pos[1]);
            view->displayBoard(*board.get());
          }
        } else if(command == "-"){
          cin >> arg;
          vector<int> pos = getInputPosition(arg);
          if (pos.empty()) {
            cout << "Invalid input!" << endl;
            continue;
          }
          board->remove(pos[0], pos[1]);
          view->displayBoard(*board.get());
        } else if(command == "="){
          cin >> arg;
          arg == "white" ? isWhiteTurn = true : isWhiteTurn = false;
        } else if(command == "done"){
          if(board->validBoard()){
            setupMode = false;
          } else {
            cout << "Invalid Board!" << endl;
          }
        } else {
          cout << "Invalid Command!" << endl;
        }
      }
    } else if (command == "quit") {
      break;
    } else {
      cout << "Invalid Command!" << endl;
    }
  }
  return 0;
}
