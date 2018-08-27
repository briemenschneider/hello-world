/*
This header file desribes the card deck data construct and the various tools that can be accessed to manipulate the deck.
*/

//DATA STRUCTURES

enum cardsuit {
  SPADE,
  HEART,
  DIAMOND,
  CLUB
};

enum cardvalue {
  ACE = 1, //explicit raw value assigned
  TWO,  //implicit raw value follows suit
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  JACK,
  QUEEN,
  KING
};

//We treat the card as a struct and the deck as a struct
struct card {
  enum cardsuit suit;
  enum cardvalue value;
};

struct deck {
  struct card *cards;  //holds the list of cards in the undealt deck
  struct card *dealt;  //holds the list of dealt cards
  struct card *discard; //holds the discard pile list
  size_t size;
};

struct hand {
  char *owner;
  struct card *cards;
  size_t size;
  unsigned int value; //allows you to calculate and store values for the existing cards
};


//FUNCTIONS

/*
initializeDeck takes an unsigned int and returns a pointer to the deck of cards allocated on the heap.
size describes how many 52-card decks are being put together to form the main deck.
*/  
struct deck *initializeDeck(unsigned int size);

void shuffleDeck(struct deck *deck);

struct hand *dealHand(struct deck *deck, unsigned int numcards);

int discardCards(struct deck *deck, struct hand *hand, struct card **discards);

int dealCards(struct deck *deck, struct hand *hand, int num);

int showHand(struct hand *hand);

//reshuffleDeck shuffles the cards from the discard pile back into the base deck
int reshuffleDeck(struct deck *deck);
