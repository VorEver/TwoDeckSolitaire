#ifndef SLOT_H
#define SLOT_H

#include <vector>
#include <iostream>
#include "card.h"
#include "gotoxy.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    slot.h
*/


using namespace std;

class slot
{
    /*  The slot class. These are the slots that
        hold piles of cards in the tableau and the
        foundation
    */
    public:
        /** Default constructor */
        slot();
        /** Default destructor */
        virtual ~slot();
        // vector for a card pile
        vector<card> slotCards;
        // id of the card pile
        string slotID;
        // Box edges and corners for building card display
        // T for top, B for bottom, L for left, R for right
        char TB;
        char LR;
        char LS;
        char RS;
        char TL;
        char TR;
        char BL;
        char BR;
        // set the x coordinate for where the pile will be displayed
        void setX(int);
        // set the y coordinate for where the pile will be displayed
        void setY(int);
        // retrieve the x coordinate
        int getX();
        // retrieve the y coordinate
        int getY();
        // set the ID for the pile
        void setSlotID(string);
        // get the ID
        string getSlotID();
        // display the top card
        void displayCard();
        // display a card "back" for the bank or draw pile
        // called boom because it's too easy to typo bank/blank
        void displayBoom();
        // display empty slot/blank card space
        void displayBlank();
        // add a card to the top of a piel
        void addCard(card);
    protected:
    private:
        // x coordinate
        int slotX;
        // y coordinate
        int slotY;
};

#endif // SLOT_H
