#include "tableau.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    tableau.cpp
*/


tableau::tableau()
{
    //ctor
}

tableau::~tableau()
{
    //dtor
}



void tableau::createTableau()
{
    /*  Creating the tableau.
        Initializing slots for each tableau pile.
    */
    // counter for the tableau piles
    int counter;
    // slots for each pile -- these will be filled when the cards are dealt
    slot pileSlot;
    // list of T labels for the Tableau slots
    string slotList[] = {"A","2","3","4","5","6","7","8","9","T","B","J","Q","K"};
    // list of X and Y coordinates for the tableau slots
    int pileXList[] = {13,21,29,37,45,53,61,13,21,29,37,45,53,61};
    int pileYList[] = {7,7,7,7,7,7,7,13,13,13,13,13,13,13};
    // list of suits for Up and Down slots for the foundation piles
    string suitList[] = {"H","C","D","S"};
    // the x coordinates for the Up and Down slots
    // they are all in the same row so have the same y coordinate
    int upXList[] = {12,19,26,33};
    int downXList[] = {41,48,55,62};

    // create the tableau
    for(counter = 0; counter < 14; counter ++)
    {
        // set the slot ID -- 1-14
        pileSlot.setSlotID(slotList[counter]);
        // set the display coordinates for that slot
        pileSlot.setX(pileXList[counter]);
        pileSlot.setY(pileYList[counter]);
        // put that slot into the tableau
        tableauSlots.push_back(pileSlot);
    }
    // create the foundation
    for(counter = 0;counter < 4; counter++)
    {
        // set the slot ID for Up and Down slots
        pileSlot.setSlotID(suitList[counter]);
        // set the Up slot x coordinate
        pileSlot.setX(upXList[counter]);
        // set the y coordinate
        pileSlot.setY(1);
        // put that slot in the foundation in the Up section
        upSlots.push_back(pileSlot);
        // reset the x coordinate to the Down x coordinate
        pileSlot.setX(downXList[counter]);
        // put that slot in the foundation in the Down section
        downSlots.push_back(pileSlot);
    }
    // initialize the hand slot to empty
    isHand = false;
}
void tableau::displayTableau()
{
    /*  Display only the tableau piles.
        The top card of each tableau pile
        (including the draw pile) is displayed
    */
    // counter to go through the tableau piles
    int counter;
    // iterator to access the appropriate slot
    vector<slot>::iterator thisSlot;
    // goes through the first part of the tableau
    for(counter = 0; counter < 10; counter++)
    {
        // the current pile
        thisSlot = tableauSlots.begin() + counter;
        // if this is the hand slot
        if(isHand && thisSlot == handSlot)
            // show a blank
            thisSlot->displayBlank();
        // if it's not empty
        else if(!thisSlot->slotCards.empty())
            // show the top card
            thisSlot->displayCard();
        else
            // otherwise show a blank card display
            thisSlot->displayBlank();
    }
    // this is the draw pile, is the bank of face-down cards to draw from
    thisSlot = tableauSlots.begin() + 10;
    // if this pile is not empty -- if there are cards to draw
    if(!thisSlot->slotCards.empty())
        // show the face-down <boom> display
        thisSlot->displayBoom();
    else
        // display the blank card display
        thisSlot->displayBlank();
    // goes through the rest of the tableau
    for(counter = 11; counter < 14; counter++)
    {
        // the current slot
        thisSlot = tableauSlots.begin() + counter;
        // if it's the hand
        if(isHand && thisSlot == handSlot)
            // show a blank card display
            thisSlot->displayBlank();
        // if it's not empty
        else if(!thisSlot->slotCards.empty())
            // show the top card
            thisSlot->displayCard();
        else
            // otherwise show a blank card display
            thisSlot->displayBlank();
    }
    // call the foundation display function
    displayFoundation();

}
void tableau::displayFoundation()
{
    /*  Displays the foundation piles
        The top card of each foundation pile is displayed.
    */
    // iterator for the foundation piles
    vector<slot>::iterator thisSlot;
    // loop to go through both the Up and Down slots
    for(int counter = 0; counter < 4; counter++)
    {
        // the Up slots ... the current slot
        thisSlot = upSlots.begin() + counter;
        // if it's not empty -- if there's a card
        if(!thisSlot->slotCards.empty())
            // display it
            thisSlot->displayCard();
        else
            // otherwise show a blank card display
            thisSlot->displayBlank();
        // the down slots ... the current slot
        thisSlot = downSlots.begin() + counter;
        // if it's not empty -- if there's a card
        if(!thisSlot->slotCards.empty())
            // display it
            thisSlot->displayCard();
        else
            // otherwise show a blank card display
            thisSlot->displayBlank();
    }
    // place cursor at the bottom
    gotoxy(56,24);

}
void tableau::displayLabels()
{
    /*  Displays the labels on the tableau piles and foundation piles
        These do not need to be redrawn very often.
    */
    // list of x coordinates for tables piles.
    int xList[] = {14,22,30,38,46,54,62,14,22,30,38,46,54,62};
    // list of y coordinates for tableau piles
    int yList[] = {10,10,10,10,10,10,10,16,16,16,16,16,16,16};
    // list of pile names for tableau piles - A for ace, T for Ten, B for Bank, etc.
    string pipList[] = {"A","2","3","4","5","6","7","8","9","T","B","J","Q","K"};
    // list of suit designations for foundation piles
    string suitList[] = {"H","C","D","S"};
    // the x coordinates for the foundation piles are calculable
    int promptX = 0;
    // display the labels for the tableau piles
    for(int counter = 0; counter < 14; counter++)
    {
        // go to the x,y indicated
        gotoxy(xList[counter],yList[counter]);
        // display T + the pile name
        cout << "T" << pipList[counter];
    }
    // characters for horizontal double lines
    // left side
    char LS = '\xC6';
    // right side
    char RS = '\xB5';
    // horizontal line
    char HL = '\xCD';
    // left line
    string leftLine = LS + string(5,HL);
    // right line
    string rightLine = string(5,HL) + RS;
    // go to these coordinates
    gotoxy(12,5);
    // display the label for the up piles
    cout << leftLine << " ACE TO KING " << rightLine;
    // now display the pile labels for the up piles
    for(int counter = 0; counter < 4; counter++)
    {
        // set the x coordinate
        promptX = 13 + (7*counter);
        // go to the x,y
        gotoxy(promptX,4);
        // display U for Up + the suit designation
        cout << "U" << suitList[counter];
    }
    // go to these coordinates
    gotoxy(41,5);
    // display the label for the down piles
    cout << leftLine << " KING TO ACE " << rightLine;
    // now display the pile labels for the down piles
    for(int counter = 0; counter < 4; counter++)
    {
        // set the x coordinate
        promptX = 42 + (7*counter);
        // go to the x,y
        gotoxy(promptX,4);
        // display the D for Down + the suit designation
        cout << "D" << suitList[counter];
    }
}

