#include "../include/fileUtils.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(){

  string tempFileString = "";
  map<int, Card> masterCardList;

  cout << "TEST START" << endl;
  loadCardData(tempFileString, &masterCardList, true);

  for (int i = 1001; i < 1007; i++)
  {
    cout << "card[1]: ";
    masterCardList.find(i)->second.printCard();
    cout << endl << endl;
  }
  cout << "TEST END" << endl;

  return 0;
}

