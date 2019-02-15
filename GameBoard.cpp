/**
 * 
 */
import java.util.ArrayList;

/**
 * The GameBoard class, that is responsible for housing the tableau, destination piles,
 * and stock pile.
 * 
 * @author jsupton
 *
 */
public class GameBoard {

	//A Tableau object, consisting of an arrayList of arrayLists of cards
	private ArrayList<ArrayList<Card>> tableau = new ArrayList<ArrayList<Card>>();
	
	//The stock pile for the solitaire game
	private ArrayList<Card> stock = new ArrayList<Card>();
	
	//The discard pile for the game
	private ArrayList<Card> discard = new ArrayList<Card>();
	
	//The destination piles for the game
	private ArrayList<ArrayList<Card>> destination = new ArrayList<ArrayList<Card>>();
	
	//
	private Integer stockCounter;
	
	/**
	 * Default constructor for the game board. It creates the 7 column tableau and puts cards in it, sets the 
	 * stock counter to 0, creates a 4 column destination pile array List, and builds the stock pile
	 * with the remaining cards not in the tableau
	 * @param deck
	 */
	public GameBoard(Deck deck) {
		ArrayList<Card> col1 = new ArrayList<Card>();
		ArrayList<Card> col2 = new ArrayList<Card>();
		ArrayList<Card> col3 = new ArrayList<Card>();
		ArrayList<Card> col4 = new ArrayList<Card>();
		ArrayList<Card> col5 = new ArrayList<Card>();
		ArrayList<Card> col6 = new ArrayList<Card>();
		ArrayList<Card> col7 = new ArrayList<Card>();
		
		stockCounter = 0;
		
		destination.add(new ArrayList<Card>());
		destination.add(new ArrayList<Card>());
		destination.add(new ArrayList<Card>());
		destination.add(new ArrayList<Card>());
		
		int colCounter = 0;
		int deckCounter = 0;
		ArrayList<Card> d = deck.getDeck();
		
		//Adds cards to the tableau
		for(int i = 1; i <= 7; i++) {
			for(int j = 0; j < i; j++) {
				int col = Math.floorMod(colCounter, 7);
				Card c = d.get(deckCounter);
				if(j+1 == i)
					c.makeVisible();
				switch(col){
				   case 0 :
				      col1.add(c);
				      break; // break is optional
				   case 1 : 
					  col2.add(c);
					  break; // break is optional
				   case 2 : 
					  col3.add(c);
					  break; // break is optional
				   case 3 :
				      col4.add(c);
				      break; // break is optional
				   case 4 : 
					  col5.add(c);
					  break; // break is optional
				   case 5 : 
					  col6.add(c);
					  break; // break is optional
				   case 6 :
				      col7.add(c);
				      break; // break is optional
				}
				deckCounter++;
			}
			colCounter++;
		}
		
		//Adds the remaining cards to the stock pile
		for(int k = deckCounter; k< d.size();k++) {
			stock.add(d.get(k));
		}
		stock.get(0).makeVisible();
		
		tableau.add(col1);
		tableau.add(col2);
		tableau.add(col3);
		tableau.add(col4);
		tableau.add(col5);
		tableau.add(col6);
		tableau.add(col7);
		
		printGameBoard();
	}
	
	/**
	 * This method is used to print out the game board in a visually appealing way
	 */
	public void printGameBoard() {
		for(ArrayList<Card> t: tableau) {
			for(Card c: t) {
				if(c.getVisibility()==true)
					System.out.print("["+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+"] ");
				else
					System.out.print(" "+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+" ");
			}
			System.out.println();
		}
		System.out.println();
		System.out.print("STOCK:  ");
		for(Card c: stock) {
			if(c.getVisibility()==true)
				System.out.print("["+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+"] ");
			else
				System.out.print(" "+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+" ");
		}
		System.out.println();
		System.out.println("DESTINATIONS:  ");
		for(ArrayList<Card> t: destination) {
			for(Card c: t) {
				if(c.getVisibility()==true)
					System.out.print("["+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+"] ");
				else
					System.out.print(" "+c.getRankAsString()+""+c.getSuitAsString().charAt(0)+" ");
			}
			System.out.println();
		}
		System.out.println();
        System.out.println("\n-------------------------------------------------------------------------------------------------------------");
	}
	
	/**
	 * Used to return the current tableau
	 * @return ArrayList<ArrayList<Card>> representing the tableau
	 */
	public ArrayList<ArrayList<Card>> getTableau(){
		return tableau;
	}
	
	/**
	 * Used to return the current destination piles
	 * @return ArrayList<ArrayList<Card>> representing the destination piles
	 */
	public ArrayList<ArrayList<Card>> getDestination(){
		return destination;
	}
	
	/**
	 * Used to return the current discard pile
	 * @return ArrayList<Card> representing the discard pile
	 */
	public ArrayList<Card> getDiscard(){
		return discard;
	}
	
	/**
	 * Used to return the current stock pile
	 * @return ArrayList<Card> representing the stock pile
	 */
	public ArrayList<Card> getStock(){
		return stock;
	}
	
	/**
	 * Used to return the current stock counter
	 * @return ArrayList<Card> representing the stock counter
	 */
	public Integer getStockCounter(){
		return stockCounter;
	}
	
	/**
	 * Used to increment the stock counter. This happens when all the cards in the stock
	 * have been seen again.
	 */
	public void incrementStockCounter(){
		stockCounter += 1;
	}
	
	/**
	 * Used to swap the discard and stock piles, this happens when the stock counter is incremented.
	 * All the cards that we have already seen (in the discard pile) are put back into the stock pile
	 */
	public void swapStockAndDiscard(){
		this.stock = this.discard;
		this.discard = new ArrayList<Card>();
	}
	
	/**
     * This method determines whether or not this move is valid on the Tableau
     * (the bottom 7 columns)
     * This value is greater than the parameter value. Meaning that we can 
     * place this new card below of the parameter value
     * @param c
     * @return
     */
    public boolean validTableauMove(Card c1, Card c2) {
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
    public boolean validDestinationMove(Card c1, Card c2) {
    	int rank = c1.compareRank(c2);
    	int suit = c1.compareSuit(c2);
    	if(rank>0 && suit==0)
    		return true;
    	return false;
    }
}
