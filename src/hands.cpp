

#include "deck.h"
#include "dbg_hlp.h"


#include <map>


typedef std::map<Card::Rank,unsigned> Occurence;
typedef std::pair<Card::Rank, Card::Rank> TwoPair;


bool Hands::IsRoyalFlush( const Deck & hand ) {

    const Card & Ace = hand.find( Card::Ace, Card::suit_any );

    if ( Card::suit_any == Ace.suit ) {

        return false;

    }

    // Rest of hand must also be in this suit

    Card::Rank RoyalFlush[] = { Card::Ten, Card::Knave, Card::Queen, Card::King };

    for ( unsigned u = 0; u < sizeof( RoyalFlush ) / sizeof( RoyalFlush[0] ); u++ ) {

        const Card & card = hand.find( RoyalFlush[u], Ace.suit );

        if ( card.suit != Ace.suit ) {

            return false;

        }

    }

    return true;

}


bool Hands::IsStraightFlush( const Deck & hand ) {

    if ( ! hand.size() ) {

        return false;

    }

    const Card & First = hand.at( 0 );

    // Rest of hand must also be in this suit and in increasing rank

    for ( unsigned u = 1; u < hand.size(); u++ ) {

        const Card & card = hand.at( u );

        if ( ( card.suit != First.suit ) || ( card.rank != ( First.rank + u ) ) ) {

            return false;

        }

    }

    return true;

}


bool Hands::IsFourofaKind( const Deck & hand ) {

    auto check_hand = []( const Deck & hand, Card::Rank rank ) {

        unsigned u  = 0;

        for ( auto const & card : hand ) {

            if ( card.get().rank == rank ) {

                u++;

            }

        }

        return u;

    };

    if ( 5 != hand.size() ) {

        return false;

    }


    for ( auto const & card : hand ) {

        unsigned u = check_hand( hand, card.get().rank );

        if ( 4 == u ) {

            return true;

        }

    }

    return false;

}


static void CountOccurences( const Deck & hand, Occurence & occurences ) {

    for ( auto const & card : hand ) {

        Occurence::iterator i = occurences.find( card.get().rank );

        if ( occurences.end() == i ) {

            // Never seen before, add it
            occurences.insert( std::pair<Card::Rank,unsigned>( card.get().rank, 1 ) );

        } else {

            // Increment its reference-count
            i->second++;

        }

    }

}


bool Hands::IsFullHouse( const Deck & hand ) {

    Occurence occurences;

    CountOccurences( hand, occurences );

    if ( occurences.size() == 2 ) {

        return true;

    }

    return false;

}


bool Hands::IsFlush( const Deck & hand ) {

    Card::Suit suit = Card::suit_any;

    for ( auto const & card : hand ) {

        if ( Card::suit_any == suit ) {

            suit = card.get().suit;

        } else {

            if ( card.get().suit != suit ) {

                return false;

            }

        }

    }

    return true;

}


bool Hands::IsStraight( const Deck & hand ) {

    if ( ! ( 5 == hand.size() ) ) {

        return false;

    }

    const Card & First = hand.at( 0 );

    // Rest of hand must be in increasing rank

    for ( unsigned u = 1; u < hand.size(); u++ ) {

        const Card & card = hand.at( u );

        if ( card.rank != ( First.rank + u ) ) {

            // Check if this is the last card, and that the first card was a deuce
            if ( ( u == 4 ) && ( Card::Ace == card.rank ) && ( Card::Deuce == hand.at( 0 ).get().rank ) ) {

                // It's an Ace-2-3-4-Five straight
                continue;

            }

            return false;

        }

    }

    return true;

}


bool Hands::IsThreeofaKind( const Deck & hand ) {

    Occurence occurences;

    CountOccurences( hand, occurences );

    if ( occurences.size() != 3 ) {

        return false;

    }

    for ( auto const & occurence : occurences ) {

        if ( 3 == occurence.second ) {

            return true;

        }

    }

    return false;

}


bool Hands::IsTwoPair( const Deck & hand ) {

    Occurence occurences;

    CountOccurences( hand, occurences );

    unsigned uPairs = 0;

    for ( auto const & occurence : occurences ) {

        if ( 2 == occurence.second ) {

            uPairs++;

        }

    }

    if ( 2 == uPairs ) {

        return true;

    }

    return false;

}


bool Hands::IsOnePair( const Deck & hand ) {

    Occurence occurences;

    CountOccurences( hand, occurences );

    for ( auto const & occurence : occurences ) {

        if ( 2 == occurence.second ) {

            return true;

        }

    }

    return false;

}


bool Hands::IsHighCard( const Deck & hand ) {

    return true;

}


Hands::Hand Hands::evaluate( const Deck & hand ) {

    if ( IsRoyalFlush( hand ) ) {

        return hand_Royal_Flush;

    }

    if ( IsStraightFlush( hand ) ) {

        return hand_Straight_Flush;

    }

    if ( IsFourofaKind( hand ) ) {

        return hand_Four_of_a_Kind;

    }

    if ( IsFullHouse( hand ) ) {

        return hand_Full_House;

    }

    if ( IsFlush( hand ) ) {

        return hand_Flush;

    }

    if ( IsStraight( hand ) ) {

        return hand_Straight;

    }

    if ( IsThreeofaKind( hand ) ) {

        return hand_Three_of_a_Kind;

    }

    if ( IsTwoPair( hand ) ) {

        return hand_Two_Pair;

    }

    if ( IsOnePair( hand ) ) {

        return hand_One_Pair;

    }

    return hand_High_Card;

}


