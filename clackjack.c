#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define DECK_SIZE 52
#define NUM_COLORS 4
#define CARDS_PER_COLOR 13

struct card {
	char key; 					/* e.g. '4', 'J', 'Q'. */
	unsigned int value;	/* A 1 or 14. J=11, Q=12. */
	unsigned int hidden;
};


struct deck {
	struct card *cards[DECK_SIZE];
	unsigned int num_cards;
};

/* Takes deck or hand as input. If it is deck, print all as visible (debug).
 * If it is hand, print only non-hidden cards. */
void print_cards (struct deck *d) {
	/* error: Getting only [K] in deck when printing here but not in main. */
	unsigned int print_all;
        print_all = 1 ? d->num_cards == DECK_SIZE : 0;
	
	// printf("num_cards: %u \n", d->num_cards);

	size_t i;
	struct card *c;
	
	for (i = 0; i < d->num_cards; i++) {
		c = d->cards[i];
		if (print_all || !c->hidden) 
			printf ("[%c] at i=%lu \n", c->key, i);
			
	}	
}

void print_info () {
	printf ("===== Clackjack v0.1 =====\n");
}

int main () {
	print_info ();
	
	/* Init the deck of cards. */
	struct deck *d = malloc (DECK_SIZE * sizeof (struct card *));
	d->num_cards = 0;
	
	/* Key array. */
	const char k[CARDS_PER_COLOR + 1] = "A23456789TJQK\0";
	
	// printf ("k[3] == %c \n", k[3]);
	
	/* Add 52 hidden cards, 4 of each value since
	 * color does not matter in BJ. */

	size_t i, j, deck_index = 0;

	for (i = 0; i < NUM_COLORS; i++) {
		for (j = 0; j < CARDS_PER_COLOR; j++) {
			
			struct card *c = malloc (sizeof (struct card)); 
			c->key = k[j];
			c->value = j + 1;
			c->hidden = 1;

			deck_index = i * CARDS_PER_COLOR + j;

			printf("%c at i=%lu, j=%lu \n", k[j], i, j);
			
			d->cards[deck_index] = c;
			d->num_cards++;
		}
	}

       	print_cards (d);	
	assert (d->num_cards == DECK_SIZE);

	/* Shuffle the deck. */
}