void tableau::play()
{
    /*  Plays the game.

    */
    // is the game over?
    bool gameOver = false;
    // the user's choice for their move
    string choice = "";
    // the field of the card the user wishes to play (tableau or hand)
    string field = "";
    // the pile within the field
    string pile = "";

    // display the tableau
    displayTableau();
    // prompt the user for a card
    prompt(23,"ENTER CARD TO PLAY (? FOR HELP): ");
    // while the game is not over
    while(!gameOver)
    {
        // get the user's choice
        choice = getOption();
        // if the user asks for help
        if(choice == "?")
        {
            // display the help screen
            displayHelp();
        }
        // if they want to quit
        else if(choice == "X")
            // quit
            gameOver = true;
        else
        {
            // where on the screen the card is the user wants to play
            field = choice.substr(0,1);
            // what pile the card is on
            pile = choice.substr(1,1);
            // if it's the draw pile (bank)
            if(field == "T" && pile == "B") // if it's a draw
            {
                // if there are no more cards
                if(!drawCard())
                prompt(16,"THERE ARE NO MORE CARDS - GAME OVER - X TO EXIT  ");
            }
            else
            {
                // play the card
                playCard(choice);
                // prompt for the next card
                if(victoryCheck())
                {
                    victoryScreen();
                    gameOver = true;
                }
                else
                    prompt(23,"ENTER CARD TO PLAY (? FOR HELP): ");
            }

        }
    }
    exitGame();
}
string tableau::getOption()
{
    /*  gets the card choice to play from the user
        uses the two-letter designation shown below
        each pile or ? for help or X or x to quit.
    */

    // the return string
    string option;
    // boolean for if we're done
    bool isValid = false;
    // the input character
    char keyPress;
    // as long as it's not valid
    while(!isValid)
    {
        // get the key press
        keyPress = _getch();
        // switch on uppercase of the character
        switch(toupper(keyPress))
        {
        // if X -- return X to exit
        case 'X':
            option = "X";
            isValid = true;
            break;
        // if ? return ? for help
        case '?':
            option = "?";
            isValid = true;
            break;
        // if T, it's a tableau pile -- find out which one
        case 'T':
            // get another keypress
            keyPress = _getch();
            // see if it's a valid  pile
            switch(toupper(keyPress))
            {
            case 'A':
                option = "TA";
                isValid = true;
                break;
            case '2':
                option = "T2";
                isValid = true;
                break;
            case '3':
                option = "T3";
                isValid = true;
                break;
            case '4':
                option = "T4";
                isValid = true;
                break;
            case '5':
                option = "T5";
                isValid = true;
                break;
            case '6':
                option = "T6";
                isValid = true;
                break;
            case '7':
                option = "T7";
                isValid = true;
                break;
            case '8':
                option = "T8";
                isValid = true;
                break;
            case '9':
                option = "T9";
                isValid = true;
                break;
            case 'T':
                option = "TT";
                isValid = true;
                break;
            case 'B':
                option = "TB";
                isValid = true;
                break;
            case 'J':
                option = "TJ";
                isValid = true;
                break;
            case 'Q':
                option = "TQ";
                isValid = true;
                break;
            case 'K':
                option = "TK";
                isValid = true;
                break;
            default:
                isValid = false;
            }
            break;
        case 'H':
            keyPress = _getch();
            switch(toupper(keyPress))
            {
            case '1':
                option = "H1";
                isValid = true;
                break;
            case '2':
                option = "H2";
                isValid = true;
                break;
            case '3':
                option = "H3";
                isValid = true;
                break;
            case '4':
                option = "H4";
                isValid = true;
                break;
            case '5':
                option = "H5";
                isValid = true;
                break;
            case '6':
                option = "H6";
                isValid = true;
                break;
            case '7':
                option = "H7";
                isValid = true;
                break;
            case '8':
                option = "H8";
                isValid = true;
                break;
            case '9':
                option = "H9";
                isValid = true;
                break;
            case 'T':
                option = "HT";
                isValid = true;
                break;
            case 'E':
                option = "HE";
                isValid = true;
                break;
            default:
                isValid = false;
            }
            break;
        default:
            isValid = false;
        }
    }
    return option;
}
void tableau::displayHelp()
{
    /*  This function displays a help screen for the user.
        It describes game play and the object of the game.
    */
    // characters for the card
    char TB = '\xC4';
    char LR = '\xB3';
    char TL = '\xDA';
    char TR = '\xBF';
    char BL = '\xC0';
    char BR = '\xD9';
    // keypress for exiting help
    char keypress;
    // clear the screen, starting at 0,0
    gotoxy(0,0);
    cout << string(50,'\n');
    // The help screen
    cout << "MAMA'S TWO-DECK SOLITAIRE \n\n";

    cout << "OBJECT:\n";
    cout << "Build eight foundations piles.  One pile ace to king and one pile king to ace\n";
    cout << "for each of the four suits.\n\n";

    cout << "SAMPLE CARD:   "<< TL << TB << TB << TR <<"    This card is the 2 of Hearts\n";
    cout << "               "<< LR << "2H" << LR << "    It is in the Tableau Queen pile\n";
    cout << "               "<< BL << TB << TB << BR <<"    as shown by the TQ below it\n";
    cout << "                TQ     Type TQ to play it to a foundation\n\n";

    cout << "PLAY:\n";
    cout << "Cards are dealt to the tableau. There are 14 tableau piles. One for each pip\n";
    cout << "designation (ace through king) and one for the bank (draw pile). They are laid\n";
    cout << "out in two rows of seven piles, with the bank in the middle of the bottom row\n";
    cout << "between the ten pile and the jack pile.\n\n";

    cout << "When a card is drawn from the bank, the corresponding tableau pile becomes the\n";
    cout << "hand.  The hand is laid out below the tableau piles.\n\n";

    cout << "To play a card to a foundation pile, type the two-letter code below the card.\n";
    cout << "In the example above, type TQ to play the 2 of Hearts to the foundation.\n\n";

    cout << "Press any key to return to the game ...";
    // get keypress
    keypress = _getch();
    // clear the screen, starting at 0,0
    gotoxy(0,0);
    cout << string(50,'\n');
    //display the foundation
    displayFoundation();
    // the tableau
    displayTableau();
    // if there's a hand
    if(isHand)
        // the hand
        displayHand();
    // the labels
    displayLabels();
}
void tableau::exitGame()
{
    // char for key press to exit game
    char keyPress;
    // give the user a goodbye message
    prompt(24,"Press any key to exit the game ...");
    // get key press
    keyPress = _getch();
}

