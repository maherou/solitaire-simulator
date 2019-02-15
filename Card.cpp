/**
 * This class is the class that is responsible for creating
 * the card object.
 * 
 * @author jsupton
 */
public class Card {

	//Ranks the different Suits and assigns a name to the corresponding number
    public final static int HEARTS = 0, SPADES = 1, DIAMONDS = 2, CLUBS = 3;
    
    //Assigns a name to the corresponding numerical value, for cards that are not numeric
    public final static int ACE = 1, JACK = 11, QUEEN = 12, KING = 13;
    
    //Assigns codes for the different Suit Colors
    public final static int BLACK = 0, RED = 1;
    
    //The suit of the card 
    private final int suit;   
    
    //The rank of the card, from 1 to 13
    private final int rank;
    
    //The color of the card
    private int color; 
    
    //Whether or not the card is visible on the board
    private boolean isVisible;
       
    /**
     * The default constructor for a Card
     * @param theRank
     * @param theSuit
     */
    public Card(int theRank, int theSuit) {
        rank = theRank;
        suit = theSuit;
        switch ( suit ) {
        	case SPADES:   color = BLACK;
        	case HEARTS:   color = RED;
        	case DIAMONDS: color = RED;
        	case CLUBS:    color = BLACK;
        }
        isVisible = false;
    }
       
    /**
     * gets the suit of the card
     * @return the int that corresponds to this card's suit.
     */
    public int getSuit() {
        return suit;
    }
    
    /**
     * gets the rank of the card
     * @return int that corresponds to this card's Rank.
     */
    public int getRank() {
        return rank;
    }
    
    /**
     * gets the color of the card
     * @return int that corresponds to this card's Color.
     */
    public int getColor() {
    	return color;
    }
    
    /**
     * gets the color of the card
     * @return string that corresponds to this card's color.
     */
    public String getColorAsString() {
    	switch ( suit ) {
        case SPADES:   return "B";
        case HEARTS:   return "R";
        case DIAMONDS: return "R";
        case CLUBS:    return "B";
        default:       return "??";
     }
    }
    
    /**
     * gets the color of the card
     * @return string that corresponds to this card's Suit.
     */
    public String getSuitAsString() {
            // Return a String representing the card's suit.
            // (If the card's suit is invalid, "??" is returned.)
        switch ( suit ) {
           case SPADES:   return "S";
           case HEARTS:   return "H";
           case DIAMONDS: return "D";
           case CLUBS:    return "C";
           default:       return "??";
        }
    }
    
    /**
     * gets the color of the card
     * @return string that corresponds to this card's Rank.
     */
    public String getRankAsString() {
            // Return a String representing the card's Rank.
            // If the card's Rank is invalid, "??" is returned.
        switch ( rank ) {
           case 1:   return "A";
           case 2:   return "2";
           case 3:   return "3";
           case 4:   return "4";
           case 5:   return "5";
           case 6:   return "6";
           case 7:   return "7";
           case 8:   return "8";
           case 9:   return "9";
           case 10:  return "10";
           case 11:  return "J";
           case 12:  return "Q";
           case 13:  return "K";
           default:  return "??";
        }
    }
    
    /**
     * Override for the toString method. It prints out the suit as rank
     * of suit
     */
    public String toString() {
           // Return a String representation of this card, such as
           // "10 of Hearts" or "Queen of Spades".
        return getRankAsString() + " of " + getSuitAsString();
    }

    /**
     * gets the visibility of the card
     * @return boolean that corresponds to whether the card is visible or not.
     */
    public boolean getVisibility() {
    	return isVisible;
    }
    
    /**
     * Makes the card visible on the game board
     */
    public void makeVisible() {
    	isVisible = true;
    }
    
    /**
     * Makes the card invisible on the game board
     */
    public void makeInvisible() {
    	isVisible = false;
    }
    
    /**
     * This method is used to compare the ranks of the cards. It returns 1
     * if the rank of this card is greater than the parameter, -1 if the rank
     * of this card is less than the parameter, and 0 otherwise.
     * @param c
     * @return
     */
    public int compareRank(Card c) {
    	if(this.getRank()-1 == c.getRank())
    		return 1;
    	else if(this.getRank()+1 == c.getRank())
    		return -1;
    	else 
    		return 0;
    }
    
    /**
     * This method is used to compare the suits. It returns 0 if the suits are the
     * same, 1 if the suits are both the same color, and -1 if the color of the
     * suits do not match
     * @param c
     * @return
     */
    public int compareSuit(Card c) {
    	if(this.getSuit()==c.getSuit())
    		return 0;
    	else if(Math.floorMod(this.getSuit(),2) == Math.floorMod(c.getSuit(),2))
    		return 1;
    	else 
    		return -1;
    }

}