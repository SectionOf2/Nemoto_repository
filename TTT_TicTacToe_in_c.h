/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      �R���|�[�l���g�� : TTT	 	        	                        */
/*                                                                              */
/*      �t�@�C���� : TTT_TicTacToe_in_c.h			                */
/*                                                                              */
/*	�@�\�T�v �F �}���o�c�Q�[��				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#ifndef __TTT_TICTACTOE_IN_C_H__
#define __TTT_TICTACTOE_IN_C_H__

#define	D_TTT_ROW_SIZE	(3U)	/* �s�T�C�Y */
#define D_TTT_COLUMN_SIZE	(3U)	/* ��T�C�Y */
#define D_TTT_BOARD_SIZE	(9U)	/* �ՖʃT�C�Y */
#define D_TTT_BOARD_MIN_POINT	(0U)	/* �Ֆʔz��̍ŏ��@�Y���� */
#define D_TTT_PLAYER_NUM	(2U)	/* �v���C���[�� */
#define D_TTT_MAX_TURNS	(9U)	/* �ő�^�[���� */

/* �Ֆʁ@��� */
#define D_TTT_BOARD_EMPTY	(0U)	/* ������*/
#define D_TTT_BOARD_NOUGHT	(1U)	/* �}�� */
#define D_TTT_BOARD_CROSS	(2U)	/* �o�c */

/* bitboard */
#define D_TTT_NOUGHT_BITBOARD	(0U)	/* �}�� �z��Y���� */
#define D_TTT_CROSS_BITBOARD	(1U)	/* �o�c �z��Y����*/
#define D_TTT_BITBOARD_INITIAL_VALUE	(0U)	/* �o�c �z��Y����*/

/* �Q�[���I���̔��� */
#define D_TTT_NOT_GAMEOVER	(0U)	/* �Q�[���I���łȂ� */
#define D_TTT_GAMEOVER	(1U)	/* �Q�[���I�� */
#define D_TTT_NOUGHT_WIN	(2U)	/* �}���̏��� */
#define D_TTT_CROSS_WIN	(4U)	/* �o�c�̏��� */
#define D_TTT_LINE_SIZE	(8U)	/* 3���Ԑ��̐� */
#define D_TTT_ROW_1	(0xE000U)	/* �ォ��1�s�� 1110 0000 0000 0000 */
#define D_TTT_ROW_2	(0x1C00U)	/* �ォ��2�s�� 0001 1100 0000 0000 */
#define D_TTT_ROW_3	(0x0380U)	/* �ォ��3�s�� 0000 0011 1000 0000 */
#define D_TTT_COLUMN_1	(0x9200U)	/* ������1��� 1001 0010 0000 0000 */
#define D_TTT_COLUMN_2	(0x4900U)	/* ������2��� 0100 1001 0000 0000 */
#define D_TTT_COLUMN_3	(0x2480U)	/* ������3��� 0010 0100 1000 0000 */
#define D_TTT_SLANTING_1	(0x8880U)	/* �΂߁@�E������ 1000 1000 1000 0000 */
#define D_TTT_SLANTING_2	(0x2A00U)	/* �΂߁@�E�オ�� 0010 1010 0000 0000 */

/* ��� */
#define D_TTT_NOUGHT_PLAYER	(0U)	/* �}���̎�� */
#define D_TTT_CROSS_PLAYER	(1U)	/* �o�c�̎�� */

/* �֐��@�߂�l */
#define D_TTT_VALID	(0U)	/* �L�� */
#define D_TTT_INVALID	(1U)	/* ���� */
#define D_TTT_ERROR	(99U)	/* �ُ� */

/* �Q�[���J�n */
#define D_TTT_PLAY_TIC_TAC_TOE	(0U)	/* �}���o�c�Q�[���J�n���� */

#endif /* __TTT_TICTACTOE_IN_C_H__ */
