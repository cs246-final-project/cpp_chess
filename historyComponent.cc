#include "historyComponent.h"

HistoryComponent::HistoryComponent(vector<int> from, vector<int> to): from{from}, to{to}{}

vector<int> HistoryComponent::getFrom(){
  return from;
}
vector<int> HistoryComponent::getTo(){
  return to;
}