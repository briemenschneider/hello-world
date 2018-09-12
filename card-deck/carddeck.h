/*
This header file desribes the card deck data construct and the various tools that can be accessed to manipulate the deck.
*/

//MACROS
#define DECK_SIZE 52
#define NUM_SUITS 4
#define NUM_VALUES 12

//String constants
const char *spade = "Spades\0";
const char *heart = "Hearts\0";
const char *diamond = "Diamonds\0";
const char *club = "Clubs\0";
const char *ace = "Ace\0";
const char *jack = "Jack\0";
const char *queen = "Queen\0";
const char *king = "King\0";


//DATA STRUCTURES

enum cardsuit {
  SPADE,
  HEART,
  DIAMOND,
  CLUB
};

enum cardvalue {
  ACE,
  TWO,
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
  size_t numbase;  //refers to the number in cards
  struct card *dealt;  //holds the list of dealt cards
  size_t numdealt; //refers to the number in dealt
  struct card *discard; //holds the discard pile list
  size_t numdiscard; //refers to the number of discarded
  size_t size; //size of the total deck
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
struct deck *initializeDeck(size_t size);

void shuffleDeck(struct deck *deck);

struct hand *dealHand(struct deck *deck, size_t numcards);

int discardCards(struct deck *deck, struct hand *hand, struct card **discards);

int dealCards(struct deck *deck, struct hand *hand, int num);

int showHand(struct hand *hand);

int showCard(struct card *card);

//reshuffleDeck shuffles the cards from the discard pile back into the base deck
int reshuffleDeck(struct deck *deck);
