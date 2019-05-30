#include "Card.h"
#include "Deck.h"
#include "Gameboard.h"

/**
 * The GameBoard class, that is responsible for housing the tableau, destination piles,
 * and stock pile.
 *
 * @author jsupton
 * @author Michael Carroll
 * @version February 16 2019
 */

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
    GameBoard::GameBoard(Deck deck) {
        vector<Card> col1;
        vector<Card> col2;
        vector<Card> col3;
        vector<Card> col4;
        vector<Card> col5;
        vector<Card> col6;
        vector<Card> col7;

        stockCounter = 0;

        vector<Card> dest1;
        vector<Card> dest2;
        vector<Card> dest3;
        vector<Card> dest4;
        destination.push_back(dest1);
        destination.push_back(dest2);
        destination.push_back(dest3);
        destination.push_back(dest4);

        int colCounter = 0;
        int deckCounter = 0;
        vector<Card> *d = deck.getDeck();

        //Adds cards to the tableau
        for(int i = 1; i <= 7; i++) {
            for(int j = 0; j < i; j++) {
                int col = fmod(colCounter, 7);
                Card c = d->at(deckCounter);
                if(j+1 == i)
                    c.makeVisible();
                switch(col) {
                    case 0 :
                        col1.push_back(c);
                        break; // break is optional
                    case 1 :
                        col2.push_back(c);
                        break; // break is optional
                    case 2 :
                        col3.push_back(c);
                        break; // break is optional
                    case 3 :
                        col4.push_back(c);
                        break; // break is optional
                    case 4 :
                        col5.push_back(c);
                        break; // break is optional
                    case 5 :
                        col6.push_back(c);
                        break; // break is optional
                    case 6 :
                        col7.push_back(c);
                        break; // break is optional
                }
                deckCounter++;
            }
            colCounter++;
        }

        //Adds the remaining cards to the stock pile
        for(int k = deckCounter; k< d->size(); k++) {
            stock.push_back(d->at(k));
        }
        stock.at(0).makeVisible();

        tableau.push_back(col1);
        tableau.push_back(col2);
        tableau.push_back(col3);
        tableau.push_back(col4);
        tableau.push_back(col5);
        tableau.push_back(col6);
        tableau.push_back(col7);

        //printGameBoard();
    }

    /**
     * This method is used to print out the game board in a visually appealing way
     */
    void GameBoard::printGameBoard() {
        for(auto t: tableau) {
            for(auto c: t) {
                if(c.getVisibility())
                    cout << "[" << c.getRankAsString() << "" << c.getSuitAsString().at(0) << "] ";
                else
                    cout << " " << c.getRankAsString() << "" << c.getSuitAsString().at(0) << " ";
            }
            cout << '\n';
        }
        cout << '\n';
        cout << "STOCK:  ";
        for(auto c: stock) {
            if(c.getVisibility())
                cout << "[" << c.getRankAsString() << "" << c.getSuitAsString().at(0) << "] ";
            else
                cout << " " << c.getRankAsString() << "" << c.getSuitAsString().at(0) << " ";
        }
        cout << '\n';
        cout << "DESINTATIONS:  \n";
        for(vector<Card> t: destination) {
            for(Card c: t) {
                if(c.getVisibility())
                    cout << "[" << c.getRankAsString() << "" << c.getSuitAsString().at(0) << "] ";
                else
                    cout << " " << c.getRankAsString() << "" << c.getSuitAsString().at(0) << " ";
            }
            cout << '\n';
        }
        cout << '\n';
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------";
        cout << '\n';
    }

    /**
     * Used to return the current tableau
     * @return vector<vector<Card>> representing the tableau
     */
    vector<vector<Card>>* GameBoard::getTableau(){
        return &this ->tableau;
    }

    /**
     * Used to return the current destination piles
     * @return vector<vector<Card>> representing the destination piles
     */
    vector<vector<Card>>* GameBoard::getDestination(){
        return &this ->destination;
    }

    /**
     * Used to return the current discard pile
     * @return vector<Card> representing the discard pile
     */
    vector<Card> * GameBoard::getDiscard(){
        return &this ->discard;
    }

    /**
     * Used to return the current stock pile
     * @return <vector<Card> representing the stock pile
     */
    vector<Card> * GameBoard::getStock(){
        return &this ->stock;
    }

    /**
     * Used to return the current stock counter
     * @return integer representing the stock counter
     */
    int* GameBoard::getStockCounter(){
        return &this ->stockCounter;
    }

    /**
     * Used to increment the stock counter. This happens when all the cards in the stock
     * have been seen again.
     */
    void GameBoard::incrementStockCounter(){
        stockCounter += 1;
    }

    /**
     * Used to swap the discard and stock piles, this happens when the stock counter is incremented.
     * All the cards that we have already seen (in the discard pile) are put back into the stock pile
     */
    void GameBoard::swapStockAndDiscard(){
        this ->stock = this ->discard;
        this ->discard = vector<Card>();
    }

    /**
     * This method determines whether or not this move is valid on the Tableau
     * (the bottom 7 columns)
     * This value is greater than the parameter value. Meaning that we can
     * place this new card below of the parameter value
     * @param c
     * @return
     */
    bool GameBoard::validTableauMove(Card c1, Card c2) {
        int rank = c1.compareRank(c2);
        int suit = c1.compareSuit(c2);
        if(rank<0 && suit==-1)
            return true;
        return false;
    }

    /**
     * This method determines whether or not this move is valid on the destination
     * piles (the 4 piles on top)
     * This value is greater than the parameter value. Meaning that we can
     * place this new card ontop of the parameter value
     * @param c
     * @return
     */
    bool GameBoard::validDestinationMove(Card c1, Card c2) {
        int rank = c1.compareRank(c2);
        int suit = c1.compareSuit(c2);
        if(rank>0 && suit==0)
            return true;
        return false;
    }
