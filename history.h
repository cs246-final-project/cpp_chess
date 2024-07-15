#ifndef HISTORY_H
#define HISTORY_H
#include "piece.h"
#include "historyComponent.h"
#include <vector>
#include <memory>
using namespace std;

class History {
  vector<unique_ptr<HistoryComponent>> history;
  public:
    void undo();
    void AddMove(vector<int> from, vector<int> to);
};

#endif
