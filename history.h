#ifndef HISTORY_H
#define HISTORY_H
#include "piece.h"
#include "historyComponent.h"
#include <vector>

class History {
    std::vector<Piece*> history;
    public:
        HistoryComponent pop();
};

#endif