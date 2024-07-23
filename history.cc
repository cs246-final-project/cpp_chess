#include "history.h"

History::History(){};

History::History(const History& other) {
  for (const auto& component : other.history) {
    history.emplace_back(make_unique<HistoryComponent>(*component));
  }
}

History& History::operator=(const History& other) {
  if (this != &other) { // protect against self-assignment
    history.clear(); // clear current contents
    for (const auto& component : other.history) {
      history.emplace_back(make_unique<HistoryComponent>(*component));
    }
  }
  return *this;
}

void History::addMove(vector<int> from, vector<int> to){
  unique_ptr<HistoryComponent> hc{new HistoryComponent{from, to}};
  history.emplace_back(move(hc));
}
vector<vector<int>> History::getLast(){
  return vector<vector<int>>{history.back()->getFrom(), history.back()->getTo()};
}
