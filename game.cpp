//
//  game.cpp
//  Blackjack
//
//  Created by Daniel Luan on 9/4/24.
//

#include "game.h"
#include<string>
/* End Config Includes *************************************************/

/* Public Global Variables *********************************************/
//vector<Dealer*> dealerSet;
vector<Player*> playerSet;
/* End Public Global Variables *****************************************/

/* Begin Function:addDealer *********************************************
Description : Add a Dealer to the game.
Input       : None.
Output      : None.
Return      : None.
************************************************************************/
void Game::addDealer() {
    Dealer* d = new Dealer();
    //dealerSet.push_back(d);
    dealer = d;
}
/* End Function:addDealer **********************************************/

/* Begin Function:addPlayer *********************************************
Description : Add a Player to the game.
Input       : None.
Output      : None.
Return      : None.
************************************************************************/
void Game::addPlayer() {
    Player* d = new Player();
    playerSet.push_back(d);
}
/* End Function:addPlayer ***********************************************/

/* Begin Function:start **************************************************
Description : Start game, config deck and players.
Input       : None.
Output      : None.
Return      : None.
*************************************************************************/
void Game::start() {
    cout << "******Game Start!******"<<endl;
    init_deck();
    print_deck();
    shuffler();
    print_deck();
    //Dealer* d = dealerSet.front();
    dealer->setPlayerSet(playerSet);
    dealer->Distribute();
    dealer->collectBets();
}
/* End Function:start ****************************************************/

/* Begin Function:checkWin ************************************************
Description : Check who wins in a round.
Input       : None.
Output      : None.
Return      : None.
**************************************************************************/
void Game::checkWin() {
    cout << "******Check Win******" << endl;
    //Dealer* d = dealerSet.front();
    int dealerHand = dealer->CheckHand();
    int player = 0;

    string res = "";
    for (auto p : dealer->getPlayerSet()) {
        player++;
        cout << "Player" << player << "'s Hand" << endl;
        int playerHand = p->CheckHand();
        if (playerHand == 21 && dealerHand == 21) {
            res += "Player";
            res += (char)(player + '0');
            res+=" Blackjack Push!\n";
            p->setPush();
        }else
        if (playerHand == 21 && dealerHand != 21) {
            res += "Player";
            res += (char)(player + '0');
            if( p->getAttemptDouble() == true){
                p->setDouble();
                res += " Wins DOUBLE Blackjack!\n";
            } else
                p->setWin();
                res += " Wins Blackjack!\n";
        }else
        if(playerHand != 21 && dealerHand == 21) {
            res+= "Dealer Wins, Blackjack!\n";
        }else
        if (playerHand <21 && playerHand > dealerHand) {
            res+= "Player";
            res+= (char)(player + '0');
            if( p->getAttemptDouble() == true){
                p->setDouble();
                res += " Wins DOUBLE!\n";
            } else
                p->setWin();
                res += " Wins!\n";
        }else
        if (playerHand > 21) {
            res += "Player";
            res += (char)(player + '0');
            res += " Bust, lose!\n";
        }else
        if (dealerHand > 21) {
            res += "Dealer Bust, Player";
            res+= (char)(player + '0');
            if( p->getAttemptDouble() == true){
                p->setDouble();
                res += " Wins DOUBLE!\n";
            } else
                p->setWin();
                res += " Wins!\n";
        }else
        if (playerHand == dealerHand) {
            res += "Player";
            res += (char)(player + '0');
            res+= " Push!\n";
            p->setPush();
        }else
        if (playerHand < dealerHand) {
            res += "Player";
            res += (char)(player + '0');
            res += " lose!\n";
        }
        //cout << "Player" << player << "'s updated money: $" << p->Money() << endl;
    }
        for (auto p : dealer->getPlayerSet()) {
            if(p->getDouble() == true)
                p->dWin();
            else if (p->getWin() == true)
                p->win();
            else if ( p->getPush() == true)
                p->Push();
        }
        cout << res << endl;
        int i = 1;
        for (auto p : dealer->getPlayerSet()) {
            cout << "Player" << i << "'s updated money: $" << p->Money() << endl;
            i++;
        }
}
/* End Function:checkWin ****************************************************/

/* Begin Function:turn *******************************************************
Description : Take turns, each non-blackjack player can choose to Hit or Stand,
              if hand>21, Bust!
              After all players' turn end, Dealer must Hit until hand>17,
              if hand>21, Bust, else, checkWin().
Input       : None.
Output      : None.
Return      : None.
******************************************************************************/
void Game::turn() {
    //Dealer* d = dealerSet.front();
    int player = 0;
    for (auto p : dealer->getPlayerSet()) {
        player++;
        cout << endl;
        cout << "******Player" << player << "'s move*******" << endl;
        cout << "Player" << player << "'s Hand" << endl;
        int playerHand = p->CheckHand();
        char c = ' ';
        while (c != 'S' && playerHand < 21) {
            bool split = false;
            c = p->choice();
            if (c == 'H')
                p->Hit();
            else if (c == 'S')
                /*Stand, do nothing*/;
            else if (c == 's' && p->Splittable()){
                p->Split();
                getInput(p->Splits(0), player, 'l');
                getInput(p->Splits(1), player, 'r');
                
                if ((p->Splits(0)->HandTotal() > p->Splits(1)->HandTotal() && p->Splits(0)->HandTotal() <= 21) || p->Splits(1)->HandTotal() > 21){
                    p->setHand(p->Splits(0)->getHand());
                    playerHand = p->CheckHand();
                    split = true;
                    //break;
                } else {
                    p->setHand(p->Splits(1)->getHand());
                    playerHand = p->CheckHand();
                    split = true;
                    //break;
                }
                //cout << "check" << endl;
            }
            else if (c == 'D' && p->getHand().size() == 2){
                p->Hit();
                p->SetAttemptDouble();
                p->CheckHand();
                break;
            }
            else
                cout << "Invalid input, try again." << endl;
            if (!split){
                playerHand = p->CheckHand();
            }
        }
    }
    cout << "******Turns end!******" << endl;
    while (dealer->CheckHand() < 17)
        dealer->Hit();
}

void Game::getInput(Player* p, int pNum, char dir){
    if (dir == 'l'){
        cout << "******Player" << pNum << "'s left split move*******" << endl;
        cout << "Player" << pNum << "'s left split Hand" << endl;
    } else {
        cout << "******Player" << pNum << "'s right split move*******" << endl;
        cout << "Player" << pNum << "'s right split Hand" << endl;
    }
    int playerHand = p->CheckHand();
    char c = ' ';
    while (c != 'S' && playerHand < 21) {
        bool split = false;
        c = p->choice();
        if (c == 'H')
            p->Hit();
        else if (c == 'S')
            /*Stand, do nothing*/;
        else if (c == 's' && p->Splittable()){
            p->Split();
            getInput(p->Splits(0), pNum, 'l');
            getInput(p->Splits(1), pNum, 'r');
            
            if (p->Splits(0)->HandTotal() > p->Splits(1)->HandTotal() && p->Splits(0)->HandTotal() <= 21){
                p->setHand(p->Splits(0)->getHand());
                playerHand = p->CheckHand();
                split = true;
            } else {
                p->setHand(p->Splits(1)->getHand());
                playerHand = p->CheckHand();
                split = true;
            }
            
            //cout << "check" << endl;
        }
        else
            cout << "Invalid input, try again." << endl;
        if (!split){
            playerHand = p->CheckHand();
        }
    }
}

