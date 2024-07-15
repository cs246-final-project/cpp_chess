#ifndef HISTORYCOMPONENT_H
#define HISTORYCOMPONENT_H
#include "piece.h"
#include <memory>
#include <vector>
using namespace std;

class HistoryComponent {
  vector<int> from;
  vector<int> to;
  public:
    HistoryComponent(vector<int> from, vector<int> to);
    vector<int> getFrom();
    vector<int> getTo();
};

#endif