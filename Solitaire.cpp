#include <list>
#include <vector>
#include <random>
#include <time.h>

#include "Card.h"
#include "Deck.h"
#include "Gameboard.h"

using namespace std;

/**
 * This class is the main solitaire game class. It uses the classes Deck, Card, and Tableau to
 * execute a solitaire simulation game.
 * @author Colin Tate from Jacob's Solitaire.java
 * @version February 17 2019
 */
class Solitaire {

    /**
     * Solitaire constructor. Consists of creating a new
     * deck of cards, then shuffling those cards, and then
     * executing a the solitaire game.
	 * @return A solitaire game object to be played
     */
public:

Solitaire() {
        Deck d = Deck();
        vector<Card> deck = d.getDeck();

        //Randomly shuffles the deck
        cout << "SHUFFLED DECK " << endl;
        d.shuffle();
        deck = d.getDeck();
        GameBoard t = GameBoard(d);

        //A loop that executes the solitaire game
        while (t.getStockCounter() < 3) {
            bool tab = true;
            bool stock = false;
            while (tab) {
                tab = checkTableau(t);
            }
            while (!stock) {
                stock = checkStock(t);
            }
        }

        //If all of the cards are in the destination piles YOU WIN
        vector<vector<Card>> destination = t.getDestination();
        if (destination.at(0).size() == 13 && destination.at(1).size() == 13 &&
            destination.at(2).size() == 13 && destination.at(3).size() == 13) {
            cout << "YOU WIN" << endl;
        } else
            cout << "YOU LOSE" << endl;
    }

    /**
     * This method is used for checking the stock pile. First, it checks to see if the card on the stock
     * pile can be moved to a destination pile. It then checks to see if it can be moved to somewhere on
     * the tableau.
     * @param t the tableau GameBoard object for the game
     * @return returning false will cause the while loop above to loop again. This means, if a stock
     *		card was placed in a destination pile, it loops again, since nothing was placed on the bottom
     *		tableau, so that doesn't need to be checked again for moves. Returning true means a stock card
     *		was placed on the tableau, which will cause the loop to stop since we now need to look over the
     *		tableau and see if we can do any moves down there
     */
    bool checkStock(GameBoard t) {
        vector<vector<Card>> board = t.getTableau();
        vector<Card> stock = t.getStock();
        vector<Card> discard = t.getDiscard();
        vector<vector<Card>> destination = t.getDestination();

        //If the stock is not empty:
        if (!stock.empty()) {
            Card compC = stock.front();
            compC.makeVisible();

            //Check to see if the stock card can be placed in any of the 4 destination piles
            for (int j = 0; j < 4; j++) {
                vector<Card> dest = destination.at(j);
                if (!dest.empty()) {
                    Card card = dest.back();
                    bool b = t.validDestinationMove(compC, card);
                    //If it is a valid move, move the stock card, and flip a new stock card over
                    if (b) {
                        stock.erase(stock.begin());
                        dest.push_back(compC);
                        if (!stock.empty())
                            stock.front().makeVisible();
                        t.printGameBoard();
                        return false;
                    }
                }

                    //If the stock card is an Ace, it can be automatically placed in one of the empty destination piles
                else if (compC.getRank() == 1) {
                    stock.erase(stock.begin());
                    dest.push_back(compC);
                    if (!stock.empty())
                        stock.front().makeVisible();
                    t.printGameBoard();
                    return false;
                }
            }

            //Check if it can be placed on any of the bottom columns
            for (int i = 0; i < 7; i++) {
                vector<Card> col = board.at(i);
                if (!col.empty()) {
                    Card c = col.back();
                    if (c.getVisibility() == true) {
                        bool b = t.validTableauMove(compC, c);
                        if (b) {
                            //If it is a valid move, move the stock card, and flip a new stock card over
                            stock.erase(stock.begin());
                            col.push_back(compC);

                            if (!stock.empty())
                                stock.front().makeVisible();
                            t.printGameBoard();
                            return true;
                        }
                    }
                }
                    //If the tableau column is empty, then the stock card can be placed in the empty column
                else {
                    stock.erase(stock.begin());
                    col.push_back(compC);
                    if (!stock.empty())
                        stock.front().makeVisible();
                    t.printGameBoard();
                    return true;
                }
            }

            //If the card couldn't be placed, remove the card from the stock and put it into the Discard Pile
            compC.makeInvisible();
            discard.push_back(compC);
            stock.erase(stock.begin());

            //If the stock isn't empty, flip over a new card
            if (!stock.empty()) {
                stock.front().makeVisible();
                return false;
            }
                //If the stock is empty, the counter is incremented, and the discard pile become the stock again
            else {
                cout << "COUNTER INCREMENTED" << endl;
                t.incrementStockCounter();
                t.swapStockAndDiscard();
                if (t.getStockCounter() < 3)
                    return false;
                else
                    return true;
            }
        }

            //If the stock is empty, the counter is incremented, and the discard pile become the stock again
        else if (t.getStockCounter() < 3) {
            cout << "COUNTER INCREMENTED" << endl;
            t.incrementStockCounter();
            t.swapStockAndDiscard();
            return false;
        } else
            return true;
    }


