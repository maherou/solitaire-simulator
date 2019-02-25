/**
* Header for Solitaire class. Complete will all methods and include.
* @author Wilmot Osei-Bonsu
* @version Febuary 24, 2019
*/

#ifndef SOLITAIRE_MAIN_GAME
#define SOLITAIRE_MAIN_GAME

#include <list>
#include <vector>
#include <random>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>


using namespace std;
class Card;
class GameBoard;
class Deck;

class Solitaire {

	/**
	* Solitaire constructor. Consists of creating a new
	* deck of cards, then shuffling those cards, and then
	* executing a the solitaire game.
	* @return A solitaire game object to be played
	*/
public:

	Solitaire(int type);

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
	bool checkStock(GameBoard *t);

	/**
	*This method is responsible for simply moving a stoack card to the new pile it belongs on
	* @param stock
	* @param dest
	* @param compC
	* @param t
	*/
	void stockMoveCard(vector<Card> *stock, vector<Card> *dest, Card *compC, GameBoard *t);

	/**
	* This method is used for checking the tableau. First, it checks to see if any of the cards on the tableau can be moved
	* to a destination pile. It then checks to see if any of the cards on the tableau can be moved to another spot on the tableau
	* @param t the tableau object for the game
	* @return returning true means that a card on the tableau was either moved to a destination pile, or moved to another spot on the
	* tableau. Either way, the main loop above continues, and the tableau is rechecked for new possible moves. Returning false means
	* that there were no valid moves on the tableau.
	*/
	bool checkTableau(GameBoard *t);
};

void wait(int e);

#endif