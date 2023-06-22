#ifndef HANDS_DEFINES_H
#define HANDS_DEFINES_H


#ifdef _WIN32
#include <windows.h>
#define TEXTCHAR TCHAR
#else
#define TEXT( string ) string
#define TEXTCHAR char
#endif


class Hands {

    static bool IsRoyalFlush( const class Deck & hand );
    static bool IsStraightFlush( const class Deck & hand );
    static bool IsFourofaKind( const class Deck & hand );
    static bool IsFullHouse( const class Deck & hand );
    static bool IsFlush( const class Deck & hand );
    static bool IsStraight( const class Deck & hand );
    static bool IsThreeofaKind( const class Deck & hand );
    static bool IsTwoPair( const class Deck & hand );
    static bool IsOnePair( const class Deck & hand );
    static bool IsHighCard( const class Deck & hand );

    public:

        typedef enum {

            hand_Unknown,
            hand_High_Card,
            hand_One_Pair,
            hand_Two_Pair,
            hand_Three_of_a_Kind,
            hand_Straight,
            hand_Flush,
            hand_Full_House,
            hand_Four_of_a_Kind,
            hand_Straight_Flush,
            hand_Royal_Flush

        } Hand;


        static const TEXTCHAR * name( Hand hand ) {

            switch( hand ) {

                case hand_High_Card:       return TEXT( "High Card" );
                case hand_One_Pair:        return TEXT( "One Pair" );
                case hand_Two_Pair:        return TEXT( "Two Pair" );
                case hand_Three_of_a_Kind: return TEXT( "Three of a Kind" );
                case hand_Straight:        return TEXT( "Straight" );
                case hand_Flush:           return TEXT( "Flush" );
                case hand_Full_House:      return TEXT( "Full House" );
                case hand_Four_of_a_Kind:  return TEXT( "Four of a Kind" );
                case hand_Straight_Flush:  return TEXT( "Straight Flush" );
                case hand_Royal_Flush:     return TEXT( "Royal Flush" );

                default:
                    return TEXT( "UNKNOWN" );

            }

        }


        typedef enum {

            Hand_Equality_Unknown,
            Hand_Equality_TrulyEqual,
            Hand_Equality_First_Hand_Is_Highest,
            Hand_Equality_Second_Hand_Is_Highest

        } Hand_Equality;

        typedef enum {

            notification_init,
            notification_shuffle,
            notification_deal,
            notification_discard,
            notification_reveal

        } notification;

        static Hand_Equality CompareRoyalFlushes( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareStraightFlushes( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareFourofaKinds( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareFullHouses( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareFlushes( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareStraights( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareThreeofaKinds( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareTwoPairs( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareOnePairs( const class Deck & hand1, const class Deck & hand2 );
        static Hand_Equality CompareHighCards( const class Deck & hand1, const class Deck & hand2 );

        static Hand evaluate( const class Deck & hand );

};


#endif /* HANDS_DEFINES_H */
