/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      �R���|�[�l���g�� : TTT	 	        	                        */
/*                                                                              */
/*      �t�@�C���� : TTT_TicTacToe_in_s.h			                */
/*                                                                              */
/*	�@�\�T�v �F �}���o�c�Q�[��				   		        */
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
  U1 board[D_TTT_BOARD_SIZE];	/* �Ֆ� */
  U1 turns;			/* �萔 */
  U1 currentPlayer;		/* ��� */
  U2 bitboard[D_TTT_PLAYER_NUM];		/* ���s����p�r�b�g �Y����0�F�}���A�Y����1�F�o�c */
}TTT_Position_T;

#endif /* __TTT_TICTACTOE_IN_S_H__ */
