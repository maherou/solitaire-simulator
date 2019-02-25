#include "Card.h"
#include "Deck.h"
#include "Gameboard.h"

/**
 * An object of type Deck represents an ordinary deck of 52 playing cards.
 * The deck can be shuffled, and cards can be dealt from the deck.
 * @author jsupton
 * @author Wilmot Osei-Bonsu
 * @version Febuary 16 2019
 */

    // An arrayList of the deck of cards
    vector<Card> deck;

    //A Number of cards for the deck
    int NumberOfCards;

    /**
     * Default constructor. It simply creates a deck of 52 cards
     */
    Deck::Deck() {
        // Create an unshuffled deck of cards.
        deck.clear();
        for (int suit = 0; suit <= 3; suit++) {
            for (int value = 1; value <= 13; value++) {
                deck.push_back(Card(value, suit));
            }
        }
    }

    /**
     * Shuffles the deck using the Fisher-Yates algorithm
     */
    void Deck::shuffle() {
        // Put all the used cards back into the deck, and shuffle it into
        // a random order.

        for (int i = 51; i > 0; i--) {

            int random = rand()%(i+1);

            Card temp = deck[i];
            deck.at(i) = deck[random];
            deck.at(random) = temp;
        }
    }

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will win their solitaire game
     */
    void Deck::shuffle_WIN() {
        deck.clear();
        deck.push_back(Card(1, 0));
        deck.push_back(Card(2, 0));
        deck.push_back(Card(1, 1));
        deck.push_back(Card(4, 0));
        deck.push_back(Card(3, 0));
        deck.push_back(Card(1, 2));
        deck.push_back(Card(5, 0));
        deck.push_back(Card(4, 1));
        deck.push_back(Card(3, 1));
        deck.push_back(Card(1, 3));
        deck.push_back(Card(6, 0));
        deck.push_back(Card(5, 1));
        deck.push_back(Card(4, 2));
        deck.push_back(Card(3, 2));
        deck.push_back(Card(2, 1));
        deck.push_back(Card(7, 0));
        deck.push_back(Card(6, 1));
        deck.push_back(Card(6, 2));
        deck.push_back(Card(5, 2));
        deck.push_back(Card(3, 3));
        deck.push_back(Card(2, 2));
        deck.push_back(Card(7, 1));
        deck.push_back(Card(7, 2));
        deck.push_back(Card(7, 3));
        deck.push_back(Card(6, 3));
        deck.push_back(Card(5, 3));
        deck.push_back(Card(4, 3));
        deck.push_back(Card(2, 3));
        for (int value = 8; value <= 13; value++) {
            for (int suit = 0; suit <= 3; suit++) {
                deck.push_back(Card(value, suit));
            }
        }
    }

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will win their solitaire game
     */
    void Deck::shuffle_WIN2() {
        deck.clear();
        deck.push_back(Card(7, 0));
        deck.push_back(Card(5, 0));
        deck.push_back(Card(6, 1));
        deck.push_back(Card(2, 1));
        deck.push_back(Card(3, 0));
        deck.push_back(Card(4, 1 ));
        deck.push_back(Card(1, 3));
        deck.push_back(Card(1, 2));
        deck.push_back(Card(1, 1));
        deck.push_back(Card(1, 0));
        deck.push_back(Card(7, 1));
        deck.push_back(Card(2, 0));
        deck.push_back(Card(3, 1));
        deck.push_back(Card(4, 0));
        deck.push_back(Card(5, 1));
        deck.push_back(Card(7, 3));
        deck.push_back(Card(2, 2));
        deck.push_back(Card(3, 3));
        deck.push_back(Card(4, 2));
        deck.push_back(Card(5, 3));
        deck.push_back(Card(6, 0));
        deck.push_back(Card(7, 2));
        deck.push_back(Card(6, 3));
        deck.push_back(Card(5, 2));
        deck.push_back(Card(4, 3));
        deck.push_back(Card(3, 2));
        deck.push_back(Card(2, 3));
        deck.push_back(Card(6, 2));
        for (int value = 8; value <= 13; value++) {
            for (int suit = 0; suit <= 3; suit++) {
                deck.push_back(Card(value, suit));
            }
        }
    }

    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the
     * User will lose their solitaire game
     */
    void Deck::shuffle_LOSE() {
        deck.clear();
        deck.push_back(Card(13, 0));
        deck.push_back(Card(8, 0));
        deck.push_back(Card(13, 1));
        deck.push_back(Card(8, 0));
        deck.push_back(Card(8, 0));
        deck.push_back(Card(13, 2));
        deck.push_back(Card(1, 0));
        deck.push_back(Card(12, 1));
        deck.push_back(Card(10, 1));
        deck.push_back(Card(13, 3));
        deck.push_back(Card(1, 0));
        deck.push_back(Card(12, 1));
        deck.push_back(Card(10, 2));
        deck.push_back(Card(9, 2));
        deck.push_back(Card(11, 1));
        deck.push_back(Card(1, 0));
        deck.push_back(Card(12, 1));
        deck.push_back(Card(10, 2));
        deck.push_back(Card(9, 2));
        deck.push_back(Card(8, 3));
        deck.push_back(Card(11, 2));
        deck.push_back(Card(1, 1));
        deck.push_back(Card(12, 2));
        deck.push_back(Card(10, 3));
        deck.push_back(Card(9, 3));
        deck.push_back(Card(9, 3));
        deck.push_back(Card(11, 3));
        deck.push_back(Card(11, 3));
        for (int value = 2; value <= 7; value++) {
            for (int suit = 0; suit <= 3; suit++) {
                deck.push_back(Card(value, suit));
            }
        }
    }

    /**
     * Gets the deck of cards
     * @return ArrayList<Cards> representing the current deck
     */
    vector<Card> * Deck::getDeck() {
        return &this ->deck;
    }

    /*
    * Generates a normal distribution random number between 0 and 1.
    * @return Random double between 0 and 1.
    */
    double Deck::random() {
        mt19937 generator;
        generator.seed(time(0));
        uniform_real_distribution<double> cardRand(0, 1);
        return cardRand(generator);
    }
