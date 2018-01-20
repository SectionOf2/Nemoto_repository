/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      コンポーネント名 : TTT	 	        	                        */
/*                                                                              */
/*      ファイル名 : TTT_TicTacToe_in_p.h			                */
/*                                                                              */
/*	機能概要 ： マルバツゲーム				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#ifndef __TTT_TICTACTOE_IN_P_H__
#define __TTT_TICTACTOE_IN_P_H__

static void ttt_initPosition( TTT_Position_T *position );
static void ttt_printPosition( const TTT_Position_T *position );
static U1 ttt_isInvalidMove( const TTT_Position_T *position, U1 point );
static void ttt_Move( TTT_Position_T *position, U1 point );
static U1 ttt_isGameOver( const TTT_Position_T *position );

#endif /* __TTT_TICTACTOE_IN_P_H__ */
