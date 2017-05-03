#include <iostream>
#include "card.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    card.cpp
*/


card::card()
{
    //ctor
}

card::~card()
{
    //dtor
}
// gets the suit from a card
string card::getSuit()
{
    return suit;
}
// gets the pip from a card
string card::getPip()
{
    return pip;
}
// sets the pip on a card
void card::setPip(string newPip)
{
    pip = newPip;
}
// sets the suit on a card
void card::setSuit(string newSuit)
{
    suit = newSuit;
}
// shows the pip/suit of a card and a space
// for testing/debugging only
void card::showCard()
{
    cout << pip << suit << " ";
}
