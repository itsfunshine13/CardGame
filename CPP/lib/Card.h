#ifndef CARD_H
#define CARD_H


#include <string>
#include "utils.h"


Card::Card(string cardName, string cardDescription, string cardID){
	this.cardName = cardName;
	this.cardDescription = cardDescription;
	this.cardID = cardID;
	this.isCore = ((cardID[0] == '0') ? true : false);
	this.firstAction intToAction(cardID[1]);
	this.secondAction intToAction(cardID[2]);
		


}//eo constructor
Card::~Card(){}

string Card::getCardName(){
	return this.cardName;
}

string Card::getCardDescription(){
	return this.cardDescription;
}

bool Card::isCore(){
	return this.isCore;
}

Action Card::getFirstAction(){
	return this.firstAction;
}
Action Card::getSecondAction(){
	return this.secondAction;
}

int Card::getID(){
	return this.cardID;
}

Action intToAction(char ID){
	switch(ID){
		case '1':
			return ATTACK;
		case '2':
			return DEFEND;
		case '3':
			return HEAL;
		default:
			cout << ">> DBUG >> SHOULD NOT GET HERE. SOFTWARE FAULT" << endl;
			break;
	}//eo switch
}

#endif