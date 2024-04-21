#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DECK_SIZE 52
#define NUM_COLORS 4
#define CARDS_PER_COLOR 13

struct card {
	char key; 					/* e.g. '4', 'J', 'Q'. */
	unsigned int value;	/* A 1 or 14. J=11, Q=12. */
	unsigned int hidden;
};


struct deck {
	struct card *cards[DECK_SIZE * sizeof (struct card *)];
	unsigned int num_cards;
};


/* Fisher - Yates Shuffle algorithm. */
void shuffle (struct deck *d) {
	int r;
	srand (time (NULL));

	for (size_t i = d->num_cards - 1; i > 0; i--) {
		r = rand() % (i + 1);
		struct card *c1 = d->cards[i];
		d->cards[i] = d->cards[r];
		d->cards[r] = c1;
	}
}

/* Deal one card from DECK to HAND. */
void deal_one (struct deck *d, struct deck *hand, unsigned int hidden) {
   	/* Take a card from the deck, and add it to hand. memmove? */	
	struct card *c = d->cards[d->num_cards - 1];
	
	assert (hand->num_cards < DECK_SIZE / 2);
	/* Turn the card belly up if we need to. */
	if (!hidden)
		c->hidden = 0;
	
	hand->cards[hand->num_cards] = c;
	hand->num_cards++;
	/* Remove the card from the deck. */
	d->cards[--d->num_cards] = NULL;
}

void print_info ();
void print_cards (struct deck *d);

int main () {
	print_info ();
	
	/* Init the deck of cards. */
	struct deck *d = malloc (sizeof (struct deck));
	d->num_cards = 0;
	
	/* Key array. */
	const char k[CARDS_PER_COLOR + 1] = "A23456789TJQK\0";
	
	/* Add 52 hidden cards, 4 of each value since
	 * color does not matter in BJ. */

	size_t i, j, deck_index;

	for (i = 0; i < NUM_COLORS; i++) {
		for (j = 0; j < CARDS_PER_COLOR; j++) {
			
			struct card *c = malloc (sizeof (struct card)); 
			c->key = k[j];
			c->value = j + 1;
			c->hidden = 1;

			deck_index = i * CARDS_PER_COLOR + j;			
			
			d->cards[deck_index] = c;
			d->num_cards++;
		}
	}

	assert (d->num_cards == DECK_SIZE);
	
	/* Shuffle the deck. */
	shuffle (d);

	/* Hands are represented as decks */
	struct deck *player = malloc (sizeof (struct deck));
    	struct deck *cpu = malloc (sizeof (struct deck));
	
	/* 0 is visible, 1 is hidden. */
	deal_one (d, player, 0);
	deal_one (d, cpu, 1);
	deal_one (d, player, 0);
	deal_one (d, cpu, 0);

	// unsigned int run = 1;
	/* Ask user hit or stand or double. make functions for them. */
	
	print_cards (player);
	print_cards (cpu);
}
/* Takes deck or hand as input. If it is deck, print all as visible (debug).
 * If it is hand, print only non-hidden cards. */
void print_cards (struct deck *d) {
	unsigned int print_all;
    	print_all = 1 ? d->num_cards == DECK_SIZE : 0;
	
	size_t i;
	struct card *c;
	
	for (i = 0; i < d->num_cards; i++) {
		c = d->cards[i];
		if (print_all || !c->hidden) 
			printf ("[%c]", c->key);
		else
			printf ("[ ]");
	}	

	printf("\n");
}

void print_info () {
	printf ("===== Clackjack v0.1 =====\n");
}