bool tableau::drawCard() // *** *** ***
{
    /*  This function draws a card from the draw pile, or bank
        The corresponding pile then is laid out to form the hand
    */
    // the top card of the draw pile
    card topCard;
    // the pip on the top card
    string topPip;
    // an iterator to hold the slot for the draw pile/bank -- called boom
    // to differentiate it from blank
    vector<slot>::iterator boomSlot;
    // an iterator to find the slot for the pip on the top card
    vector<slot>::iterator findSlot;
    // this is always true
    boomSlot = tableauSlots.begin() + 10;
    // show the table
    displayTableau();
    // if there's a card in the draw pile/bank
    if(!boomSlot->slotCards.empty())
    {
        // draw it
        topCard = boomSlot->slotCards.back();
        // see what pip it has
        topPip = topCard.getPip();
        // remove it from the draw pile/bank
        boomSlot->slotCards.pop_back();
        // find the slot with the slotID that matches the pip
        for(findSlot = tableauSlots.begin();findSlot != tableauSlots.end();findSlot++)
            // when you find it, that's the hand
            if(topPip == findSlot->slotID)
                handSlot = findSlot;
        // insert the card you drew from the draw pile at the bottom of the hand pile
        handSlot->slotCards.insert(handSlot->slotCards.begin(),topCard);
        // there is a hand, so set isHand to true
        isHand = true;
        // lay out the hand
        displayHand();
        // redraw the tableau
        displayTableau();
        // we successfully drew the card
        return true;
    }
    else
        // we couldn't draw the card
        return false;
}
card tableau::resolveCard(string choice)
{
    /*  Resolve card gets the card that corresponds
        to the pile choice of the user
        It returns the top card of the specified pile
    */
    // The return value or hot card
    card hotCard;
    // the pile the card comes from
    vector<card> hotPile;
    // a slot iterator
    vector<slot>::iterator it;
    // an int to position the iterator
    int position;
    // list of valid piles to draw from, including the bank
    string piles = "A23456789TBJQK";
    // likst of valid suit designations
    string suits = "HCDS";
    // the field (hand or tableau pile
    string tableauField;
    // the pile within the field
    string pileName;
    // set the field
    tableauField = choice.substr(0,1);
    // set the pile
    pileName = choice.substr(1,1);
    // if the field is the tableau piles
    if(tableauField == "T") // it's from the top of a pile
    {
        // find the pile position in the piles string
        position = piles.find(pileName);
        // use the position to set the iterator
        it = tableauSlots.begin() + position;
        // the hotcard equals the top card on the pile
        hotCard = it->slotCards.back();
        // return it
        return hotCard;
    }
    // if the field is the hand
    else if(tableauField == "H")
    {
        // the postion is the pile number - 1
        position = stoi(pileName) - 1;
        // the value of the hand card in that position is what we want
        hotCard = handSlot->slotCards.at(position);
        // return it
        return hotCard;
    }
}