Hands::Hand_Equality Hands::CompareRoyalFlushes( const class Deck & /* hand1 */, const class Deck & /* hand2 */ ) {

    // Royal flushes are always equal
    return Hand_Equality_TrulyEqual;

}


Hands::Hand_Equality Hands::CompareStraightFlushes( const class Deck & hand1, const class Deck & hand2 ) {

    if ( hand1.at( 4 ).get().rank == hand2.at( 4 ).get().rank ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( hand1.at( 4 ).get().rank > hand2.at( 4 ).get().rank ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareFourofaKinds( const class Deck & hand1, const class Deck & hand2 ) {

    auto get_FourofaKinds = []( const Deck & hand ) {

        Occurence occurences;

        CountOccurences( hand, occurences );

        for ( auto const & occurence : occurences ) {

            if ( 4 == occurence.second ) {

                return occurence.first;

            }

        }

        TRACE( ID_DBG_ERROR, "ERROR EVALUATING FOUR OF A KINDS" EOL );
        return Card::rank_any;

    };

    Card::Rank t1 = get_FourofaKinds( hand1 );
    Card::Rank t2 = get_FourofaKinds( hand2 );

    if ( t1 == t2 ) {

        TRACE( ID_DBG_ERROR, "LOGIC ERROR EVALUATING FOUR OF A KINDS" EOL );
        return Hand_Equality_TrulyEqual;

    }

    if ( t1 > t2 ) {


        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareFullHouses( const class Deck & hand1, const class Deck & hand2 ) {

    // Returns the 3-of-a-kind as the first of the pair and the 2-of-a-kind as the second of the pair
    auto get_Flushes = []( const Deck & hand ) {

        Occurence occurences;

        CountOccurences( hand, occurences );

        TwoPair pair( Card::rank_any, Card::rank_any );

        for ( auto const & occurence : occurences ) {

            if ( 3 == occurence.second ) {

                pair.first = occurence.first;

            } else if ( 2 == occurence.second ) {

                pair.second = occurence.first;

            }

        }

        return pair;

    };

    TwoPair h1 = get_Flushes( hand1 );
    TwoPair h2 = get_Flushes( hand2 );

    // Testing for equality is unnecessary, both players CANNOT have the same three-of-a-kinds

    if ( h1.first > h2.first ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareFlushes( const class Deck & hand1, const class Deck & hand2 ) {

    if ( hand1.at( 4 ).get().rank == hand2.at( 4 ).get().rank ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( hand1.at( 4 ).get().rank > hand2.at( 4 ).get().rank ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareStraights( const class Deck & hand1, const class Deck & hand2 ) {

    if ( hand1.at( 4 ).get().rank == hand2.at( 4 ).get().rank ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( hand1.at( 4 ).get().rank > hand2.at( 4 ).get().rank ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareThreeofaKinds( const class Deck & hand1, const class Deck & hand2 ) {

    auto get_ThreeofaKinds = []( const Deck & hand ) {

        Occurence occurences;

        CountOccurences( hand, occurences );

        for ( auto const & occurence : occurences ) {

            if ( 3 == occurence.second ) {

                return occurence.first;

            }

        }

        TRACE( ID_DBG_ERROR, "ERROR EVALUATING THREE OF A KINDS" EOL );
        return Card::rank_any;

    };

    Card::Rank t1 = get_ThreeofaKinds( hand1 );
    Card::Rank t2 = get_ThreeofaKinds( hand2 );

    if ( t1 == t2 ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( t1 > t2 ) {


        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareTwoPairs( const class Deck & hand1, const class Deck & hand2 ) {

    auto get_pairs = []( const Deck & hand ) {

        Occurence occurences;

        CountOccurences( hand, occurences );

        TwoPair pairs(Card::rank_any, Card::rank_any);

        for ( auto const & occurence : occurences ) {

            if ( 2 == occurence.second ) {

                if ( Card::rank_any == pairs.first ) {

                    pairs.first = occurence.first;

                } else {

                    pairs.second = occurence.first;

                }

            }

        }

        return pairs;

    };

    TwoPair twopair1 = get_pairs( hand1 );
    TwoPair twopair2 = get_pairs( hand2 );

    if ( ( twopair1.second == twopair2.second ) && ( twopair1.first == twopair2.first ) ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( twopair1.second == twopair2.second ) {

        if ( twopair1.first > twopair2.first ) {

            return Hand_Equality_First_Hand_Is_Highest;

        } else {

            return Hand_Equality_Second_Hand_Is_Highest;

        }

    }

    if ( twopair1.second > twopair2.second ) {


        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareOnePairs( const class Deck & hand1, const class Deck & hand2 ) {

    auto get_pair = []( const Deck & hand ) {

        for ( unsigned u = 0; u < ( hand.size() - 1 ); u++ ) {

            if ( hand.at( u ).get().rank == hand.at( u + 1 ).get().rank ) {

                return hand.at( u ).get().rank;

            }

        }

        return Card::rank_any;

    };

    Card::Rank h1 = get_pair( hand1 );

    Card::Rank h2 = get_pair( hand2 );

    if ( h1 == h2 ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( h1 > h2 ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}


Hands::Hand_Equality Hands::CompareHighCards( const class Deck & hand1, const class Deck & hand2 ) {

    const Card & h1First = hand1.at( 4 );
    const Card & h2First = hand2.at( 4 );

    if ( h1First.rank == h2First.rank ) {

        return Hand_Equality_TrulyEqual;

    }

    if ( h1First.rank > h2First.rank ) {

        return Hand_Equality_First_Hand_Is_Highest;

    }

    return Hand_Equality_Second_Hand_Is_Highest;

}
