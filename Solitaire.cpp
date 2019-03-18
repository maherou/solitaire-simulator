#include "Solitaire.h"
#include "Card.h"
#include "Deck.h"
#include "Gameboard.h"

    /**
     * This class is the main solitaire game class. It uses the classes Deck, Card, and Tableau to
     * execute a solitaire simulation game.
     * @author Colin Tate from Jacob's Solitaire.java
     * @version February 17 2019
     */
    Solitaire::Solitaire(int type) {
        Deck d = Deck();
        vector<Card> *deck = d.getDeck();

        double overall_Count = 0;
        double overall_Probability = 0;
        double overall_Time = 0;
        double overall_NumberOfMoves = 0;
        vector<double> *probabilities = new vector<double>();
        vector<double> *execution = new vector<double>();
        int NumberOfSimulations = 5;
        int NumberOfGames = 100;

        //Repsonsible for looping through and doing a specified number of rounds
        for(int j = 0; j<NumberOfSimulations;j++) {

            double i = 0;
            double counter = 0;
            double seconds = 0;
            double numberOfMoves = 0;

            //Responsible for looping through the number Of games
            while (i < NumberOfGames) {

                //Starts the clock to measure run time of a game
                time_t begin = clock();
                srand(time(0));

                // Check type - normal / win / loss
                if (type == 0)
                    d.shuffle();
                else if (type == 1)
                    d.shuffle_WIN2();
                else if (type == 2)
                    d.shuffle_LOSE();

                //Creates a new deck and gameboard
                deck = d.getDeck();
                GameBoard t = GameBoard(d);
                GameBoard temp = t;

                double numMoves = 0;

                //A loop that executes the solitaire game
                while (*t.getStockCounter() < 3) {
                    bool tab = true;
                    bool stock = false;
                    while (tab) {
                        tab = checkTableau(&t);
                        //t.printGameBoard();
                        if(tab)
                            numMoves++;
                    }
                    while (!stock) {
                        stock = checkStock(&t);
                        if(stock)
                            numMoves++;
                        //t.printGameBoard();
                    }
                }

                //If all of the cards are in the destination piles YOU WIN
                vector<vector<Card>> *destination = t.getDestination();
                if (destination->at(0).size() == 13 && destination->at(1).size() == 13 &&
                    destination->at(2).size() == 13 && destination->at(3).size() == 13) {
                    //cout << "YOU WIN" << endl;
                    //temp.printGameBoard();
                    //t.printGameBoard();
                    counter++;
                    numberOfMoves+=numMoves;
                }
                //else
                  //cout << "YOU LOSE" << endl;

                  // Computes runtime for the game
                time_t end = clock();
                seconds = seconds + (double) (end - begin) / CLOCKS_PER_SEC;

                i++;

            }
            //Prints out the information for the particular round
            cout << "\n--------------------------------------------------------------------------------------------------------------------------------------------------------";
            cout << "\nGAME: " << j +1 ;
            cout << "\nWINS: " << counter;
            cout << "\nPROBABILITY: " << counter / i << " (" << (counter / i) * 100 << "%)";
            cout << "\nAVERAGE NUMBER OF MOVES: " << numberOfMoves / i;
            cout << "\nAVERAGE EXECUTION TIME PER SIMULATION: " << seconds / i << " seconds";

            probabilities->push_back(counter/i);
            execution->push_back(seconds/i);

            overall_Count += counter;
            overall_Probability += counter / i;
            overall_Time += seconds / i;
            overall_NumberOfMoves+= numberOfMoves / i;
        }

        //Prints out the stats for the overall games
        cout << "\n********************************************************************************************************************************************************";
        cout << "\nOVERALL";
        cout << "\nAVERAGE WINS: " << (int) overall_Count/NumberOfSimulations << " out of " << NumberOfGames;
        cout << "\nAVERAGE (Mean) PROBABILITY: " << overall_Probability/NumberOfSimulations << " (" << (overall_Probability/NumberOfSimulations)*100 << "%)";
        cout << "\nAVERAGE (Mean) NUMBER OF MOVES: " << overall_NumberOfMoves/NumberOfSimulations;
        cout << "\nAVERAGE (Mean) EXECUTION TIME PER SIMULATION: " << overall_Time/NumberOfSimulations << " seconds";

        double prob_sd = 0;
        double ex_sd = 0;
        for(int j = 0;j<probabilities->size();j++){
            prob_sd += pow(probabilities->at(j)-(overall_Probability/NumberOfSimulations),2);
            ex_sd += pow(execution->at(j)-(overall_Time/NumberOfSimulations),2);
        }

        prob_sd = sqrt(prob_sd/NumberOfSimulations);
        ex_sd = sqrt(ex_sd/NumberOfSimulations);

        cout << "\nSTANDARD DEVIATION PROBABILITY: " << prob_sd;
        cout << "\nSTANDARD DEVIATION EXECUTION TIME PER SIMULATION: " << ex_sd;
        cout << "\n********************************************************************************************************************************************************";
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
    bool Solitaire::checkStock(GameBoard *t) {
        vector<vector<Card>> *board = t->getTableau();
        vector<Card> *stock = t->getStock();
        vector<Card> *discard = t->getDiscard();
        vector<vector<Card>> *destination = t->getDestination();

        //If the stock is not empty:
        if (!stock->empty()) {
            Card compC = stock->at(0);
            compC.makeVisible();

            //Check to see if the stock card can be placed in any of the 4 destination piles
            for (int j = 0; j < 4; j++) {
                vector<Card> &dest = destination->at(j);
                if (!dest.empty()) {
                    Card card = dest.at(dest.size()-1);
                    bool b = t->validDestinationMove(compC, card);
                    //If it is a valid move, move the stock card, and flip a new stock card over
                    if (b) {
                        stockMoveCard(stock,&dest,&compC,t);
                        return true;
                    }
                }

                    //If the stock card is an Ace, it can be automatically placed in one of the empty destination piles
                else if (compC.getRank() == 1) {
                    stockMoveCard(stock,&dest,&compC,t);
                    return true;
                }
            }

            //Check if it can be placed on any of the bottom columns
            for (int i = 0; i < 7; i++) {
                vector<Card> &col = board->at(i);
                if (!col.empty()) {
                    Card c = col.at(col.size()-1);
                    if (c.getVisibility()) {
                        bool b = t->validTableauMove(compC, c);
                        if (b) {
                            //If it is a valid move, move the stock card, and flip a new stock card over
                            stockMoveCard(stock,&col,&compC,t);
                            return true;
                        }
                    }
                }
                    //If the tableau column is empty, then the stock card can be placed in the empty column
                else {
                    stockMoveCard(stock,&col,&compC,t);
                    return true;
                }
            }

            //If the card couldn't be placed, remove the card from the stock and put it into the Discard Pile
            compC.makeInvisible();
            discard->push_back(compC);
            stock->erase(stock->begin());

            //If the stock isn't empty, flip over a new card
            if (!stock->empty()) {
                stock->at(0).makeVisible();
                return false;
            }
                //If the stock is empty, the counter is incremented, and the discard pile become the stock again
            else {
                //cout << "COUNTER INCREMENTED" << endl;
                t->incrementStockCounter();
                t->swapStockAndDiscard();
                if (*t->getStockCounter() < 3)
                    return false;
                else
                    return true;
            }
        }

            //If the stock is empty, the counter is incremented, and the discard pile become the stock again
        else if (*t->getStockCounter() < 3) {
            //cout << "COUNTER INCREMENTED" << endl;
            t->incrementStockCounter();
            t->swapStockAndDiscard();
            return false;
        } else
            return true;
    }

    /**
     *This method is responsible for simply moving a stoack card to the new pile it belongs on
     * @param stock
     * @param dest
     * @param compC
     * @param t
     */
    void Solitaire::stockMoveCard(vector<Card> *stock, vector<Card> *dest,Card *compC, GameBoard *t){
        stock->erase(stock->begin());
        dest->push_back(*compC);
        if (!stock->empty())
            stock->at(0).makeVisible();
    }

    /**
     * This method is used for checking the tableau. First, it checks to see if any of the cards on the tableau can be moved
     * to a destination pile. It then checks to see if any of the cards on the tableau can be moved to another spot on the tableau
     * @param t the tableau object for the game
     * @return returning true means that a card on the tableau was either moved to a destination pile, or moved to another spot on the
     * tableau. Either way, the main loop above continues, and the tableau is rechecked for new possible moves. Returning false means
     * that there were no valid moves on the tableau.
     */
    bool Solitaire::checkTableau(GameBoard *t) {
        vector<vector<Card>> *board = t->getTableau();
        vector<vector<Card>> *destination = t->getDestination();

        //Checks if any of the cards below can be moved to the Top
        for (int i = 0; i < 7; i++) {
            //gets a column of the tableau
            vector<Card> &col = board->at(i);
            if (!col.empty()) {
                //each ending card in each column is checked to see if it can be moved above
                Card colCard = col.at(col.size() - 1);
                for (int j = 0; j < 4; j++) {
                    vector<Card> &dest = destination->at(j);
                    if (colCard.getVisibility()) {
                        if (!dest.empty()) {
                            Card destCard = dest.at(dest.size() - 1);
                            bool b = t->validDestinationMove(colCard, destCard);
                            if (b) {
                                dest.push_back(col.at(col.size() - 1));
                                col.erase(col.begin() + col.size() - 1);
                                if (!col.empty())
                                    col.at(col.size() - 1).makeVisible();
                                return true;
                            }
                        } else if (colCard.getRank() == 1) {
                            col.erase(col.begin() + col.size() - 1);
                            dest.push_back(colCard);
                            if (!col.empty())
                                col.at(col.size() - 1).makeVisible();
                            return true;
                        }
                    }
                }
            }
        }

        //Check if any of the bottom cards can be moved to eachother
        for (int i = 0; i < 6; i++) {
            //gets a column of the tableau
            vector<Card> &col = board->at(i);
            if (!col.empty()) {
                for (int k = 0; k < col.size(); k++) {
                    //Checks each card in that column of the tableau
                    Card colCard = col.at(k);
                    if (colCard.getVisibility()) {
                        for (int j = i + 1; j < 7; j++) {
                            //gets a different column of the tableau
                            vector<Card> &dest = board->at(j);
                            if (!dest.empty()) {
                                for (int m = 0; m < dest.size(); m++) {
                                    //checks each card in that other column of the tableau
                                    Card destCard = dest.at(m);
                                    if (destCard.getVisibility()) {
                                        //Checks both ways to see if either move is valid
                                        bool a = t->validTableauMove(colCard, destCard);
                                        bool b = t->validTableauMove(destCard, colCard);

                                        //I chose to only allow cards to swap, if this card is not part of a run already
                                        //for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
                                        if (a && m == (dest.size() - 1) &&
                                            (k == 0 || !(col.at(k - 1).getVisibility()))) {
                                            int size = col.size();
                                            for (int n = k; n < size; n++) {
                                                dest.push_back(col.at(k));
                                                col.erase(col.begin() + k);
                                            }
                                            if (!col.empty())
                                                col.at(col.size() - 1).makeVisible();
                                            return true;
                                        }
                                            //I chose to only allow cards to swap, if this card is not part of a run already
                                            //for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
                                        else if (b && k == (col.size() - 1) &&
                                                 (m == 0 || !(dest.at(m - 1).getVisibility()))) {
                                            int size = dest.size();
                                            for (int n = m; n < size; n++) {
                                                col.push_back(dest.at(m));
                                                dest.erase(dest.begin() + m);
                                            }
                                            if (!dest.empty())
                                                dest.at(dest.size() - 1).makeVisible();
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

        //If no cards can be moved onto one another, this loop checks to see if there are any empty rows
        //and if there are, it moves a stack onto an empty row to reveal a non-visible card
        for (int i = 0; i < 7; i++) {
            //gets a column of the tableau
            vector<Card> &emptyCol = board->at(i);
            //If the row is empty, we want to then move a visible stack of cards to this to turn over a non-visble card
            if (emptyCol.empty()) {

                for (int j = 0; j < 7; j++) {
                    vector<Card> &col = board->at(j);

                    //Find the first row that contains cards in it
                    if (!col.empty()) {
                        if(!col.at(0).getVisibility()) {

                            for (int m = 0; m < col.size(); m++) {
                                Card destCard = col.at(m);
                                if (destCard.getVisibility()) {
                                    int size = col.size();
                                    for (int n = m; n < size; n++) {
                                        emptyCol.push_back(col.at(m));
                                        col.erase(col.begin() + m);
                                    }
                                    col.at(col.size() - 1).makeVisible();
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }

        return false;
    }

    /**
     * Main method for creating a new Solitaire object and running the game
     * @param argc int number of arguments
     * @param argv argument variable
     */
    int main(int argc, char** argv) {
        int i = 0;
        cout << "What type of game would you like to play?\n  0 - Normal\n  1 - Guaranteed Win\n  2 - Guaranteed Loss" << endl;
        cin >> i;
        if (i == 0 || i == 1 || i == 2)
            Solitaire s = Solitaire(i);
        else
            return 1;
        return 0;
    }
