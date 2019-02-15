import java.util.ArrayList;

/**
 * An object of type Deck represents an ordinary deck of 52 playing cards.
 * The deck can be shuffled, and cards can be dealt from the deck.
 * @author jsupton
 *
 */
public class Deck {

	// An arrayList of the deck of cards
    private ArrayList<Card> deck;
    
    //A Number of cards for the deck
    private Integer NumberOfCards;
    
    /**
     * Default constructor. It simply creates a deck of 52 cards
     */
    public Deck() {
           // Create an unshuffled deck of cards.
       deck = new ArrayList<Card>();
       for ( int suit = 0; suit <= 3; suit++ ) {
          for ( int value = 1; value <= 13; value++ ) {
             deck.add(new Card(value,suit));
             }
       }
    }
	
    /**
     * Shuffles the deck using the Fisher-Yates algorithm
     */
    public void shuffle() {
        // Put all the used cards back into the deck, and shuffle it into
        // a random order.
      for ( int i = 51; i > 0; i-- ) {
          int rand = (int)(Math.random()*(i+1));
          Card temp = deck.get(i);
          deck.set(i, deck.get(rand));
          deck.set(rand, temp);
      }
    }
    
    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the 
     * User will win their solitaire game
     */
    public void shuffle_WIN() {
    	deck = new ArrayList<Card>();
    	deck.add(new Card(1,0));
    	deck.add(new Card(2,0));
    	deck.add(new Card(1,1));
    	deck.add(new Card(4,0));
    	deck.add(new Card(3,0));
    	deck.add(new Card(1,2));
    	deck.add(new Card(5,0));
    	deck.add(new Card(4,1));
    	deck.add(new Card(3,1));
    	deck.add(new Card(1,3));
    	deck.add(new Card(6,0));
    	deck.add(new Card(5,1));
    	deck.add(new Card(4,2));
    	deck.add(new Card(3,2));
    	deck.add(new Card(2,1));
    	deck.add(new Card(7,0));
    	deck.add(new Card(6,1));
    	deck.add(new Card(6,2));
    	deck.add(new Card(5,2));
    	deck.add(new Card(3,3));
    	deck.add(new Card(2,2));
    	deck.add(new Card(7,1));
    	deck.add(new Card(7,2));
    	deck.add(new Card(7,3));
    	deck.add(new Card(6,3));
    	deck.add(new Card(5,3));
    	deck.add(new Card(4,3));
    	deck.add(new Card(2,3));
    	for ( int value = 8; value <= 13; value++ ) {
    		for ( int suit = 0; suit <= 3; suit++ ) {
               deck.add(new Card(value,suit));
               }
         }
    }
    
    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the 
     * User will win their solitaire game
     */
    public void shuffle_WIN2() {
    	deck = new ArrayList<Card>();
    		deck.add(new Card(7,0));
    		deck.add(new Card(1,0));
    		deck.add(new Card(6,1));
    		deck.add(new Card(1,1));
    		deck.add(new Card(6,0));
    		deck.add(new Card(5,0));
    		deck.add(new Card(3,2));
    		deck.add(new Card(7,2));
    		deck.add(new Card(5,1));
    		deck.add(new Card(4,1));
    		deck.add(new Card(6,2));
    		deck.add(new Card(2,2));
    		deck.add(new Card(6,3));
    		deck.add(new Card(4,0));
    		deck.add(new Card(3,0));
    		deck.add(new Card(3,3));
    		deck.add(new Card(5,3));
    		deck.add(new Card(1,3));
    		deck.add(new Card(5,2));
    		deck.add(new Card(3,1));
    		deck.add(new Card(2,1));
    		deck.add(new Card(1,2));
    		deck.add(new Card(2,3));
    		deck.add(new Card(4,2));
    		deck.add(new Card(7,3));
    		deck.add(new Card(4,3));
    		deck.add(new Card(2,0));
    		deck.add(new Card(7,1));
    	for ( int value = 8; value <= 13; value++ ) {
    		for ( int suit = 0; suit <= 3; suit++ ) {
               deck.add(new Card(value,suit));
               }
         }
    }
    
    /**
     * Creates a new shuffled deck of cards in an order that guarantees that the 
     * User will lose their solitaire game
     */
    public void shuffle_LOSE() {
    	deck = new ArrayList<Card>();
    	deck.add(new Card(13,0));
    	deck.add(new Card(8,0));
    	deck.add(new Card(13,1));
    	deck.add(new Card(8,0));
    	deck.add(new Card(8,0));
    	deck.add(new Card(13,2));
    	deck.add(new Card(1,0));
    	deck.add(new Card(12,1));
    	deck.add(new Card(10,1));
    	deck.add(new Card(13,3));
    	deck.add(new Card(1,0));
    	deck.add(new Card(12,1));
    	deck.add(new Card(10,2));
    	deck.add(new Card(9,2));
    	deck.add(new Card(11,1));
    	deck.add(new Card(1,0));
    	deck.add(new Card(12,1));
    	deck.add(new Card(10,2));
    	deck.add(new Card(9,2));
    	deck.add(new Card(8,3));
    	deck.add(new Card(11,2));
    	deck.add(new Card(1,1));
    	deck.add(new Card(12,2));
    	deck.add(new Card(10,3));
    	deck.add(new Card(9,3));
    	deck.add(new Card(9,3));
    	deck.add(new Card(11,3));
    	deck.add(new Card(11,3));
        for ( int value = 2; value <= 7; value++ ) {
        	for ( int suit = 0; suit <= 3; suit++ ) {
               deck.add(new Card(value,suit));
               }
         }
    }
    
    /**
     * Gets the deck of cards
     * @return ArrayList<Cards> representing the current deck
     */
    public ArrayList<Card> getDeck() {
		return this.deck;
    }
    

}