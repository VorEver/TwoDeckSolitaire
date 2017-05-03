#include "slot.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    slot.cpp
*/


slot::slot()
{
    //ctor
}

slot::~slot()
{
    //dtor
}
// set the x coordinate for a slot
void slot::setX(int X)
{
    slotX = X;
}
// set the y coordinate for a slot
void slot::setY(int Y)
{
    slotY = Y;
}
// get the x coordinate
int slot::getX()
{
    return slotX;
}
// get the y coordinate
int slot::getY()
{
    return slotY;
}
// set the ID of the slot -- what pile it is
void slot::setSlotID(string ID)
{
    slotID = ID;
}
// get the ID of the slot -- what pile it is
string slot::getSlotID()
{
    return slotID;
}
// display the top card of the pile in the slot
void slot::displayCard()
{
    // will hold the top card
    card topCard;
    // the pip and suit of the top card
    string cardPip, cardSuit;
    // assign the top card
    topCard = slotCards.back();
    // get the pip from the top card
    cardPip = topCard.getPip();
    // get the suit from the top card
    cardSuit = topCard.getSuit();
    // characters to draw the box around the card name
    TB = '\xC4';    // top and bottom line
    LR = '\xB3';    // left and right line
    TL = '\xDA';    // top left corner
    TR = '\xBF';    // top right corner
    BL = '\xC0';    // bottom left corner
    BR = '\xD9';    // bottom right corner
    // goto the coordinates for the beginning
    gotoxy(slotX,slotY);
    // draw the top
    cout << TL << TB << TB << TR;
    // go down one line
    gotoxy(slotX,slotY+1);
    // draw the middle
    cout << LR << cardPip << cardSuit << LR;
    // go down one line
    gotoxy(slotX,slotY+2);
    // draw the bottom
    cout << BL << TB << TB << BR;
}
// add a card to the pile in the slot
void slot::addCard(card newCard)
{
    // add a card to the pile in the slot
    slotCards.push_back(newCard);
}
void slot::displayBoom() // display the draw pile
{
    TB = '\xCD';    // top and bottom line
    LR = '\xBA';    // left and right line
    TL = '\xC9';    // top left corner
    TR = '\xBB';    // top right corner
    BL = '\xC8';    // bottom left corner
    BR = '\xBC';    // bottom right corner
    // goto beginning coordinates
    gotoxy(slotX,slotY);
    // draw top
    cout << TL << TB << TB << TR;
    // go down one line
    gotoxy(slotX,slotY+1);
    // draw middle
    cout << LR << "  " << LR;
    // go down one line
    gotoxy(slotX,slotY+2);
    // draw bottom
    cout << BL << TB << TB << BR;
}
// display an empty pile
void slot::displayBlank()
{
    TB = '\xC4';    // horizontal line
    // go to the first coordinates
    gotoxy(slotX,slotY);
    // overwrite what's there with spaces
    cout << "    ";
    // go down a line
    gotoxy(slotX,slotY+1);
    // draw the blank card symbol
    cout << " "<< TB << TB << " ";
    // go down a line
    gotoxy(slotX,slotY+2);
    // overwrite what's there with spaces
    cout << "    ";
}
