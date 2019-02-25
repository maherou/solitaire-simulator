#include "Card.h"
#include "Deck.h"
#include "Gameboard.h"

/**
 * This class is the class that is responsible for creating
 * the card object.
 * 
 * @author jsupton
 */

    /**
     * The default constructor for a Card
     * @param theRank
     * @param theSuit
     */
    Card::Card(int theRank, int theSuit) {
        rank = theRank;
        suit = theSuit;
        switch ( suit ) {
            case SPADES:   color = BLACK;
            case HEARTS:   color = RED;
            case DIAMONDS: color = RED;
            case CLUBS:    color = BLACK;
        }
        isVisible = false;
    }

    /**
     * gets the suit of the card
     * @return the int that corresponds to this card's suit.
     */
    int Card::getSuit(){
        return suit;
    }

    /**
     * gets the rank of the card
     * @return int that corresponds to this card's Rank.
     */
    int Card::getRank(){
        return rank;
    }

    /**
     * gets the color of the card
     * @return int that corresponds to this card's Color.
     */
    int Card::getColor(){
        return color;
    }

    /**
     * gets the color of the card
     * @return string that corresponds to this card's color.
     */
    string Card::getColorAsString() {
        switch ( suit ) {
            case SPADES:   return "B";
            case HEARTS:   return "R";
            case DIAMONDS: return "R";
            case CLUBS:    return "B";
            default:       return "??";
        }
    }

    /**
     * gets the color of the card
     * @return string that corresponds to this card's Suit.
     */
    string Card::getSuitAsString() {
        // Return a String representing the card's suit.
        // (If the card's suit is invalid, "??" is returned.)
        switch ( suit ) {
            case SPADES:   return "S";
            case HEARTS:   return "H";
            case DIAMONDS: return "D";
            case CLUBS:    return "C";
            default:       return "??";
        }
    }

    /**
     * gets the color of the card
     * @return string that corresponds to this card's Rank.
     */
    string Card::getRankAsString() {
        // Return a String representing the card's Rank.
        // If the card's Rank is invalid, "??" is returned.
        switch ( rank ) {
            case 1:   return "A";
            case 2:   return "2";
            case 3:   return "3";
            case 4:   return "4";
            case 5:   return "5";
            case 6:   return "6";
            case 7:   return "7";
            case 8:   return "8";
            case 9:   return "9";
            case 10:  return "10";
            case 11:  return "J";
            case 12:  return "Q";
            case 13:  return "K";
            default:  return "??";
        }
    }

    /**
     * Override for the toString method. It prints out the suit as rank
     * of suit
     */
    string Card::toString() {
        // Return a String representation of this card, such as
        // "10 of Hearts" or "Queen of Spades".
        return getRankAsString() + " of " + getSuitAsString();
    }

    /**
     * gets the visibility of the card
     * @return boolean that corresponds to whether the card is visible or not.
     */
    bool Card::getVisibility() {
        return isVisible;
    }

    /**
     * Makes the card visible on the game board
     */
    void Card::makeVisible() {
        isVisible = true;
    }

    /**
     * Makes the card invisible on the game board
     */
    void Card::makeInvisible() {
        isVisible = false;
    }

    /**
     * This method is used to compare the ranks of the cards. It returns 1
     * if the rank of this card is greater than the parameter, -1 if the rank
     * of this card is less than the parameter, and 0 otherwise.
     * @param c
     * @return
     */
    int Card::compareRank(Card c) {
        if(this->getRank()-1 == c.getRank())
            return 1;
        else if(this->getRank()+1 == c.getRank())
            return -1;
        else
            return 0;
    }

    /**
     * This method is used to compare the suits. It returns 0 if the suits are the
     * same, 1 if the suits are both the same color, and -1 if the color of the
     * suits do not match
     * @param c
     * @return
     */
    int Card::compareSuit(Card c) {
        if(this->getSuit()==c.getSuit())
            return 0;
        else if(fmod(this->getSuit(),2) == fmod(c.getSuit(),2))
            return 1;
        else
            return -1;
    }
