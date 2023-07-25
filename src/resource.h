#ifndef __H_RESOURCE_H__
#define __H_RESOURCE_H__


#ifdef __unix__
#else /* ! unix */
#include <windows.h>
//#include <commctrl.h>
#endif /* ! unix */


#define IDSZ_MAIN_WINDOW_CLASS                    "Sprysoftware|Poker|MainWnd"
//#define IDSZ_CARD_WINDOW_CLASS                    "Sprysoftware|Poker|CardWnd"
#define IDSZ_CARD_WINDOW_CLASS                    WC_BUTTON

#define PLAYERCARD_CTL_STYLE                      ( BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_TABSTOP )
#define COMPUTERCARD_CTL_STYLE                    ( BS_OWNERDRAW | WS_CHILD | WS_VISIBLE | WS_DISABLED )

#define IDSZ_INIFILE_NAME                         "poker.ini"

#define PROGRAM_FATAL_ERROR                      TEXT( "Poker - FATAL ERROR" )


#define WM_LANGUAGECHANGE                         ( WM_USER + 200 )


/* ------------------------------------------------- Icons */

#define IDI_MAIN                                  10


/* ----------------------------------------------- Bitmaps */

#define IDBMP_BACK_ABSTRACT                    100
#define IDBMP_BACK_ABSTRACT_CLOUDS             101
#define IDBMP_BACK_ABSTRACT_SCENE              102
#define IDBMP_BACK_ASTRONAUT                   103
#define IDBMP_BACK_BLUE                        104
#define IDBMP_BACK_BLUE2                       105
#define IDBMP_BACK_CARS                        106
#define IDBMP_BACK_CASTLE                      107
#define IDBMP_BACK_FISH                        108
#define IDBMP_BACK_FROG                        109
#define IDBMP_BACK_RED                         110
#define IDBMP_BACK_RED2                        111

#define IDBMP_BACK_TEST                        112

#define ID_SPADES_ACE                          1
#define ID_SPADES_DEUCE                        2
#define ID_SPADES_TREY                         3
#define ID_SPADES_4                            4
#define ID_SPADES_5                            5
#define ID_SPADES_6                            6
#define ID_SPADES_7                            7
#define ID_SPADES_8                            8
#define ID_SPADES_9                            9
#define ID_SPADES_10                          10
#define ID_SPADES_KNAVE                       11
#define ID_SPADES_QUEEN                       12
#define ID_SPADES_KING                        13

#define ID_HEARTS_ACE                         14
#define ID_HEARTS_DEUCE                       15
#define ID_HEARTS_TREY                        16
#define ID_HEARTS_4                           17
#define ID_HEARTS_5                           18
#define ID_HEARTS_6                           19
#define ID_HEARTS_7                           20
#define ID_HEARTS_8                           21
#define ID_HEARTS_9                           22
#define ID_HEARTS_10                          23
#define ID_HEARTS_KNAVE                       24
#define ID_HEARTS_QUEEN                       25
#define ID_HEARTS_KING                        26

#define ID_DIAMONDS_ACE                       27
#define ID_DIAMONDS_DEUCE                     28
#define ID_DIAMONDS_TREY                      29
#define ID_DIAMONDS_4                         30
#define ID_DIAMONDS_5                         31
#define ID_DIAMONDS_6                         32
#define ID_DIAMONDS_7                         33
#define ID_DIAMONDS_8                         34
#define ID_DIAMONDS_9                         35
#define ID_DIAMONDS_10                        36
#define ID_DIAMONDS_KNAVE                     37
#define ID_DIAMONDS_QUEEN                     38
#define ID_DIAMONDS_KING                      39

#define ID_CLUBS_ACE                          40
#define ID_CLUBS_DEUCE                        41
#define ID_CLUBS_TREY                         42
#define ID_CLUBS_4                            43
#define ID_CLUBS_5                            44
#define ID_CLUBS_6                            45
#define ID_CLUBS_7                            46
#define ID_CLUBS_8                            47
#define ID_CLUBS_9                            48
#define ID_CLUBS_10                           49
#define ID_CLUBS_KNAVE                        50
#define ID_CLUBS_QUEEN                        51
#define ID_CLUBS_KING                         52


/* -------------------------------------- Dialog templates */

#define IDD_MAIN_LANDSCAPE                        1
#define IDD_MAIN_PORTRAIT                         2
#define IDD_ABOUT                                 4


/* ------------------------------------------------- Menus */

#define IDM_MENU                                  1


/* -------------------------------------- Menu command IDs */

#define IDM_ABOUT                                 100
#define IDM_LANG_EN                               110
#define IDM_LANG_FR                               120
#define IDM_LANG_ES                               130
#define IDM_EXIT                                  140
#define IDM_HELP                                  145


/* ---------------------------------- Main dialog controls */

#define IDST_ICON                                 150
#define IDB_CONTINUE                              200

#define IDST_COMPUTER_IMAGE_GROUP                 400

#define IDST_COMPUTERCARD1                        410
#define IDST_COMPUTERCARD2                        411
#define IDST_COMPUTERCARD3                        412
#define IDST_COMPUTERCARD4                        413
#define IDST_COMPUTERCARD5                        414
#define IDST_PLAYERCARD1                          415
#define IDST_PLAYERCARD2                          416
#define IDST_PLAYERCARD3                          417
#define IDST_PLAYERCARD4                          418
#define IDST_PLAYERCARD5                          419

#define IDST_PLAYER_IMAGE_GROUP                   500
#define IDST_COMPUTER_STATUS                      515
#define IDST_PLAYER_STATUS                        516

#define COMPUTER_CARD_CONTROL_IDS                 IDST_COMPUTERCARD1, IDST_COMPUTERCARD2, IDST_COMPUTERCARD3, IDST_COMPUTERCARD4, IDST_COMPUTERCARD5
#define PLAYER_CARD_CONTROL_IDS                   IDST_PLAYERCARD1,   IDST_PLAYERCARD2,   IDST_PLAYERCARD3,   IDST_PLAYERCARD4,   IDST_PLAYERCARD5

#define ALL_CARD_CONTROL_BUTTONS                  COMPUTER_CARD_CONTROL_IDS, PLAYER_CARD_CONTROL_IDS

#define IDB_CREDITS                               590


/* --------------------------------- About dialog controls */

#define IDST_VERSION                              100
#define IDST_CREDITS                              110


/* ------------------------- Language strings base offsets */

#define IDS_BASE_LANG_EN                          1000
#define IDS_BASE_LANG_FR                          2000
#define IDS_BASE_LANG_ES                          3000


/* ----------------------------------------------- Strings */

#define IDS_APPERR_INIT                             1
#define IDS_PROGRAM_TITLE                           2
#define IDS_EXIT                                    3
#define IDS_ABOUT                                   4
#define IDS_ERROR                                   5


#endif /* __H_RESOURCE_H__ */
