/*
============================================================================
Name        : player.h
Description : Class - Player, a Player has a hand of cards and has actions of
              Hit, Stand, Double, Split, CheckHand and make choice to the 
			  actions above in his turn.
============================================================================
*/
#pragma once
/* Config Includes ***********************************************************/
#include "deck.h"
#include <random>
/* End Config Includes *******************************************************/

/* Begin Class: Player **********************************************
Description : The informations of a Player.
******************************************************************************/
class Player {
/* Private Variables ***************************************************/
private:
	vector<int> hand;
    vector<Player*> splitPlayers;
    int amntMoney = 100;
    int betSize;
    bool attemptDouble = false;
    bool doubleWin = false;
    bool won = false;
    bool push = false;
/* End Private Variables ***********************************************/
public:
	/* Public C++ Function Prototypes **********************************************/
	/*****************************************************************************/
	void Hit();
	void Stand();
	void Double();
	void Split();
	int CheckHand();
    int Money() {return amntMoney;}
    
    void setBet(int money){ betSize = money;}
    void bet(int betAmnt) {amntMoney -= betAmnt;}
    
    void dWin() {amntMoney += 3 * betSize;}
    void win() {amntMoney += 2 * betSize;}
    void Push() {amntMoney += betSize;}
    
    void SetAttemptDouble() {attemptDouble = true;}
    void setDouble() {doubleWin = true;}
    void setWin() {won = true;}
    void setPush() {push = true;}
    
    bool getAttemptDouble() {return attemptDouble;}
    bool getDouble() {return doubleWin;}
    bool getWin() {return won;}
    bool getPush() {return push;}
    
    int HandTotal();
    int generateRandomInteger(int min, int max);
    bool Splittable();
	char choice();
    void setHand(vector<int> newHand){hand = newHand;}
    vector<int> getHand(){return hand;}
    void clearHand() {hand.clear();}
    Player* Splits(int i){
        return splitPlayers[i];
    }
    
	/*****************************************************************************/
	/* End Public C++ Function Prototypes ******************************************/
};
/* End Class: Player *******************************************************/

class SplitPlayer : public Player{
    
private:
    vector<int> hand1;
    vector<int> hand2;
    
public:
    void Hit() = delete;
    int CheckHand() = delete;

};
