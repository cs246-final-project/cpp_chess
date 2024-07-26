#include "piece.h"
#include "board.h"
#include "view.h"
#include "computer1.h"
#include "computer2.h"
#include "computer3.h"

#include <iostream>
#include <memory>
#include <map>

using namespace std;

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
  bool isBoardCustom = false;
  float whitePoints = 0, blackPoints = 0;

  unique_ptr<Board> board;
  unique_ptr<View> view = make_unique<View>(board.get());
  unique_ptr<Computer> whiteCpu = nullptr;
  unique_ptr<Computer> blackCpu = nullptr;
  
  string command;
  while(cin >> command){
    if(command == "game"){
      string p1, p2;
      bool p1Valid, p2Valid = false;
      cin >> p1 >> p2;
      if(p1 == "human"){
        p1Valid = true;
      } else if(p1 == "computer1") {
        p1Valid = true;
        whiteCpu = move(make_unique<Computer1>(true));
      } else if(p1 == "computer2") {
        p1Valid = true;
        whiteCpu = move(make_unique<Computer2>(true));
      } else if(p1 == "computer3") {
        p1Valid = true;
        whiteCpu = move(make_unique<Computer3>(true));
      } else if(p1 == "computer4") {
        p1Valid = true;
        // whiteCpu = move(make_unique<Computer4>(true));
      }
      if(p2 == "human"){
        p2Valid = true;
        // black = move(make_unique(human));
      } else if(p2 == "computer1") {
        p2Valid = true;
        blackCpu = move(make_unique<Computer1>(false));
      } else if(p2 == "computer2") {
        p2Valid = true;
        blackCpu = move(make_unique<Computer2>(false));
      } else if(p2 == "computer3") {
        p2Valid = true;
        blackCpu = move(make_unique<Computer3>(false));
      } else if(p2 == "computer4") {
        p2Valid = true;
        // blackCpu = move(make_unique<Computer4>(false));
      }
      if (p1Valid && p2Valid) {
        if(!isBoardCustom){
          unique_ptr<Board> temp = make_unique<Board>();
          swap(board, temp);
          view = make_unique<View>(board.get());
          view->displayBoard();
        } else {
          isBoardCustom = false;
        }
        gameStart = true;
      } else {
        cout << "Not valid player" << endl;
      }
    } else if(command == "resign") {
      if (!gameStart) {
        cout << "Game not started!" << endl;
        cin.ignore(1000, '\n');
        continue;
      }
      isWhiteTurn ? ++blackPoints : ++whitePoints;
      unique_ptr<Board> temp = make_unique<Board>();
      swap(board, temp);
      cout << (isWhiteTurn ? "Black wins." : "White wins.") << endl;
      view->colourWins(!isWhiteTurn);
      isWhiteTurn = true;
      gameStart = false;
    } else if(command == "move") {
      if (!gameStart) {
        cout << "Game not started!" << endl;
        cin.ignore(1000, '\n');
        continue;
      }
      if ((isWhiteTurn && whiteCpu) || (!isWhiteTurn && blackCpu)) {
        vector<vector<int>> cpuMove;
        if (isWhiteTurn && whiteCpu) {
          cpuMove = whiteCpu->getMove(board->clone());
        } else if (!isWhiteTurn && blackCpu) {
          cpuMove = blackCpu->getMove(board->clone());
        }
        if (cpuMove.size() == 0) {
          cout << "computer has no valid move!" << endl;
        } else {
          vector<vector<int>> positions;
          positions = board->movePiece(cpuMove[0][0], cpuMove[0][1], cpuMove[1][0], cpuMove[1][1]);
          if (positions.size() != 0){
            view->update(positions);
            isWhiteTurn = !isWhiteTurn;
          } else {
            cout << "Computer made invalid Move!" << endl;
            cout << cpuMove[0][0] << "," << cpuMove[0][1] << "," << cpuMove[1][0] << "," << cpuMove[1][1] << endl;
            continue;
          }
        }
      } else {
        string from, to;
        cin >> from >> to;
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
          vector<vector<int>> positions;
          positions = board->movePiece(pos[0][0], pos[0][1], pos[1][0], pos[1][1], promoChar);
          if (positions.size() != 0){
            view->update(positions);
            isWhiteTurn = !isWhiteTurn;
          } else {
            cout << "Invalid Move!" << endl;
            continue;
          }
        } else {
          // when normal move
          vector<vector<int>> positions;
          positions = board->movePiece(pos[0][0], pos[0][1], pos[1][0], pos[1][1]);
          if (positions.size() != 0){
            view->update(positions);
            isWhiteTurn = !isWhiteTurn;
          } else {
            cout << "Invalid Move!" << endl;
            continue;
          }
        }
      }
      if(board->cantMove(isWhiteTurn)){
        if(board->colorInCheck(isWhiteTurn)){
          isWhiteTurn ? ++blackPoints : ++whitePoints;
          view->colourWins(!isWhiteTurn);
          cout << (isWhiteTurn ? "Checkmate. Black wins." : "Checkmate. White wins.") << endl;
        } else {
          blackPoints += 0.5;
          whitePoints += 0.5;
          view->draw();
          cout << "Stalemate." << endl;
        }
        isWhiteTurn = true;
        gameStart = false;
        isBoardCustom = false;
      }
    } else if(command == "setup"){
      if (gameStart) {
        cout << "Cannot enter setup mode while game is played" << endl;
        continue;
      }
      isBoardCustom = true;
      setupMode = true;
      unique_ptr<Board> temp = make_unique<Board>(true);
      swap(board, temp);
      view = make_unique<View>(board.get());
      view->displayBoard();
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
              if (pos[1] == 1) {
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
              if (pos[1] == boardHeight - 2) {
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
            view->update(vector<vector<int>>{pos});
          }
        } else if(command == "-"){
          cin >> arg;
          vector<int> pos = getInputPosition(arg);
          if (pos.empty()) {
            cout << "Invalid input!" << endl;
            continue;
          }
          board->remove(pos[0], pos[1]);
          view->update(vector<vector<int>>{pos});
        } else if(command == "="){
          cin >> arg;
          if (arg == "white" || arg == "WHITE") {
            isWhiteTurn = true;
          } else if (arg == "black" || arg == "BLACK") {
            isWhiteTurn = false;
          } else {
            cout << "Invalid team" << endl;
          }
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
    } else if(command == "help"){
      cout << "game human computer2 - Arguments are human or computer[1-3]. Starts a game of chess." << endl;
      cout << "resign - Forfeits the game." << endl;
      cout << "move e1 e3 - Attempts to move the piece at the first argument to the position of the second argument." << endl;
      cout << "setup - Enters setup mode." << endl;
      cout << "+ Q a3 - Places the piece represented by the first argument at the position of the second argument." << endl;
      cout << "- h8 - Removes the piece at the argument." << endl;
      cout << "done - Checks for validity of the board. Exits setup mode if valid." << endl;
      cout << "quit - Ends the program." << endl;
    } else {
      cout << "Invalid Command!" << endl;
    }
  }
  cout << "Final Score:" << endl;
  cout << "White: " << whitePoints << endl;
  cout << "Black: " << blackPoints << endl;
  return 0;
}
