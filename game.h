//
//  game.hpp
//  Blackjack
//
//  Created by Daniel Luan on 9/4/24.
//

#include <stdio.h>

#pragma once
/* Config Includes ***********************************************************/
#include "dealer.h"
/* End Config Includes *******************************************************/

/* Public C++ Function Prototypes ********************************************/
/*****************************************************************************/
class Game
{
public:
    void addDealer();
    void addPlayer();
    Dealer* getDealer() {return dealer;}
    void start();
    void checkWin();
    void turn();
    void getInput(Player* p, int pNum, char dir);
private:
    Dealer* dealer;
};

