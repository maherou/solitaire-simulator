//
// Created by Michael Carroll on 2019-02-17.
//

#ifndef SOLITAIRE_CARD_H
#define SOLITAIRE_CARD_H

#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Card{

        public:
        //Ranks the different Suits and assigns a name to the corresponding number
        static const int HEARTS = 0, SPADES = 1, DIAMONDS = 2, CLUBS = 3;

        //Assigns a name to the corresponding numerical value, for cards that are not numeric
        static const int ACE = 1, JACK = 11, QUEEN = 12, KING = 13;

        //Assigns codes for the different Suit Colors
        static const int BLACK = 0, RED = 1;

        //The suit of the card
        int suit;

        //The rank of the card, from 1 to 13
        int rank;

        //The color of the card
        int color;

        //Whether or not the card is visible on the board
        bool isVisible;

        /**
         * The default constructor for a Card
         * @param theRank
         * @param theSuit
         */
        Card(int theRank, int theSuit);

        /**
         * gets the suit of the card
         * @return the int that corresponds to this card's suit.
         */
        int getSuit();

        /**
         * gets the rank of the card
         * @return int that corresponds to this card's Rank.
         */
        int getRank();

        /**
         * gets the color of the card
         * @return int that corresponds to this card's Color.
         */
        int getColor();

        /**
         * gets the color of the card
         * @return string that corresponds to this card's color.
         */
        string getColorAsString();

        /**
         * gets the color of the card
         * @return string that corresponds to this card's Suit.
         */
        string getSuitAsString();

        /**
         * gets the color of the card
         * @return string that corresponds to this card's Rank.
         */
        string getRankAsString();

        /**
         * Override for the toString method. It prints out the suit as rank
         * of suit
         */
        string toString();

        /**
         * gets the visibility of the card
         * @return boolean that corresponds to whether the card is visible or not.
         */
        bool getVisibility();

        /**
         * Makes the card visible on the game board
         */
        void makeVisible();

        /**
         * Makes the card invisible on the game board
         */
        void makeInvisible();

        /**
         * This method is used to compare the ranks of the cards. It returns 1
         * if the rank of this card is greater than the parameter, -1 if the rank
         * of this card is less than the parameter, and 0 otherwise.
         * @param c
         * @return
         */
        int compareRank(Card c);

        /**
         * This method is used to compare the suits. It returns 0 if the suits are the
         * same, 1 if the suits are both the same color, and -1 if the color of the
         * suits do not match
         * @param c
         * @return
         */
        int compareSuit(Card c);
};

#endif //SOLITAIRE_CARD_H
