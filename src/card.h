#ifndef CARD_H
#define CARD_H

#include <string>

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    card.h
*/

using namespace std;

class card
{
    /*  This is the card class.  Cards are
        the fundamental unit of the game
        Each card has a pip value, from Ace to King
        and a suit value of H, C, D, or S.
    */
    public:
        /** Default constructor */
        card();
        /** Default destructor */
        virtual ~card();
        // set the pip on a card
        void setPip(string);
        // set the suit on a card
        void setSuit(string);
        // retrieve the pip from a card
        string getPip();
        // retrieve a suit from a card
        string getSuit();
        // show a card -- for testing/debugging
        void showCard();
    protected:
    private:
        // the pip on a card
        // A, 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K
        string pip;
        // the suit on a card
        // H, C, D, S
        string suit;
};

#endif // CARD_H
