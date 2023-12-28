#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

#include "../include/Card.h"
#include "../include/Profile.h"
#include "../include/versions.h"
#include "../json/json/json.h"
#include "../json/json/json-forwards.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

const string DEFAULT_CARD_LIST_FILE = "./CardData/cardData.json";
const string DEFAULT_PLAYER_PROFILE_FILE = "./Profiles/player_profiles.json";

// FUNCTION:
//   loadCardData()
//
// PARAMETERS:
//   filePath       - path to cardData.json
//   cardDB         - pointer to card database stored in a map. <CardID, Card>
//   useDefaultFile - boolean to determine if to use default cardData.json file
//
// DESCRIPTION:
//   Reads cardData.json and builds card database stored into a map
void loadCardData(string filePath, map<int, Card> *cardDB, bool useDefaultFile)
{
  VersionData *cardVersionPtr = &cardlistVersion;

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
  cardVersionPtr->versionDescription = root["Data Description"].asString();
  cardVersionPtr->release = root["Release"].asString();
  cardVersionPtr->version = root["Version"].asString();

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

    cardDB->insert(pair<int, Card>(stoi(tmpCard.getID()), tmpCard));
  }
}

// FUNCTION:
//   loadProfileData()
//
// PARAMETERS:
//   filePath       - path to profile.json
//   cardDB         - pointer to card database stored in a map. <CardID, Card>
//   useDefaultFile - boolean to determine if to use default cardData.json file
//
// DESCRIPTION:
//   Reads profile.json and loads profiles
void loadProfileData(string filePath, map<string, Profile> *cardDB, bool useDefaultFile)
{

}
#endif
