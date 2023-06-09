#ifndef CARDS_DEFINES_H
#define CARDS_DEFINES_H


#include <array>
#include <vector>

//#include <tchar.h>

#include "hands.h"


/*
 * Callback 
 * Will notify when the deck or hands have changed
 *
 */
typedef long LCARDRESULT;
typedef LCARDRESULT (*CARDPROC)( const class Deck & playerHand, Hands::Hand, const class Deck & computerHand, Hands::Hand, Hands::Hand_Equality, Hands::notification notify, std::vector<int> & discard_cards, void * lParam );


class Card {

    public:

        typedef enum {

            Spades,
            Hearts,
            Diamonds,
            Clubs,
            suit_any

        } Suit;


        typedef enum {

            Deuce = 2,
            Trey,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Knave,
            Queen,
            King,
            Ace,
            rank_any

        } Rank;


        Suit        suit;
        Rank        rank;
        unsigned    ID;

        explicit Card( Rank r, Suit s, unsigned uID ) {

            suit = s;
            rank = r;
            ID   = uID;

        }

        const char * suit_name( void ) const {

            switch( suit ) {

                case Spades:   return "Spades";
                case Hearts:   return "Hearts";
                case Diamonds: return "Diamonds";
                case Clubs:    return "Clubs";

                default:       return "UNKNOWN";

            }

        }

        const char * suit_symbol( void ) const {

            switch( suit ) {

#if 1
                case Spades:   return "SPADE";
                case Hearts:   return "HEART";
                case Diamonds: return "DIAMOND";
                case Clubs:    return "CLUB";
#else
                case Spades:   return "♠";
                case Hearts:   return "♥️";
                case Diamonds: return "♦️";
                case Clubs:    return "♣";
#endif

                default:       return "UNKNOWN";

            }

        }

        const char * rank_name( void ) const {

            switch( rank ) {

                case Deuce: return "Deuce";
                case Trey:  return "Trey";
                case Four:  return "Four";
                case Five:  return "Five";
                case Six:   return "Six";
                case Seven: return "Seven";
                case Eight: return "Eight";
                case Nine:  return "Nine";
                case Ten:   return "Ten";
                case Knave: return "Knave";
                case Queen: return "Queen";
                case King:  return "King";
                case Ace:   return "Ace";

                default:    return "UNKNOWN";

            }

        }

        static bool PlayHand( CARDPROC cardproc, void * );

};


extern const std::array<const Card, 52> Cards;


#endif /* CARDS_DEFINES_H */
