#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "../include/Card.h"
#include "../include/Deck.h"
#include "../include/Profile.h"
#include "../include/versions.h"
#include "../json/json/json.h"
#include "../json/json/json-forwards.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <map>

using namespace std;

// Define Global variables
extern VersionData cardlistVersion;
extern map<int, Card> masterCardList;
extern map<string, Profile> profileDB;

const string DEFAULT_CARD_LIST_FILE      = "./CardData/cardData.json";
const string DEFAULT_PLAYER_PROFILE_FILE = "./Profiles/deafult_player_profiles.json";
const string PROFILES_SAVE_FILE          = "./Profiles/profiles_save_file.json";

// FUNCTION:
//   loadCardData()
//
// PARAMETERS:
//   filePath       - path to cardData.json
//   useDefaultFile - boolean to determine if to use default cardData.json file
//
// DESCRIPTION:
//   Reads cardData.json and builds card database stored into a map
void loadCardData(string filePath, bool useDefaultFile)
{
  if (useDefaultFile == true)
  {
    filePath = DEFAULT_CARD_LIST_FILE;
  }
  ifstream inFileStream(filePath);

  JSONCPP_STRING err;
  Json::CharReaderBuilder jsonBuilder;
  jsonBuilder["collectComments"] = false;
  const std::unique_ptr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
  Json::Value root;

  bool parseJsonSuccess = parseFromStream(jsonBuilder, inFileStream, &root, &err);
  if (parseJsonSuccess == false)
  {
    cout << "JSONCPP Parsing failed: " << err << endl;
    return;
  }

  /* Read Version of card data */
  cardlistVersion.versionDescription = root["Data Description"].asString();
  cardlistVersion.release = root["Release"].asString();
  cardlistVersion.version = root["Version"].asString();

  /* Read cards */
  const Json::Value cardRoot = root["Card"];
  for (uint16_t i = 0; i < cardRoot.size(); i++)
  {
    Card tmpCard(
      cardRoot[i]["Name"].asString(),
      cardRoot[i]["Description"].asString(),
      cardRoot[i]["ID"].asString(),
      cardRoot[i]["Released"].asString(),
      cardRoot[i]["Deck Limit"].asString(),
      cardRoot[i]["Rarity"].asString(),
      cardRoot[i]["Type"].asString(),
      cardRoot[i]["Class"].asString(),
      cardRoot[i]["Subclass"].asString(),
      cardRoot[i]["First Action"].asString(),
      cardRoot[i]["Second Action"].asString()
    );

    masterCardList.insert(pair<int, Card>(stoi(tmpCard.getID()), tmpCard));
  }
}

// FUNCTION:
//   jsonListStrToStringVector()
//
// PARAMETERS:
//   cardList       - pointer to vector string of card IDs
//   jsonStrList    - string in form "[<cardID>,<cardID>,<cardID>,..]"
//
// DESCRIPTION:
//   Parses json string list to get card IDs and stores in cardList
void jsonListStrToStringVector(vector<string> *cardList, string jsonStrList)
{
  // Remove square brackets
  string tmpStr = jsonStrList.substr(1, jsonStrList.length());

  // Tokenize the substring to get back just the IDs
  stringstream tokenStream(tmpStr);
  string cardID;

  while(getline(tokenStream, cardID, ','))
  {
    cardList->push_back(cardID);
  }
}

// FUNCTION:
//   loadProfileData()
//
// PARAMETERS:
//   filePath       - path to profile.json
//   useDefaultFile - boolean to determine if to use default cardData.json file
//
// DESCRIPTION:
//   Reads profile.json and loads profiles
void loadProfileData(string filePath, bool useDefaultFile)
{
  if (useDefaultFile == true)
  {
    filePath = DEFAULT_PLAYER_PROFILE_FILE;
  }
  ifstream inFileStream(filePath);

  JSONCPP_STRING err;
  Json::CharReaderBuilder jsonBuilder;
  jsonBuilder["collectComments"] = false;
  const std::unique_ptr<Json::CharReader> jsonReader(jsonBuilder.newCharReader());
  Json::Value root;

  bool parseJsonSuccess = parseFromStream(jsonBuilder, inFileStream, &root, &err);
  if (parseJsonSuccess == false)
  {
    cout << "JSONCPP Parsing failed: " << err << endl;
    cout << "Loading default profile file" << endl;
    sleep(3);
    inFileStream = ifstream(DEFAULT_CARD_LIST_FILE);
    parseJsonSuccess = parseFromStream(jsonBuilder, inFileStream, &root, &err);
    if (parseJsonSuccess == false)
    {
      cout << "JSONCPP Parsing failed: " << err << endl;
      sleep(3);
      return;
    }
  }

  

  // Loop through profiles
  const Json::Value profileRoot = root["Profiles"];
  for (uint16_t i = 0; i < profileRoot.size(); i++)
  {
    Profile tmpProfile;
    tmpProfile.setProfileName(profileRoot[i]["Name"].asString());

    // Loop through Decks
    Json::Value deckRoot = profileRoot[i]["Decks"];
    for (uint16_t j = 0; j < deckRoot.size(); j++)
    {
      Deck tmpDeck;
      vector<string> tmpCardList;

      tmpDeck.setDeckName(deckRoot[j]["Name"].asString());

      // Get Basic Cards
      string jsonCardListString = deckRoot[j]["BasicCards"].asString();
      jsonListStrToStringVector(&tmpCardList, jsonCardListString);
      // Add basic cards to Deck
      for (uint8_t cardIdx = 0; cardIdx < tmpCardList.size(); cardIdx++)
      {
        Card tmpCard = masterCardList.at(stoi(tmpCardList.at(cardIdx)));
        tmpDeck.addToOringalDeck(tmpCard);
      }
      
      // Get Advanced Cards
      tmpCardList.clear();
      jsonCardListString = deckRoot[j]["AdvancedCards"].asString();
      jsonListStrToStringVector(&tmpCardList, jsonCardListString);
      // Add basic cards to Deck
      for (uint8_t cardIdx = 0; cardIdx < tmpCardList.size(); cardIdx++)
      {
        Card tmpCard = masterCardList.at(stoi(tmpCardList.at(cardIdx)));
        tmpDeck.addToOringalDeck(tmpCard);
      }

      tmpProfile.addDeck(tmpDeck);
    } //eof deckRoot
    
    profileDB.insert(pair<string, Profile>(tmpProfile.getProfileName(), tmpProfile));
  } //eof profileRoot
} //eof loadProfileData

#endif
