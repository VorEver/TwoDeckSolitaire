#ifndef TABLEAU_H
#define TABLEAU_H

#include <vector>
#include <string>
#include <conio.h>
#include "card.h"
#include "slot.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    tableau.h
*/


using namespace std;

class tableau
{
    /*  the class dealing with the tableau ... the main card
        main card layout for the game
    */

    public:
        /** Default constructor */
        tableau();
        /** Default destructor */
        virtual ~tableau();
        // vector to hold the tableau layout of piles
        vector<slot> tableauSlots;
        // vector to hold the foundation layout of ascending (up) piles
        vector<slot> upSlots;
        // vector to hold the foundation layout of descending (down) piles
        vector<slot> downSlots;
        // vector to hold the hand pile
        vector<card> handCards;
        // iterator to point to which tableau pile is the current hand
        vector<slot>::iterator handSlot;
        // if there is a hand
        bool isHand;
        // create the tableau
        void createTableau();
        // display the tableau
        void displayTableau();
        // display both ascending (up) and descending (down) foundation piles
        void displayFoundation();
        // display the labels on the foundations and tableau
        void displayLabels();
        // play the game
        void play();
        // get the input from the user
        string getOption();
        // display a minimal help screen
        void displayHelp();
        // display exit message and exit the game
        void exitGame();
        // draw a card from the bank (draw pile)
        bool drawCard();
        // play the chosen card on a foundation pile
        void playCard(string);
        // prompt the user for input at the column specified
        void prompt(int, string);
        // get the card from the choice location -- actually remove it
        card getCard(string);
        // convert to uppercase
        void convert(string&);
        // determine if a card can be played on the ascending (up) foundation
        bool isPlayableUp(string);
        // play the card on the ascending (up) foundation
        void playUp(card);
        // determine if a card can be played on the ascending (up) foundation
        bool isPlayableDown(string);
        // play the card
        void playDown(card);
        // allow the user to pick if the card can be played up or down
        void onPilePick(card);
        // display the cards in the hand
        void displayHand();
        // turn a pip-suit string into a card
        card resolveCard(string);
        // determine if the game is won
        bool victoryCheck();
        // display a winning screen
        void victoryScreen();
    protected:
    private:
};

#endif // TABLEAU_H
