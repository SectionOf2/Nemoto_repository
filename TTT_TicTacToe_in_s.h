/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      コンポーネント名 : TTT	 	        	                        */
/*                                                                              */
/*      ファイル名 : TTT_TicTacToe_in_s.h			                */
/*                                                                              */
/*	機能概要 ： マルバツゲーム				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#ifndef __TTT_TICTACTOE_IN_S_H__
#define __TTT_TICTACTOE_IN_S_H__

typedef unsigned char U1;
typedef unsigned short U2;
typedef unsigned long U4;
typedef unsigned long long  U8;
typedef signed char S1;
typedef signed short S2;
typedef signed long S4;
typedef signed long long  S8;
typedef char C1;

typedef struct S_TTT_Position {
  U1 board[D_TTT_BOARD_SIZE];	/* 盤面 */
  U1 turns;			/* 手数 */
  U1 currentPlayer;		/* 手番 */
  U2 bitboard[D_TTT_PLAYER_NUM];		/* 勝敗判定用ビット 添え字0：マル、添え字1：バツ */
}TTT_Position_T;

#endif /* __TTT_TICTACTOE_IN_S_H__ */
