#include <carddeck.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct deck *initializeDeck(size_t size) {
  unsigned int i, index;
  enum cardsuit s;
  enum cardvalue v;
  struct deck *deck;

  //Error check
  if (size == 0) {
    fprintf(stderr, "Deck size cannot be zero.\n");
    return NULL;
  }
  
  //initialize the deck and its subordinate arrays
  deck = malloc(sizeof(struct deck));
  (*deck).cards = malloc(size * DECK_SIZE * sizeof(struct card));
  (*deck).numbase = size * DECK_SIZE;
  (*deck).dealt = NULL;
  (*deck).numdealt = 0;
  (*deck).discard = NULL;
  (*deck).numdiscard = 0;
  (*deck).size = size * DECK_SIZE;

  index = 0;
  for (i = 0; i < size; i++) {
    for (s = SPADE; s <= CLUB; s++) {
      for (v = ACE; v <= KING; v++) {
	deck[i].cards[index].suit = s;
	deck[i].cards[index].value = v;
	index++;
      }
    }
  }

  return deck;
}

//only shuffles base deck
void shuffleDeck(struct deck *deck) {
  size_t i, j, k;
  size_t sz = (*deck).numbase;
  struct card cards[sz];
  size_t positionroster[sz];

  //Error check
  if (deck == NULL) {
    fprintf(stderr, "Passed a null pointer as deck to shuffleDeck.\n");
    return;
  }
  
  srandom(time(NULL));

  for (i = 0; i < sz; i++) {
    //copy cards to the temp deck
    cards[i] = (*deck).cards[i];
  }

  for (i = 0; i < sz; i++) {
    j = random() % sz; 
    for (k = 0; k <= i; k++) {
      if (positionroster[k] == j) {
	j = random() % sz;
	k = 0;
      }
      else {
	positionroster[i] = j;
	break;
      }
    }
    (*deck).cards[i] = cards[j];
  }
  return;
}

struct hand *dealHand(struct deck *deck, size_t numcards) {
  size_t i;
  struct hand *hand;
  size_t newdealtnum;

  //Error check
  if (deck == NULL) {
    fprintf(stderr, "Passed a null pointer as the deck to dealHand.\n");
    return NULL;
  }
  else if (numcards > (*deck).numbase) {
    reshuffleDeck(deck);
  }
  if (numcards > (*deck).numbase) { //check if reshuffle did not fix the issue
    fprintf(stderr, "The deck is not large enough to deal this hand.\n");
    return NULL;
  }
  
  //initialize the hand memory structures
  newdealtnum = numcards + (*deck).numdealt;
  hand = malloc(sizeof(struct hand));
  (*hand).cards = malloc(numcards * sizeof(struct card));
  (*deck).dealt = realloc((*deck).dealt, newdealtnum * sizeof(struct card));
  
  for (i = 0; i < numcards; i++) {
    (*hand).cards[i] = (*deck).cards[(*deck).numbase - 1]; //move last card in base deck to hand
    (*deck).dealt[(*deck).numdealt + 1] = (*deck).cards[(*deck).numbase - 1];  //copy the dealt card to the dealt roster
    (*deck).numdealt = (*deck).numdealt + 1; //increment dealt roster number
    (*deck).numbase = (*deck).numbase - 1;  //decrement base pile number
  }
  (*deck).cards = realloc((*deck).cards, (*deck).numbase * sizeof(struct card)); //realloc the base deck to the size with the cards dealt
  
  return hand;
}

int discardCards(struct deck *deck, struct hand *hand, struct card **discards);

int dealCards(struct deck *deck, struct hand *hand, int num);

int showHand(struct hand *hand) {
  size_t i;

  //Error check
  if (hand == NULL) {
    fprintf(stderr, "Passed null pointer as hand to showHand.\n");
    return -1;
  }
  else if ((*hand).size == 0) {
    fprintf(stderr, "The hand passed to showHand was empty.\n");
    return 0;
  }

  printf("%s's hand:\n", (*hand).owner);
  for (i = 0; i < (*hand).size; i++) {
    showCard((*hand).card[i]);
    printf(",");
  }
  printf("\n");
  return 1;
}

int showCard(struct card *card) {
  //Error check
  if (card == NULL) {
    fprintf(stderr, "Passed a null pointer as the card to showCard.\n");
    return -1;
  }
  
  switch(card.value) {
  case ACE:
    printf("%s of ", ace);
    break;
  case JACK:
    printf("%s of ", jack);
    break;
  case QUEEN:
    printf("%s of ", queen);
    break;
  case KING:
    printf("%s of ", king);
    break;
  case default:
    printf("%i of ", card.value);
    break;
  }
  
  switch(card.suit) {
  case SPADE:
    printf("%s", spade);
    break;
  case DIAMOND:
    printf("%s", diamond);
    break;
  case HEART:
    printf("%s", heart);
    break;
  case CLUB:
    printf("%s", club);
  }
  return 1;
}

//reshuffleDeck shuffles the cards from the discard pile back into the base deck
int reshuffleDeck(struct deck *deck) {
  size_t i;

  //quick error condition check
  if (deck == NULL) {
    fprint(stderr, "Passed a null pointer as the deck to reshuffleDeck.\n");
    return -1;
  }
  else if ((*deck).numdiscard == 0) {
    shuffleDeck(deck);  //still shuffle the deck, but we return 0 as a partial error
    return 0;
  }
  
  (*deck).cards = realloc((*deck).cards, ((*deck).numbase + (*deck).numdiscard) * sizeof(struct card)); //increase the base deck size
 
  for (i = 0; i < (*deck).numdiscard; i++) {
    (*deck).cards[i + (*deck).numbase] = (*deck).discard[i];  //append the discard deck to the end of the base deck
  }
  
  free((*deck).discard); //clear the discard pile
  (*deck).numdiscard = 0;

  shuffleDeck(deck);

  return 1;  //success
}

