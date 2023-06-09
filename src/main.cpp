

#include "project.h"


#define DEFAULT_OUTPUT_CHANNELS ( ID_DBG_ERROR | ID_DBG_USER_MESSAGES )


unsigned int gDebugging = DEFAULT_OUTPUT_CHANNELS;


LCARDRESULT pokerproc( const class Deck & playerhand, Hands::Hand playerResult, const class Deck & computerhand, Hands::Hand computerResult, Hands::Hand_Equality he, Hands::notification notify, std::vector<int> & discard_cards, void * ) {

    auto print_deck = []( const Deck & deck ) {

        unsigned u = 1;

        for ( auto const & card : deck ) {

            TRACE( ID_DBG_USER_MESSAGES, u << " - " << card.get().rank_name() << " of " << card.get().suit_name() << " (" << card.get().rank << card.get().suit_symbol() << ")" << EOL );

            u++;

        }

    };

    auto ask_discards = []( std::vector<int> & discard_cards ) {

        std::string cards;

        std::getline( std::cin, cards );

        std::stringstream ss( cards );

        std::vector<int> v;

        int i;

        while( ss >> i ) {

            if ( ! ( ( i >= 1 ) && ( i <= 5 ) ) ) {

                TRACE( ID_DBG_USER_MESSAGES, EOL "Can't discard card # " << i << EOL );

            }

            v.push_back( i );

        }

        if ( ! v.empty() ) {

            std::sort( v.begin(), v.end() );
            v.erase( std::unique( v.begin(), v.end() ), v.end() );

            TRACE( ID_DBG_MINUTIAE, "Going to erase these: " EOL );
            for ( auto item : v ) {

                TRACE( ID_DBG_MINUTIAE, item << " " << EOL );


            }

            discard_cards = v;

        }

    };

    switch( notify ) {

        case Hands::notification_init:
            break;

        case Hands::notification_shuffle:
            break;

        case Hands::notification_deal:

            TRACE( ID_DBG_USER_MESSAGES, EOL "Computer's hand: " << Hands::name( computerResult ) << EOL );
            print_deck( computerhand );

            TRACE( ID_DBG_USER_MESSAGES, EOL "Your hand: " << Hands::name( playerResult ) << EOL );
            print_deck( playerhand );
            break;

        case Hands::notification_discard:

            TRACE( ID_DBG_USER_MESSAGES, EOL "Which cards do you wish to discard: " EOL );
            ask_discards( discard_cards );
            break;

        case Hands::notification_reveal:

            TRACE( ID_DBG_USER_MESSAGES, EOL "Computer's hand: " << Hands::name( computerResult ) << EOL );
            print_deck( computerhand );

            TRACE( ID_DBG_USER_MESSAGES, EOL "Your hand: " << Hands::name( playerResult ) << EOL );
            print_deck( playerhand );

            switch( he ) {

                case Hands::Hand_Equality_TrulyEqual:

                    TRACE( ID_DBG_USER_MESSAGES, EOL "Tie!" EOL );
                    break;

                case Hands::Hand_Equality_First_Hand_Is_Highest:

                    TRACE( ID_DBG_USER_MESSAGES, EOL "You win!" EOL );
                    break;

                case Hands::Hand_Equality_Second_Hand_Is_Highest:

                    TRACE( ID_DBG_USER_MESSAGES, EOL "Computer wins!" EOL );
                    break;

                case Hands::Hand_Equality_Unknown:
                    break;

            }
            break;

    }

    return true;

}


int main( int iArgC, char ** apsArgs ) {

    if ( iArgC > 1 ) {

        int i = atoi( apsArgs[1] );

        if ( 0 != i ) {

            gDebugging = i | DEFAULT_OUTPUT_CHANNELS;

        }

    }

    TRACE( ID_DBG_CHECKPOINT, "Entering process" EOL );

    Card::PlayHand( pokerproc, 0 );

    TRACE( ID_DBG_CHECKPOINT, "Exiting process" EOL );

    return 0;

}
