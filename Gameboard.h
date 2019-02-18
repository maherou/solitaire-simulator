//
// Created by Michael Carroll on 2019-02-17.
//

#ifndef SOLITAIRE_GAMEBOARD_H
#define SOLITAIRE_GAMEBOARD_H

#include <vector>
#include <time.h>
#include <random>

class Card;

using namespace std;

/**
 * The GameBoard class, that is responsible for housing the tableau, destination piles,
 * and stock pile.
 *
 * @author Michael Carroll
 * @version February 16 2019
 */
class GameBoard {

public:

    //A Tableau object, consisting of a vector of vectors of cards
    vector<vector<Card>> tableau;

    //The stock pile for the solitaire game
    vector<Card> stock;

    //The discard pile for the game
    vector<Card> discard;

    //The destination piles for the game, consisting of a vector of vector of cards
    vector<vector<Card>> destination;

    //
    int stockCounter;

    /**
     * Default constructor for the game board. It creates the 7 column tableau and puts cards in it, sets the
     * stock counter to 0, creates a 4 column destination pile array List, and builds the stock pile
     * with the remaining cards not in the tableau
     * @param deck
     */
    GameBoard(Deck deck);

    /**
     * This method is used to print out the game board in a visually appealing way
     */
    void printGameBoard();

    /**
     * Used to return the current tableau
     * @return vector<vector<Card>> representing the tableau
     */
    vector<vector<Card>>* getTableau();

    /**
     * Used to return the current destination piles
     * @return vector<vector<Card>> representing the destination piles
     */
    vector<vector<Card>>* getDestination();

    /**
     * Used to return the current discard pile
     * @return vector<Card> representing the discard pile
     */
    vector<Card>* getDiscard();

    /**
     * Used to return the current stock pile
     * @return <vector<Card> representing the stock pile
     */
    vector<Card>* getStock();

    /**
     * Used to return the current stock counter
     * @return integer representing the stock counter
     */
    int* getStockCounter();

    /**
     * Used to increment the stock counter. This happens when all the cards in the stock
     * have been seen again.
     */
    void incrementStockCounter();

    /**
     * Used to swap the discard and stock piles, this happens when the stock counter is incremented.
     * All the cards that we have already seen (in the discard pile) are put back into the stock pile
     */
    void swapStockAndDiscard();

    /**
     * This method determines whether or not this move is valid on the Tableau
     * (the bottom 7 columns)
     * This value is greater than the parameter value. Meaning that we can
     * place this new card below of the parameter value
     * @param c
     * @return
     */
    bool validTableauMove(Card c1, Card c2);

    /**
     * This method determines whether or not this move is valid on the destination
     * piles (the 4 piles on top)
     * This value is greater than the parameter value. Meaning that we can
     * place this new card ontop of the parameter value
     * @param c
     * @return
     */
    bool validDestinationMove(Card c1, Card c2);
};

#endif //SOLITAIRE_GAMEBOARD_H
