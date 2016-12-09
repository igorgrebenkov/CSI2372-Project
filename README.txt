Unfortunately, I did not have much time to properly implement the save game function.

My current implementation works fine, but it deviates from the expected
implementation as requested in the project description.

The changes I've made in my implementation are:
- the Deck istream constructor is not used
  - instead, the deck is initialized from the input stream in the Table constructor
  - this was done, because I was having circular dependency issues with Deck & CardFactory
    - To have a Deck object in CardFactory, I need to include "Deck.h"
    - To be able to use getDeck() method with Deck(istream& is, const CardFactory* cf) constructor
      requires inclusion of "CardFactory.h" in Deck 
    - Therefore, Deck includes CardFactory, and CardFactory includes Deck, which creates a circular
      dependency
    - Since I did not have enough time to figure this out, I went with my alternate approach 
      of initializing the deck through the Table constructor

- the Chain istream constructor is not used
  - player chain information is loaded to file via ostream using the player's overloaded << operator,
    along with all other game state data
  - in the Table istream constructor, the file is read via the istream, and it is chopped up into 
    individual strings representing player information, deck data, discard pile data, and trade area data.
  - these strings are then passed to the various object istream constructors via istringstreams
  - hence, to use the Chain istream constructor to reconstruct saved Chains, the player information would
    have to be chopped up even further to get a string that possesses only Chain data
  - this seemed a bit convoluted since Chains are managed in Player, and since I was pressed for time,   
    this is what I did (i.e., Chains are reconstructed in the Player istream constructor)

Finally, I'm not sure if there was a better way to do this, but when reconstructing things like the deck,
discard pile, etc., to obtain cards to add to those objects, I create a temporary deck that I can iterate
through to fetch cards of a given type. 

For example, if I need to add a Quartz card to the discardArea, I fetch a deck with Deck tmp = cf->getDeck()
and then iterate through them until I find a Quartz card, which I then add to the discard area. 

Since the CardFactory createCard method is private, I could not think of any other way to do this, since 
cards are only obtainable through the getDeck() method. 