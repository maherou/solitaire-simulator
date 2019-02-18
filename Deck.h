//
// Created by Michael Carroll on 2019-02-17.
//

#ifndef SOLITAIRE_DECK_H
#define SOLITAIRE_DECK_H

#include <vector>
#include <time.h>
#include <random>

class Card;

using namespace std;

/**
 * An object of type Deck represents an ordinary deck of 52 playing cards.
 * The deck can be shuffled, and cards can be dealt from the deck.
 * @author jsupton
 * @author Wilmot Osei-Bonsu
 * @version Febuary 16 2019
 */
class Deck {
    //access modifier
public:

    // An arrayList of the deck of cards
    vector<Card> deck;

    //A Number of cards for the deck
    int NumberOfCards;

    /**
     * Default constructor. It simply creates a deck of 52 cards
     */
    Deck();

    /**
     * Shuffles the deck using the Fisher-Yates algorithm
     */
    void shuffle();

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will win their solitaire game
     */
    void shuffle_WIN();

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will win their solitaire game
     */
    void shuffle_WIN2();

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will lose their solitaire game
     */
    void shuffle_LOSE();

    /**
     * Gets the deck of cards
     * @return ArrayList<Cards> representing the current deck
     */
    vector<Card> * getDeck();

    /*
    * Generates a normal distribution random number between 0 and 1.
    * @return Random double between 0 and 1.
    */
    double random();
};

#endif //SOLITAIRE_DECK_H
