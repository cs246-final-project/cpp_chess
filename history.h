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
    History();
    ~History() = default;
    History(const History& other);
    History& operator=(const History& other);
    void addMove(vector<int> from, vector<int> to);
    vector<vector<int>> getLast() const;
};

#endif
