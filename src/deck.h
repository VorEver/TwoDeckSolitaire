#ifndef DECK_H
#define DECK_H

#include <random>
#include <iostream>
#include <ctime>
#include <vector>
#include "tableau.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    deck.h
*/


using namespace std;

class deck
{
    /*  This class deals with the deck of cards.
        The deck for this game is constructed of
        two standard 52-card decks.
    */

    public:
        /** Default constructor */
        deck();
        /** Default destructor */
        virtual ~deck();
        // create a new double deck
        void newDeck();
        // shuffle the deck
        void shuffle();
        // display the deck (for use in debugging/testing
        void showDeck();
        // deal the deck into a tableau
        tableau deal();
    protected:
    private:
        // the deck is a vector of cards
        vector<card> playDeck;
};

#endif // DECK_H