    /**
     * This method is used for checking the tableau. First, it checks to see if any of the cards on the tableau can be moved
     * to a destination pile. It then checks to see if any of the cards on the tableau can be moved to another spot on the tableau
     * @param t the tableau object for the game
     * @return returning true means that a card on the tableau was either moved to a destination pile, or moved to another spot on the
     * tableau. Either way, the main loop above continues, and the tableau is rechecked for new possible moves. Returning false means
     * that there were no valid moves on the tableau.
     */
    bool checkTableau(GameBoard t) {
        vector<vector<Card>> board = t.getTableau();
        vector<vector<Card>> destination = t.getDestination();

        //Checks if any of the cards below can be moved to the Top
        for (int i = 0; i < 7; i++) {
            //gets a column of the tableau
            vector<Card> col = board.at(i);
            if (!col.empty()) {
                //each ending card in each column is checked to see if it can be moved above
                Card colCard = col.back();
                for (int j = 0; j < 4; j++) {
                    vector<Card> dest = destination.at(j);
                    if (colCard.getVisibility() == true) {
                        if (!dest.empty()) {
                            Card destCard = dest.back();
                            bool b = t.validDestinationMove(colCard, destCard);
                            if (b) {
                                dest.push_back(col.back());
                                col.pop_back();
                                if (col.size() != 0)
                                    col.back().makeVisible();
                                t.printGameBoard();
                                return true;
                            }
                        }
                        else if (colCard.getRank() == 1) {
                            col.pop_back();
                            dest.push_back(colCard);
                            if (col.size() != 0)
                                col.back().makeVisible();
                            t.printGameBoard();
                            return true;
                        }
                    }
                }
            }
        }

        //Check if any of the bottom cards can be moved to eachother
        for (int i = 0; i < 6; i++) {
            //gets a column of the tableau
            vector<Card> col = board.at(i);
            if (!col.empty()) {
                for (int k = 0; k < col.size(); k++) {
                    //Checks each card in that column of the tableau
                    Card colCard = col.at(k);
                    if (colCard.getVisibility() == true) {
                        for (int j = i + 1; j < 7; j++) {
                            //gets a different column of the tableau
                            vector<Card> dest = board.at(j);
                            if (!dest.empty()) {
                                for (int m = 0; m < dest.size(); m++) {
                                    //checks each card in that other column of the tableau
                                    Card destCard = dest.at(m);
                                    if (destCard.getVisibility() == true) {
                                        //Checks both ways to see if either move is valid
                                        bool a = t.validTableauMove(colCard, destCard);
                                        bool b = t.validTableauMove(destCard, colCard);

                                        //I chose to only allow cards to swap, if this card is not part of a run already
                                        //for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
                                        if (m == dest.back() && k == col.back()) {
                                            if (a && (col.size() == 1 || col.at(k - 1).getVisibility() == false)) {
                                                for (int n = k; n < col.size(); n++) {
                                                    dest.push_back(col.at(n));
                                                    col.erase(n);
                                                }
                                                if (col.size() != 0)
                                                    col.back().makeVisible();
                                                t.printGameBoard();
                                                return true;
                                            }
                                                //I chose to only allow cards to swap, if this card is not part of a run already
                                                //for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
                                            else if (b && (dest.size() == 1 || dest.at(m - 1).getVisibility() == false)) {
                                                for (int n = m; n < dest.size(); n++) {
                                                    col.push_back(dest.at(n));
                                                    dest.erase(n);
                                                }
                                                if (dest.size() != 0)
                                                    dest.back().makeVisible();
                                                t.printGameBoard();
                                                return true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
};

/**
 * Main method for creating a new Solitaire object and running the game
 * @param argc int number of arguments
 * @param argv argument variable
 */
int main(int argc, char** argv) {
    Solitaire();

    return 0;
}
