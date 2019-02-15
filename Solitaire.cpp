/**
 * This class is the main solitaire game class. It uses the classes Deck, Card, and Tableau to
 * execute a solitaire simulation game.
 */
public class Solitaire {

	/**
	 * Main method for creating a new Solitaire object and running the game
	 * @param args
	 */
    public static void main(String[] args) {
	    return EXIT_FAILURE;
    }

    /**
     * Solitaire constructor. Consists of creating a new
     * deck of cards, then shuffling those cards, and then
     * executing a the solitaire game.
     */
    public Solitaire() {
	    return EXIT_FAILURE;
    }
    
    /**
     * This method is used for checking the stock pile. First, it checks to see if the card on the stock 
     * pile can be moved to a destination pile. It then checks to see if it can be moved to somewhere on
     * the tableau.
     * @param t the tableau object for the game
     * @return returning false will cause the while loop above to loop again. This means, if a stock
     * card was placed in a destination pile, it loops again, since nothing was placed on the bottom
     * tableau, so that doesn't need to be checked again for moves. Returning true means a stock card
     * was placed on the tableau, which will cause the loop to stop since we now need to look over the 
     * tableau and see if we can do any moves down there
     */
    public boolean checkStock(GameBoard t) {
	    return FALSE;
    }
   
    
    /**
     * This method is used for checking the tableau. First, it checks to see if any of the cards on the tableau can be moved
     * to a destination pile. It then checks to see if any of the cards on the tableau can be moved to another spot on the tableau
     * @param t the tableau object for the game
     * @return returning true means that a card on the tableau was either moved to a destination pile, or moved to another spot on the
     * tableau. Either way, the main loop above continues, and the tableau is rechecked for new possible moves. Returning false means 
     * that there were no valid moves on the tableau.
     */
    public boolean checkTableau(GameBoard t) {
	    return FALSE;
    }
}
