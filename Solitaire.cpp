import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;
/**
 * This class is the main solitaire game class. It uses the classes Deck, Card, and Tableau to
 * execute a solitaire simulation game.
 * 
 * @author jsupton
 */
public class Solitaire {

	/**
	 * Main method for creating a new Solitaire object and running the game
	 * @param args
	 */
    public static void main(String[] args) {
    	new Solitaire();
    }

    /**
     * Solitaire constructor. Consists of creating a new
     * deck of cards, then shuffling those cards, and then
     * executing a the solitaire game.
     */
    public Solitaire() {
        Deck d = new Deck();
        ArrayList<Card> deck = d.getDeck();
        
        //Randomly shuffles the deck
        System.out.println("SHUFFLED DECK");
        d.shuffle();
        deck = d.getDeck();
        GameBoard t = new GameBoard(d);
        
        //Shuffles the deck for a GUARANTEED WIN
        /*System.out.println("\nSHUFFLED DECK - GUARANTEED TO WIN");
        d.shuffle_WIN();
        deck = d.getDeck();
        GameBoard t = new GameBoard(d);*/

        //Shuffles the deck for a GUARANTEED LOSS
        /*System.out.println("\nSHUFFLED DECK - GUARANTEED TO LOSE");
        d.shuffle_LOSE();
        deck = d.getDeck();
        GameBoard t = new GameBoard(d);*/

        //A loop that executes the solitaire game
        while(t.getStockCounter()<3){
        	boolean tab = true;
        	boolean stock = false;
        	while(tab) 
        	{
        		tab = checkTableau(t);
        	}
        	while(!stock) 
        	{
        		stock = checkStock(t);
        	}
        }
        
        //If all of the cards are in the destination piles YOU WIN
        ArrayList<ArrayList<Card>> destination = t.getDestination();
        if(destination.get(0).size()==13 && destination.get(1).size()==13 && 
        		destination.get(2).size()==13 && destination.get(3).size()==13) {
        	System.out.println("YOU WIN");
        }
        else {
        	System.out.println("YOU LOSE");
        }
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
    	ArrayList<ArrayList<Card>> board = t.getTableau();
        ArrayList<Card> stock = t.getStock();
        ArrayList<Card> discard = t.getDiscard();
        ArrayList<ArrayList<Card>> destination = t.getDestination();
        
        //If the stock is not empty:
        if(!stock.isEmpty()) {
        	Card compC = stock.get(0);
        	compC.makeVisible();
        	
        	//Check to see if the stock card can be placed in any of the 4 destination piles
        	for(int j = 0; j < 4 ; j++) {
    			ArrayList<Card> dest = destination.get(j);
    			if(!dest.isEmpty()) {
    				Card card = dest.get(dest.size()-1);
					boolean b = t.validDestinationMove(compC,card);
					//If it is a valid move, move the stock card, and flip a new stock card over
					if(b) {
						stock.remove(0);
						dest.add(compC);
						if(!stock.isEmpty())
							stock.get(0).makeVisible();
						t.printGameBoard();
						return false;
					}
    			}
    			//If the stock card is an Ace, it can be automatically placed in one of the empty destination piles
    			else if(compC.getRank()==1) {
    				stock.remove(0);
					dest.add(compC);
					if(!stock.isEmpty())
						stock.get(0).makeVisible();
					t.printGameBoard();
					return false;
    			}
        	}
        	
        	//Check if it can be placed on any of the bottom columns
        	for(int i = 0; i < 7;i++) {
    			ArrayList<Card> col = board.get(i);
    			if(!col.isEmpty()) {
	    			Card c = col.get(col.size()-1);
					if(c.getVisibility()==true) {
						boolean b = t.validTableauMove(compC,c);
						if(b) {
							//If it is a valid move, move the stock card, and flip a new stock card over
							stock.remove(0);
							col.add(compC);
							if(!stock.isEmpty())
								stock.get(0).makeVisible();
							t.printGameBoard();
							//
							return true; 
						}
					}
    			}
    			//If the tableau column is empty, then the stock card can be placed in the empty column
    			else {
					stock.remove(0);
					col.add(compC);
					if(!stock.isEmpty())
						stock.get(0).makeVisible();
					t.printGameBoard();
					return true; 
    			}
    		}
        	
        	//If the card couldn't be placed, remove the card from the stock and put it into the Discard Pile
        	compC.makeInvisible();
        	discard.add(compC);
        	stock.remove(0);
        	
        	//If the stock isn't empty, flip over a new card
        	if(!stock.isEmpty()) {
        		stock.get(0).makeVisible();
        		return false;
        	}
        	//If the stock is empty, the counter is incremented, and the discard pile become the stock again
        	else {
        		System.out.println("COUNTER INCREMENTED");
        		t.incrementStockCounter();
        		t.swapStockAndDiscard();
        		if(t.getStockCounter()<3)
        			return false;
        		else
        			return true;
        	}
        }
      //If the stock is empty, the counter is incremented, and the discard pile become the stock again
        else if(t.getStockCounter()<3) {
        	System.out.println("COUNTER INCREMENTED");
        	t.incrementStockCounter();
        	t.swapStockAndDiscard();
        	return false;
        }
        else
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
    public boolean checkTableau(GameBoard t) {
    	ArrayList<ArrayList<Card>> board = t.getTableau();
        ArrayList<ArrayList<Card>> destination = t.getDestination();
        
        //Checks if any of the cards below can be moved to the Top
    	for(int i = 0; i < 7;i++) {
    		//gets a column of the tableau
			ArrayList<Card> col = board.get(i);
			if(!col.isEmpty()) {
				//each ending card in each column is checked to see if it can be moved above
				Card colCard = col.get(col.size()-1);
				for(int j = 0; j < 4; j++) {
					ArrayList<Card> dest = destination.get(j);
					if(colCard.getVisibility()==true) {
						if(!dest.isEmpty()) {
							Card destCard = dest.get(dest.size()-1);
								boolean b = t.validDestinationMove(colCard,destCard);
								if(b) {
									dest.add(col.remove(col.size()-1));
									if(col.size()!=0)
										col.get(col.size()-1).makeVisible();
									t.printGameBoard();
									return true; 
								}
						}
						else if(colCard.getRank()==1) {
							col.remove(col.size()-1);
		    				dest.add(colCard);
		    				if(col.size()!=0)
								col.get(col.size()-1).makeVisible();
		    				t.printGameBoard();
		    				return true;
		    			}
					}
				}
			}
		}
    	
    	//Check if any of the bottom cards can be moved to eachother
    	for(int i = 0; i < 6;i++) {
    		//gets a column of the tableau
			ArrayList<Card> col = board.get(i);
			if(!col.isEmpty()) {
				for(int k = 0;k<col.size();k++) {
					//Checks each card in that column of the tableau
					Card colCard = col.get(k);
					if(colCard.getVisibility()==true) {
						for(int j = i+1; j < 7; j++) {
							//gets a different column of the tableau
							ArrayList<Card> dest = board.get(j);
							if(!dest.isEmpty()) {
								for(int m = 0;m<dest.size();m++) {
									//checks each card in that other column of the tableau
									Card destCard = dest.get(m);
									if(destCard.getVisibility()==true) {
										//Checks both ways to see if either move is valid
										boolean a = t.validTableauMove(colCard,destCard);
										boolean b = t.validTableauMove(destCard,colCard);
										
										//I chose to only allow cards to swap, if this card is not part of a run already
										//for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
										if(m==(dest.size()-1) && k==col.size()-1) {
											if(a && (col.size()==1 || col.get(k-1).getVisibility()==false)) {
												for(int n = k;n<col.size();n++)
													dest.add(col.remove(n));
												if(col.size()!=0)
													col.get(col.size()-1).makeVisible();
												t.printGameBoard();
												return true; 
											}
										   //I chose to only allow cards to swap, if this card is not part of a run already
											//for example a 2 of hearts can be moved to a 3 only if the 2 isn't already on another 3
											else if(b && (dest.size()==1 || dest.get(m-1).getVisibility()==false)) {
												for(int n = m;n<dest.size();n++)
													col.add(dest.remove(n));
												if(dest.size()!=0)
													dest.get(dest.size()-1).makeVisible();
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
}