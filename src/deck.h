#ifndef DECK_DEFINES_H
#define DECK_DEFINES_H


#include "cards.h"
#include "hands.h"


#include <vector>
#include <algorithm>
#include <random>


class Deck : public std::vector<std::reference_wrapper<const Card>> {

    static bool sortfunction( const Card & i, const Card & j ) {

        // Compare suits
//        if ( i.suit < j.suit ) {

//            return true;

//        }

//        if ( i.suit == j.suit ) {

            // Compare ranks within suit
            return i.rank < j.rank;

//        }

//        return false;

    }

//    Hands::Hand hand;

    public:

        Deck( void ) {

//            hand = Hands::hand_Unknown;

        }

        void shuffle( void ) {

            std::random_device rd;
            std::mt19937 dealer( rd() );

            std::shuffle( begin(), end(), dealer );

        }

        bool Deal( Deck & hand, unsigned ncards ) {

            if ( size() < ncards ) {

                return false;

            }

            for ( unsigned u = 0; u < ncards; u++ ) {

                hand.push_back( front() );
                erase( begin() );

            }

            return true;

        }

        const Card & find( Card::Rank, Card::Suit ) const;

        void sort( void ) {

            std::sort( begin(), end(), sortfunction ) ;

        }

};


#endif /* DECK_DEFINES_H */
