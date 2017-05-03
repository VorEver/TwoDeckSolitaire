#include <iostream>
#include <string>
#include "deck.h"

/*  Mama's Two-Deck Solitaire
    by J-Mag Guthrie
    (c) 2016 - All rights reserved

    main.cpp
*/

using namespace std;
void splashScreen();

int main()
{
    // display the splashscreen
    splashScreen();
    // initialize a deck
    deck cards;
    // and a tableau
    tableau myTableau;
    // build a new double deck
    cards.newDeck();
    // shuffle the deck
    cards.shuffle();
    // deal the cards into a tableau
    myTableau = cards.deal();
    // display the tableau
    myTableau.displayTableau();
    // display th labels for the tableau
    myTableau.displayLabels();
    // play the game
    myTableau.play();
    // we're done
    return 0;
}
void splashScreen()
{
    /*  Splashscreen for the game.
        Tells people what the game is
    */
    // to get keypress from user when ready to begin
    char keyPress;
    // clear the screen
    cout << string(50, '\n');
    // go to these coordinates
    gotoxy(19,3);
    cout << "    __  ___";
    gotoxy(19,4);
    cout << "   /  |/  /___ _____ ___  ____ _ _   _____";
    gotoxy(19,5);
    cout << "  / /|_/ / __ `/ __ `__ \\/ __ `/( ) / ___/";
    gotoxy(19,6);
    cout << " / /  / / /_/ / / / / / / /_/ / |/(__  )";
    gotoxy(19,7);
    cout << "/_/  /_/\\__,_/_/ /_/ /_/\\__,_/   /____/";
    gotoxy(16,9);
    cout << "  ______                    ____            __";
    gotoxy(16,10);
    cout << " /_  __/      ______       / __ \\___  _____/ /_";
    gotoxy(16,11);
    cout << "  / / | | /| / / __ \\_____/ / / / _ \\/ ___/ //_/";
    gotoxy(16,12);
    cout << " / /  | |/ |/ / /_/ /____/ /_/ /  __/ /__/ ,<";
    gotoxy(16,13);
    cout << "/_/   |__/|__/\\____/    /_____/\\___/\\___/_/|_|";
    gotoxy(20,15);
    cout << "   _____       ___ __        _";
    gotoxy(20,16);
    cout << "  / ___/____  / (_) /_____ _(_)_______";
    gotoxy(20,17);
    cout << "  \\__ \\/ __ \\/ / / __/ __ `/ / ___/ _ \\";
    gotoxy(20,18);
    cout << " ___/ / /_/ / / / /_/ /_/ / / /  /  __/";
    gotoxy(20,19);
    cout << "/____/\\____/_/_/\\__/\\__,_/_/_/   \\___/";
    gotoxy(27,21);
    cout << "Written by J-Mag Guthrie";
    gotoxy(24,22);
    cout << "(c) 2016 - All rights reserved";
    gotoxy(22,24);
    cout << "Press any key to begin the game ...";
    // get keypress
    keyPress = _getch();
    // clear the screen
    for(int counter = 0; counter < 25; counter++)
        {
            gotoxy(0,counter);
            // display a blank line
            cout << "                                                                                ";
        }

}
