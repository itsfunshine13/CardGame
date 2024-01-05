#include "../include/fileUtils.h"
#include "../include/GameMonitor.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<int, Card> masterCardList;
map<string, Profile> profileDB;

int main(){

  srand(time(NULL));
  
  string tempFileString = "";

  loadCardData(tempFileString, true);
  loadProfileData(tempFileString, true);

  GameMonitor gm;
  gm.mainMenu();

  return 0;
}

