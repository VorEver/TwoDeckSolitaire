#include "deck.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    deck.cpp
*/

deck::deck()
{
    //ctor

}

deck::~deck()
{
    //dtor
}

void deck::newDeck() // we create a double deck of cards in a vector
{
    /*  This function builds a double-deck of
        cards.
    */
    // ints for the suites and the pips
    int suits, pips;
    // card for new card
    card newCard;
    // all the suit symbols that can be defined
    // two sets of Hearts, Diamonds, Clubs, and Spades
    string suitSymbols[8] =
        {"H","H","D","D","C","C","S","S"};
    // all of the pip symbols, ace through king
    string pipSymbols[13] =
        {"A","2","3","4","5","6","7","8","9","T","J","Q","K"};
    // for each suit ...
    for (suits = 0; suits < 8; suits++)
    {
        // for each pip value
        for(pips = 0; pips < 13; pips++)
        {
            // set the pip of the new card
            newCard.setPip(pipSymbols[pips]);
            // set the suit of the new card
            newCard.setSuit(suitSymbols[suits]);
            // put it in the deck
            playDeck.push_back(newCard);
        }
    }
}
void deck::shuffle()
{
    /*  Shuffle the cards.
        Use time to get a random
        number
    */
    // seed the random number generator
    srand(time(0));
    // the shuffled deck
    vector<card> shuffled;
    // the drawn card from the unshuffled deck
    card drawCard;
    // the postion where the card came from
    int drawPosition;
    // an iterator for the deck
    vector<card>:: iterator it;
    // pip and suit of the temporary card
    string tmpPip, tmpSuit;
    // building a shuffled deck of 104 cards
    for(int counter = 0; counter < 104; counter++)
    {
        // determine where to draw a card from
        drawPosition = rand() % 104;
        // get the pip from that card
        tmpPip = playDeck.at(drawPosition).getPip();
        // get the suit from that card
        tmpSuit = playDeck.at(drawPosition).getSuit();
        // if that pip is blank/empty (which means that card was already drawn)
        while(tmpPip=="")
        {
            // if we're at the end
            if(drawPosition==103)
                // go to the beginning
                drawPosition = 0;
            else
                // go up one
                drawPosition++;
            // get a new pip
            tmpPip = playDeck.at(drawPosition).getPip();
            // get a new suit
            tmpSuit = playDeck.at(drawPosition).getSuit();
        }
        // set the pip at the draw position to blank/empty
        playDeck.at(drawPosition).setPip("");
        // now set the draw card pip
        drawCard.setPip(tmpPip);
        // and the suit
        drawCard.setSuit(tmpSuit);
        // add it to the shuffled deck
        shuffled.push_back(drawCard);
    }
    // make the play deck, the shuffled deck
    playDeck = shuffled;
    // clear the shuffled deck
    shuffled.clear();
}
void deck::showDeck()
{
    /*  Display the pip/suit pairs
        for the cards in the deck
        (for testing/debugging)
    */
    // drawn card
    card drawCard;
    // counter
    int counter = 1;
    // the pip and suit on the card
    string drawPip, drawSuit;
    // iterator to go through the deck
    vector<card>::iterator it;
    // go through the deck
    for(it = playDeck.begin(); it != playDeck.end();it++)
    {
        // get the card at the iterator position
        drawCard = *it;
        // output the pip and the suit and a space
        cout << drawCard.getPip() << drawCard.getSuit() << " ";
        // if there are 13
        if(counter % 13 == 0)
            // start a new line
            cout << endl;
        // increment the counter
        counter++;
    }
}
tableau deck::deal()
{
    /*  This function deals the tableau according to the rules of the game
        The rules are rather complex in terms of dealing (playing is easy)
        Cards are dealt into 14 piles, one pile for each pip number and one
        draw pile (the bank).
            ┌──┐    ┌──┐    ┌──┐    ┌──┐    ┌──┐    ┌──┐    ┌──┐
            │8C│    │8D│    │7D│    │TS│    │KC│    │6H│    │6S│
            └──┘    └──┘    └──┘    └──┘    └──┘    └──┘    └──┘
             TA      T2      T3      T4      T5      T6      T7


            ┌──┐    ┌──┐    ┌──┐    ╒══╕    ┌──┐    ┌──┐    ┌──┐
            │KH│    │JS│    │9D│    ╞══╡    │AD│    │8H│    │TH│
            └──┘    └──┘    └──┘    ╘══╛    └──┘    └──┘    └──┘
             T8      T9      TT      TB      TJ      TQ      TK
        The bank is located between the ten pile and the jack pile.  Cards are
        dealt in order, face up to the pip piles and face down to the bank.
        Also, two cards are dealt to the bank after a card is dealt to the king
        pile. However, if a card is dealt to a pile with the same pip value as
        its face, a bonus card is dealt face-down to the bank.  When an Ace or
        King is dealt to any pile, two bonus cards are dealt to the bank. The
        bonus cards are cumulative, so if an ace is dealt to the ace pile, three
        cards are dealt to the bank.
    */
    // the tableau that will be returned
    tableau myTableau;
    // create the tableau
    myTableau.createTableau();
    // the drawn card
    card drawCard;
    // iterator for the current slot / pile
    vector<slot>::iterator thisSlot;
    // iterator for the bank slot / pile -- called "boom"
    // because of the confusion between bank and blank
    vector<slot>::iterator boomSlot;
    // the bank/boom slot is always at this position
    boomSlot = myTableau.tableauSlots.begin()+10;
    // strings for the pip and the suit
    string cardPip, slotPip;
    // counter - to track what pip pile the next card goes on
    int counter= 0;
    // while there are cards to deal
    while(!playDeck.empty())
    {
        // get the top card
        drawCard = playDeck.back();
        // remove it from the deck
        playDeck.pop_back();
        // see what the pip value is
        cardPip = drawCard.getPip();
        // position the iterator to the current pile
        thisSlot = myTableau.tableauSlots.begin()+ counter;
        // see what the pip number is for this pile
        slotPip = thisSlot->getSlotID();
        // put the card on the pile
        thisSlot->slotCards.push_back(drawCard);
        // see if the pips match -- if they do
        if(cardPip == slotPip && !playDeck.empty())
        {
            // draw another card
            drawCard = playDeck.back();
            // remove it from the deck
            playDeck.pop_back();
            // put it in the bank/boom slot
            boomSlot->slotCards.push_back(drawCard);
            // if the last face-up card dealt was a king or an ace
            if((cardPip == "A" || cardPip== "K")
                    // and if there are cards left
                    && !playDeck.empty())
            {
                // draw another bonus card for the draw pile
                drawCard = playDeck.back();
                // remove it from the deck
                playDeck.pop_back();
                // put it in the bank/boom slot
                boomSlot->slotCards.push_back(drawCard);
                // if there are cards left ...
                // there should be 2 bonus cards for ace or king
                if(!playDeck.empty())
                {
                    // draw another bonus card for the draw pile
                    drawCard = playDeck.back();
                    // remove it from the deck
                    playDeck.pop_back();
                    // add it to the bank/boom pile
                    boomSlot->slotCards.push_back(drawCard);
                }
            }
        }
        // increment the counter
        counter++;
        // if we are at the end of the piles (after the king pile)
        if(counter == 14)
        {
            // if there are cards
            if(!playDeck.empty())
            {
                // draw the next card
                drawCard = playDeck.back();
                // remove it from the deck
                playDeck.pop_back();
                // put it on the bank/boom pile
                boomSlot->slotCards.push_back(drawCard);
            }
            // repeat if possible -- if there are cards
            if(!playDeck.empty())
            {
                // draw the next card
                drawCard = playDeck.back();
                // remove it from the deck
                playDeck.pop_back();
                // put it on the bank/boom pile
                boomSlot->slotCards.push_back(drawCard);
            }
            // reset the counter to 0
            counter = 0;
        }

    }
    // return the tableau
    return myTableau;
}
