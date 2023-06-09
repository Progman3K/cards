

#include "resource.h"
#include "cards.h"
#include "deck.h"


#include "dbg_hlp.h"


const std::array<const Card, 52> Cards = {

    Card( Card::Ace,   Card::Spades, ID_SPADES_ACE       ),
    Card( Card::Deuce, Card::Spades, ID_SPADES_DEUCE     ),
    Card( Card::Trey,  Card::Spades, ID_SPADES_TREY      ),
    Card( Card::Four,  Card::Spades, ID_SPADES_4         ),
    Card( Card::Five,  Card::Spades, ID_SPADES_5         ),
    Card( Card::Six,   Card::Spades, ID_SPADES_6         ),
    Card( Card::Seven, Card::Spades, ID_SPADES_7         ),
    Card( Card::Eight, Card::Spades, ID_SPADES_8         ),
    Card( Card::Nine,  Card::Spades, ID_SPADES_9         ),
    Card( Card::Ten,   Card::Spades, ID_SPADES_10        ),
    Card( Card::Knave, Card::Spades, ID_SPADES_KNAVE     ),
    Card( Card::Queen, Card::Spades, ID_SPADES_QUEEN     ),
    Card( Card::King,  Card::Spades, ID_SPADES_KING      ),

    Card( Card::Ace,   Card::Hearts, ID_HEARTS_ACE       ),
    Card( Card::Deuce, Card::Hearts, ID_HEARTS_DEUCE     ),
    Card( Card::Trey,  Card::Hearts, ID_HEARTS_TREY      ),
    Card( Card::Four,  Card::Hearts, ID_HEARTS_4         ),
    Card( Card::Five,  Card::Hearts, ID_HEARTS_5         ),
    Card( Card::Six,   Card::Hearts, ID_HEARTS_6         ),
    Card( Card::Seven, Card::Hearts, ID_HEARTS_7         ),
    Card( Card::Eight, Card::Hearts, ID_HEARTS_8         ),
    Card( Card::Nine,  Card::Hearts, ID_HEARTS_9         ),
    Card( Card::Ten,   Card::Hearts, ID_HEARTS_10        ),
    Card( Card::Knave, Card::Hearts, ID_HEARTS_KNAVE     ),
    Card( Card::Queen, Card::Hearts, ID_HEARTS_QUEEN     ),
    Card( Card::King,  Card::Hearts, ID_HEARTS_KING      ),

    Card( Card::Ace,   Card::Diamonds, ID_DIAMONDS_ACE   ),
    Card( Card::Deuce, Card::Diamonds, ID_DIAMONDS_DEUCE ),
    Card( Card::Trey,  Card::Diamonds, ID_DIAMONDS_TREY  ),
    Card( Card::Four,  Card::Diamonds, ID_DIAMONDS_4     ),
    Card( Card::Five,  Card::Diamonds, ID_DIAMONDS_5     ),
    Card( Card::Six,   Card::Diamonds, ID_DIAMONDS_6     ),
    Card( Card::Seven, Card::Diamonds, ID_DIAMONDS_7     ),
    Card( Card::Eight, Card::Diamonds, ID_DIAMONDS_8     ),
    Card( Card::Nine,  Card::Diamonds, ID_DIAMONDS_9     ),
    Card( Card::Ten,   Card::Diamonds, ID_DIAMONDS_10    ),
    Card( Card::Knave, Card::Diamonds, ID_DIAMONDS_KNAVE ),
    Card( Card::Queen, Card::Diamonds, ID_DIAMONDS_QUEEN ),
    Card( Card::King,  Card::Diamonds, ID_DIAMONDS_KING  ),

    Card( Card::Ace,   Card::Clubs, ID_CLUBS_ACE         ),
    Card( Card::Deuce, Card::Clubs, ID_CLUBS_DEUCE       ),
    Card( Card::Trey,  Card::Clubs, ID_CLUBS_TREY        ),
    Card( Card::Four,  Card::Clubs, ID_CLUBS_4           ),
    Card( Card::Five,  Card::Clubs, ID_CLUBS_5           ),
    Card( Card::Six,   Card::Clubs, ID_CLUBS_6           ),
    Card( Card::Seven, Card::Clubs, ID_CLUBS_7           ),
    Card( Card::Eight, Card::Clubs, ID_CLUBS_8           ),
    Card( Card::Nine,  Card::Clubs, ID_CLUBS_9           ),
    Card( Card::Ten,   Card::Clubs, ID_CLUBS_10          ),
    Card( Card::Knave, Card::Clubs, ID_CLUBS_KNAVE       ),
    Card( Card::Queen, Card::Clubs, ID_CLUBS_QUEEN       ),
    Card( Card::King,  Card::Clubs, ID_CLUBS_KING        )

};


