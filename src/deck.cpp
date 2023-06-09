

#include "deck.h"


#include <iostream>


Card none( Card::rank_any, Card::suit_any, 0 );


const Card & Deck::find( Card::Rank rank, Card::Suit suit ) const {

    for ( auto const & card : *this ) {

        if ( ( card.get().rank == rank ) && ( card.get().suit == suit ) ) {

            return card;

        }

        if ( ( suit == Card::suit_any ) && ( card.get().rank == rank ) ) {

            return card;

        }

        if ( ( suit == card.get().suit ) && ( card.get().rank == Card::rank_any ) ) {

            return card;

        }

        if ( ( suit == card.get().suit ) && ( rank == card.get().rank ) ) {

            return card;

        }

    }

    return none;

}