void tableau::playCard(string choice)
{
    /*  This function actually plays the card from the place
        the user chooses to the foundation pile
    */
    // the card that will be played
    card hotCard;
    // if the card can be played on either pile
    if(isPlayableUp(choice) && isPlayableDown(choice))
    {
        // get the card
        hotCard = getCard(choice);
        // let the user pick which pile, and play it
        onPilePick(hotCard);
    }
    // if the card can be played on the up pile of its suit
    else if(isPlayableUp(choice))
    {
        // get the card
        hotCard = getCard(choice);
        // play it
        playUp(hotCard);
    }
    // if it can be played down
    else if(isPlayableDown(choice))
    {
        // get the card
        hotCard = getCard(choice);
        // play it
        playDown(hotCard);
    }
}
void tableau::prompt(int column, string userPrompt)
{
    /*  this function displays a prompt on the
        bottom of the screen
    */
    // go to these screen coordinates
    gotoxy(0,24);
    // these two lines clear the current prompt
    for(int counter = 0; counter < 80; counter ++)
        cout << " ";
    // go to the appropriate coordinate
    gotoxy(column,24);
    // display the prompt
    cout << userPrompt;
}

card tableau::getCard(string option)
{
    /*  This function actually moves a card from the non-bank pile
        that's why the "hot card" designation -- this card
        has to be directly placed somewhere
    */
    // the card in play
    card hotCard;
    // the pile where the card will be played
    vector<card> hotPile;
    // the tableau iterator
    vector<slot>::iterator it;
    // iterator for the tableau pile if a card originates there
    vector<card>::iterator it2;
    // int for positioning the iterator
    int position;
    // list of valid tableau piles as a string
    string piles = "A23456789TBJQK";
    // list of valid suits as a string
    string suits = "HCDS";
    // where the card originates ... the tableau or the hand
    string tableauField;
    // if on the tableau, the pile number, if on the hand, the card number
    string pileName;
    // set the field
    tableauField = option.substr(0,1);
    // set the pile
    pileName = option.substr(1,1);
    // if it's the tableau
    if(tableauField == "T") // it's from the top of a pile
    {
        // set the position for the tableau iterator
        position = piles.find(pileName);
        // set the tableau iterator to that position
        it = tableauSlots.begin() + position;
        // get the hot card
        hotCard = it->slotCards.back();
        // remove it from the pile
        it->slotCards.pop_back();
        // show the new tableau
        displayTableau();
        // return the card
        return hotCard;
    }
    // if the field is the hand
    else if(tableauField == "H")
    {
        // determine the position
        position = stoi(pileName) - 1;
        // get the card
        hotCard = handSlot->slotCards.at(position);
        // set the iterator to that postion
        it2 = handSlot->slotCards.begin() + position;
        // remove the card
        handSlot->slotCards.erase(it2);
        // show the new hand
        displayHand();
        // return the card
        return hotCard;
    }
}
void tableau::convert(string& s)
{
    /* converts a string in-place
       to upper case
    */
    // for each character
    for(int i = 0; i < s.length();i++)
    {
        // change it to upper case
        s[i] = toupper(s[i]);
    }
}
bool tableau::isPlayableUp(string choice)
{
    /*  Determine if a card can be played on the Up
        foundation pile of its suit
    */
    // the card the user is trying to play
    card choiceCard;
    // the pip of the choice card
    string choicePip;
    // int for the choice card pip
    int pipNum;
    // the suit of the choice card
    string choiceSuit;
    // int for the choice card suit
    int suitNum;
    // valid pips
    string allPips = "A23456789TJQK";
    // valid suits
    string allSuits = "HCDS";
    // slot iterator
    vector<slot>::iterator it;
    // top card for a pile
    card topCard;
    // the top card pip
    string topPip;
    // the int for the top card pip
    int topPipNum;
    // use resolveCard to turn the user's choice into the card value
    choiceCard = resolveCard(choice);
    // set the pip from the choice card
    choicePip = choiceCard.getPip();
    // set the suit from the choice card
    choiceSuit = choiceCard.getSuit();
    // find the pip position in th allPips list
    pipNum = allPips.find(choicePip);
    // find the suit position in the allSuits list
    suitNum = allSuits.find(choiceSuit);
    // use the suit position to set the iterator to the correct Up pile
    it = upSlots.begin() + suitNum;
    // check if it's empty
    if(it->slotCards.empty())
    {
        // if it's a ace (pipNum 0)
        if(pipNum==0)
            // it's playable
            return true;
        else
            // it's not
            return false;
    }
    // see what the current top card in the pile is
    topCard = it->slotCards.back();
    // get the pips from the top card
    topPip = topCard.getPip();
    // find the pip number
    topPipNum = allPips.find(topPip);
    // if the choice card is the next card in ascending order
    if(pipNum == topPipNum + 1)
        // it's playable
        return true;
    else
        // it's not
        return false;
}
void tableau::playUp(card choiceCard)
{
    /*  This function actually moves the card
        from the pile it was in to the foundation
        Up pile of its suit
    */
    // string to hold the pip from the choice card
    string choicePip;
    // int for the pip position
    int pipNum;
    // string for the choice suit
    string choiceSuit;
    // int for the suit position
    int suitNum;
    // string of all pips for finding pip position
    string allPips = "A23456789TJQK";
    // string of all suits for finding suit position
    string allSuits = "HCDS";
    // slot iterator for finding tableau pile
    vector<slot>::iterator it;
    // get the pip from the choice card
    choicePip = choiceCard.getPip();
    // get the suit from the choice card
    choiceSuit = choiceCard.getSuit();
    // find the pip position in the allPips list
    pipNum = allPips.find(choicePip);
    // find the suit position in the allSuits list
    suitNum = allSuits.find(choiceSuit);
    // set the Up slot pile iterator
    it = upSlots.begin() + suitNum;
    // add the card to the Up pile
    it->slotCards.push_back(choiceCard);
    // display the foundation with the played card
    displayFoundation();
}
bool tableau::isPlayableDown(string choice)
{
    /*  Determine if a card can be played on the Down
        foundation pile of its suit
    */
    // the card chosen by the user
    card choiceCard;
    // the pip on the choice card
    string choicePip;
    // the int to store the position of the pip
    int pipNum;
    // the suit on the choice card
    string choiceSuit;
    // the int to store the position of the suit
    int suitNum;
    // list of all valid pips, in order
    string allPips = "KQJT98765432A";
    // list of all valid suits
    string allSuits = "HCDS";
    // iterator for Down piles
    vector<slot>::iterator it;
    // the top card of the Down pile of the appropriate suit
    card topCard;
    // pip on the top card
    string topPip;
    // position of the pip of the top card
    int topPipNum;
    // use resolveCard to get the card the user chose
    choiceCard = resolveCard(choice);
    // set the pip from the choice card
    choicePip = choiceCard.getPip();
    // set the suit from the choice card
    choiceSuit = choiceCard.getSuit();
    // find the pip position from the allPips list
    pipNum = allPips.find(choicePip);
    // find the suit position from the allSuits list
    suitNum = allSuits.find(choiceSuit);
    // use the suit position to set the iterator to the correct Down pile
    it = downSlots.begin() + suitNum;
    // check if it's empty
    if(it->slotCards.empty())
    {
        // if it's a K (pipNum 0)
        if(pipNum==0)
            // it's playable
            return true;
        else
            // it's not
            return false;
    }
    // see what the current top card in the pile is
    topCard = it->slotCards.back();
    // get the pips from the top card
    topPip = topCard.getPip();
    // find the pip number
    // (these are in reverse order because it's a Down pile)
    topPipNum = allPips.find(topPip);
    // if the choice card is the next in descending order
    if(pipNum == topPipNum + 1)
        // it's playable
        return true;
    else
        // it's not
        return false;
}
void tableau::playDown(card choiceCard)
{
    /*  THis function actuall moves the card
        from the pile it was in to the foundation
        Down pile of its suit
    */
    // string to store the pip from the choice card
    string choicePip;
    // int for the pip position
    int pipNum;
    // string for the choice suit
    string choiceSuit;
    // int for the choice position
    int suitNum;
    // string of all pips for finding pip position (reverse order for Down pile
    string allPips = "KQJT98765432A";
    // string of all suits for finding suit position
    string allSuits = "HCDS";
    // slot iterator for finding tableau pile
    vector<slot>::iterator it;
    // get the pip from the choice card
    choicePip = choiceCard.getPip();
    // get the suit from the choice card
    choiceSuit = choiceCard.getSuit();
    // find the pip position in the allPips string (reverse order for Down piles)
    pipNum = allPips.find(choicePip);
    // find the suit position in the allSuits string
    suitNum = allSuits.find(choiceSuit);
    // set the Down slot pile iterator
    it = downSlots.begin() + suitNum;
    // add the card to the Down pile
    it->slotCards.push_back(choiceCard);
    // display the foundation with the played card
    displayFoundation();
}
void tableau::onPilePick(card hotCard)
{
    /*  If a card is playable on either the Up or Down
        foundation pile, the use can choose which one.
    */
    // char to hold the input
    char inputData;
    // start out assuming it's bad
    bool notGood = true;
    // prompt the user
    prompt(21,"PLAY THIS CARD UP OR DOWN (U OR D) ?");
    // get the input
    inputData = _getch();
    // while it's not good input
    while(notGood)
    {
        // if it's for the Up pile
        if(toupper(inputData) == 'U')
        {
            // play card on the Up foundation pile
            playUp(hotCard);
            // we had good input
            notGood = false;
        }
        // otherwise if it's down
        else if (toupper(inputData) == 'D')
        {
            // play card on the Down foundation pile
            playDown(hotCard);
            // we had good input
            notGood = false;
        }
    }
    prompt(23,"ENTER CARD TO PLAY (? FOR HELP): ");
}
void tableau::displayHand()
{
    /*  Displays the cards in the hand
        with their labels
    */
    // If there needs to be a hand displayed

    int dispX = 3, dispY = 19, counter = 0;
    // strings for the card pip and suit for each card to be displayed
    string cardPip, cardSuit;
    // the iterator to go through the hand
    vector<card>::iterator thisCard;
    // clear the hand area
    for(int counter = 0; counter < 4; counter++)
    {
        gotoxy(0,(19+counter));
        for(int counter2 = 0; counter2 < 80; counter2++)
                cout << " ";
    }
    // display the cards in the slot as the hand.
    // for each card in the hand
    for(thisCard = handSlot->slotCards.begin();thisCard != handSlot->slotCards.end();thisCard++)
    {
        // get the pip for the current card
        cardPip = thisCard->getPip();
        // get the suit for the current card
        cardSuit = thisCard->getSuit();
        // set the column for the card display
        dispX = 3 + (7 *counter);
        // characters for the card outline
        char TB = '\xC4';   // top and bottom
        char LR = '\xB3';   // left and right
        char TL = '\xDA';   // top left corner
        char TR = '\xBF';   // top right corner
        char BL = '\xC0';   // bottom left corner
        char BR = '\xD9';   // bottom right corner
        // goto the coordinates
        gotoxy(dispX,dispY);
        // top line
        cout << TL << TB << TB << TR;
        // goto coordinates
        gotoxy(dispX,dispY+1);
        // middle line, including card designation
        cout << LR << cardPip << cardSuit << LR;
        // goto coordinates
        gotoxy(dispX,dispY+2);
        // bottom line of card
        cout << BL << TB << TB << BR;
        // go down another line (3 lines from start) and over a column
        gotoxy(dispX+1,dispY+3);
        // if it's a digit
        if(counter < 9)
            // display H + the digit
            cout << "H" << ++counter;
        // if it's 10
        else if(counter == 9)
        {
            // display HT for Hand Ten
            cout << "HT";
            ++counter;
        }
        else if(counter == 10)
        {
            // display HE for Hand Eleven -- that's as many as fit
            cout << "HE";
            ++counter;
        }
    }
    // go to the place in the tableau where the hand was taken from and display a blank card display
    handSlot->displayBlank();
    // show a prompt
    prompt(23,"ENTER CARD TO PLAY (? FOR HELP): ");

}
bool tableau::victoryCheck()
{
    /*  This function checks to see if the game is won.
        If so, it displays a victory screen.
    */
    // iterator for dealing with slots/piles
    vector<slot>::iterator it;
    // the top card in the pile
    card topCard;
    // pip on top card
    string topPip;
    // count through the Up foundation piles
    for(it = upSlots.begin(); it != upSlots.end(); it++)
    {
        // if there are no cards
        if(it->slotCards.empty())
        {
            return false;
        }
        else
        {
            // get the top card
            topCard = it->slotCards.back();
            // get the pips from the top card
            topPip = topCard.getPip();
            // if it's not a king
            if(topPip != "K")
            {
                // we can quit checking
                return false;
            }
        }
    }
    // iterate through the down foundation pile
    for(it = downSlots.begin(); it != downSlots.end(); it++)
    {
        // if there are no cards
        if(it->slotCards.empty())
        {
            return false;
        }
        else
        {
            // get the top card
            topCard = it->slotCards.back();
            // get the pips from the top card
            topPip = topCard.getPip();
            // if it's not a king
            if(topPip != "A")
            {
                // we can quit checking
                return false;
            }
        }
    }
    // if nothing keeps it from being a victory, it is one
    return true;
}
void tableau::victoryScreen()
{
    /*  Display a victory screen to show that the game has been won.
    */
    // counter for the loop to write blank lines to clear the screen area
    int counter;
    // the loop to clear the screen
    for(counter = 7; counter < 25; counter++)
    {
        // go to the 0 column in the counter row
        gotoxy(0,counter);
        // display a blank line
        cout << "                                                                                ";
    }
    // now that the screen is clear, we will display the WINNER text
    gotoxy(7,7);
    cout << " ____      ____ _____ ____  _____ ____  _____ ________ _______";
    gotoxy(7,8);
    cout << "|_  _|    |_  _|_   _|_   \\|_   _|_   \\|_   _|_   __  |_   __ \\";
    gotoxy(7,9);
    cout << "  \\ \\  /\\  / /   | |   |   \\ | |   |   \\ | |   | |_ \\_| | |__) |";
    gotoxy(7,10);
    cout << "   \\ \\/  \\/ /    | |   | |\\ \\| |   | |\\ \\| |   |  _| _  |  __ /";
    gotoxy(7,11);
    cout << "    \\  /\\  /    _| |_ _| |_\\   |_ _| |_\\   |_ _| |__/ |_| |  \\ \\_";
    gotoxy(7,12);
    cout << "     \\/  \\/    |_____|_____|\\____|_____|\\____|________|____| |___|";
    gotoxy(0,18);
}
