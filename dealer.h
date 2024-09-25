/*
============================================================================
Name        : dealer.h
Author      : ZF Song
Version     :
Copyright   : ZF Song
Description : Class - dealer, a Dealer has a hand of cards and PlayerSet he
              aganist to, also has actions of Hit, CheckHand, Distribute cards
			  and getPlayerSet, but Dealer can not choose to Stand in his turn. 
============================================================================
*/
#pragma once
/* Config Includes ***********************************************************/
#include "deck.h"
#include "player.h"
/* End Config Includes *******************************************************/

/* Begin Class: Dealer **********************************************
Description : The informations of a Dealer.
******************************************************************************/
class Dealer {
/* Private Variables ***************************************************/
private:
	vector<int> hand;
	vector<Player*> playerSet;
/* End Private Variables ***********************************************/
public:
	/* Public C++ Function Prototypes **********************************************/
	/*****************************************************************************/
	void setPlayerSet(vector<Player*>& playerSet);
    vector<int> getHand(){return hand;}
    void clearHand() {hand.clear();}
    vector<Player*> getPlayerSet(){return playerSet;}
	void Distribute();
	void Hit();
	int CheckHand();
    void collectBets();
	/*****************************************************************************/
	/* End Public C++ Function Prototypes *****************************************/
};
/* End Class: Dealer *******************************************************/
