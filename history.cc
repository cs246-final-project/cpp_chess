#include "history.h"

void History::AddMove(vector<int> from, vector<int> to){
  unique_ptr<HistoryComponent> hc{new HistoryComponent{from, to}};
  history.emplace_back(move(hc));
}
