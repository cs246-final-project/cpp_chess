#include "history.h"

void History::addMove(vector<int> from, vector<int> to){
  unique_ptr<HistoryComponent> hc{new HistoryComponent{from, to}};
  history.emplace_back(move(hc));
}
vector<vector<int>> History::getLast(){
  return vector<vector<int>>{history.back()->getFrom(), history.back()->getTo()};
}