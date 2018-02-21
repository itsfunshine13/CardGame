#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "utils.h"


class Card{

private:
	string cardName, cardDescription;
	bool isCoreCard;
	Action firstAction, secondAction;
	string cardID;


public:
	Card(string cardName, string cardDescription, string cardID);
	~Card();
	inline string getCardName();
	inline string getCardDescription();
	inline bool isCore();
	inline Action getFirstAction();
	inline Action getSecondAction();
	inline int getID();
	inline intToAction(char ID);

	
};