bool Card::PlayHand( CARDPROC cardproc, void * p ) {

    Deck playing_deck;
    Deck muck_deck;

    Deck playerhand;
    Deck computerhand;

    std::vector<int> discard_cards;

    Hands::Hand playerResult = Hands::hand_Unknown;
    Hands::Hand computerResult = Hands::hand_Unknown;

    Hands::Hand_Equality he = Hands::Hand_Equality_Unknown;

    playing_deck.assign( Cards.begin(), Cards.end() );

    if ( ! cardproc( playerhand, playerResult, computerhand, computerResult, he, Hands::notification_init, discard_cards, p ) ) {

        return false;

    }

    playing_deck.shuffle();

    if ( ! cardproc( playerhand, playerResult, computerhand, computerResult, he, Hands::notification_shuffle, discard_cards, p ) ) {

        return false;

    }

    TRACE( ID_DBG_MINUTIAE, "Shuffled " << playing_deck.size() << " cards" EOL EOL );


#if 1   // Used for normal hands

    if ( ! ( playing_deck.Deal( playerhand, 5 ) && playing_deck.Deal( computerhand, 5 ) ) ) {

        TRACE( ID_DBG_ERROR, "ERROR DEALING" EOL );
        return false;

    }


#else   // Used for testing hands

    const std::array<const Card, 5> myTesthand = {

        Card( Card::Eight, Card::Hearts   ),
        Card( Card::Eight, Card::Spades   ),
        Card( Card::Eight, Card::Clubs    ),
        Card( Card::Queen, Card::Diamonds ),
        Card( Card::Queen, Card::Hearts   ),

    };
    playerhand.assign( myTesthand.begin(), myTesthand.end() );

    const std::array<const Card, 5> computerTesthand = {

        Card( Card::Seven, Card::Hearts   ),
        Card( Card::Seven, Card::Spades   ),
        Card( Card::Seven, Card::Clubs    ),
        Card( Card::Knave, Card::Diamonds ),
        Card( Card::Knave, Card::Clubs    ),

    };
    computerhand.assign( computerTesthand.begin(), computerTesthand.end() );

#endif

    playerhand.sort();
    playerResult = Hands::evaluate( playerhand );

    computerhand.sort();
    computerResult = Hands::evaluate( computerhand );

    if ( ! cardproc( playerhand, playerResult, computerhand, computerResult, he, Hands::notification_deal, discard_cards, p ) ) {

        return false;

    }

    // Allow discards here

    if ( ! cardproc( playerhand, playerResult, computerhand, computerResult, he, Hands::notification_discard, discard_cards, p ) ) {

        return false;

    }

    if ( ! discard_cards.empty() ) {

        // Only allow the requested discards if the playing deck still has at least that many cards
        if ( discard_cards.size() <= playing_deck.size() ) {

            auto getnewcards = discard_cards.size();

            for( ; ! discard_cards.empty(); ) {

                // Remove the numbered cards from the player's deck and add them to the muck
                auto i = discard_cards.back();
                discard_cards.pop_back();

                auto discarded_card = playerhand.at( i - 1 );
                playerhand.erase( playerhand.begin() + ( i - 1 ) );
                muck_deck.push_back( discarded_card );

            }

            playing_deck.Deal( playerhand, getnewcards );

        }

        playerhand.sort();
        playerResult = Hands::evaluate( playerhand );

    }

    discard_cards.clear();

    if ( playerResult == computerResult ) {

        he = Hands::Hand_Equality_TrulyEqual;

        switch( playerResult ) {

            case Hands::hand_High_Card:

                he = Hands::CompareHighCards( playerhand, computerhand );
                break;

            case Hands::hand_One_Pair:

                he = Hands::CompareOnePairs( playerhand, computerhand );
                break;

            case Hands::hand_Two_Pair:

                he = Hands::CompareTwoPairs( playerhand, computerhand );
                break;

            case Hands::hand_Three_of_a_Kind:

                he = Hands::CompareThreeofaKinds( playerhand, computerhand );
                break;

            case Hands::hand_Straight:

                he = Hands::CompareStraights( playerhand, computerhand );
                break;

            case Hands::hand_Flush:

                he = Hands::CompareFlushes( playerhand, computerhand );
                break;

            case Hands::hand_Full_House:

                he = Hands::CompareFullHouses( playerhand, computerhand );
                break;

            case Hands::hand_Four_of_a_Kind:

                he = Hands::CompareFourofaKinds( playerhand, computerhand );
                break;

            case Hands::hand_Straight_Flush:

                he = Hands::CompareStraightFlushes( playerhand, computerhand );
                break;

            case Hands::hand_Royal_Flush:

                he = Hands::CompareRoyalFlushes( playerhand, computerhand );
                break;

            default:

                TRACE( ID_DBG_ERROR, EOL "INTERNAL ERROR!" EOL );
                break;

        }

    } else if ( playerResult > computerResult ) {

        he = Hands::Hand_Equality_First_Hand_Is_Highest;

    } else {

        he = Hands::Hand_Equality_Second_Hand_Is_Highest;

    }

    TRACE( ID_DBG_MINUTIAE,  playing_deck.size() << " cards left in the deck" EOL );
    TRACE( ID_DBG_MINUTIAE,  muck_deck.size() << " cards in the muck" EOL );

    if ( ! cardproc( playerhand, playerResult, computerhand, computerResult, he, Hands::notification_reveal, discard_cards, p ) ) {

        return false;

    }

    return true;

}
