//
//  main.cpp
//  Blackjack
//
//  Created by Daniel Luan on 9/4/24.
//

#include<iostream>
#include "game.h"
/* End Config Includes *******************************************************/

/* Begin Function:main **************************************************
Description : Let's play Blackjack!
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
int main() {
    //Add a Dealer
    Game g;
    g.addDealer();
    //Add players
    int numPlayers;
    cout << "Enter number of players: " << endl;
    cin >> numPlayers;
    while (numPlayers > 10 || numPlayers < 1){
        cout << "Invalid Input" << endl;
        cout << "Enter number of players: " << endl;
        cin >> numPlayers;
    }
    for (int i = 0; i < numPlayers; i++){
        g.addPlayer();
    }
    
    char anotherRound = 'y';
    
    while (anotherRound == 'y'){
        //Start game
        g.start();
        g.turn();
        g.checkWin();
        cout << "Play another round?:" << endl;
        cin >> anotherRound;

        while (anotherRound != 'y' && anotherRound != 'n'){
            cout << "Invalid Input" << endl;
            cout << "Play another round?:" << endl;
            cin >> anotherRound;
        }
        g.getDealer()->clearHand();
        for (auto player : g.getDealer()->getPlayerSet()) {
            player->clearHand();
        }
    }
    system("pause");
}
