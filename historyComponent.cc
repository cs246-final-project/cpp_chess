#include "historyComponent.h"

HistoryComponent::HistoryComponent(vector<int> from, vector<int> to): from{from}, to{to}{}

vector<int> HistoryComponent::getFrom() const {
  return from;
}
vector<int> HistoryComponent::getTo() const {
  return to;
}