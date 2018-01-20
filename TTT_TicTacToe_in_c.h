/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      コンポーネント名 : TTT	 	        	                        */
/*                                                                              */
/*      ファイル名 : TTT_TicTacToe_in_c.h			                */
/*                                                                              */
/*	機能概要 ： マルバツゲーム				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#ifndef __TTT_TICTACTOE_IN_C_H__
#define __TTT_TICTACTOE_IN_C_H__

#define	D_TTT_ROW_SIZE	(3U)	/* 行サイズ */
#define D_TTT_COLUMN_SIZE	(3U)	/* 列サイズ */
#define D_TTT_BOARD_SIZE	(9U)	/* 盤面サイズ */
#define D_TTT_BOARD_MIN_POINT	(0U)	/* 盤面配列の最小　添え字 */
#define D_TTT_PLAYER_NUM	(2U)	/* プレイヤー数 */
#define D_TTT_MAX_TURNS	(9U)	/* 最大ターン数 */

/* 盤面　情報 */
#define D_TTT_BOARD_EMPTY	(0U)	/* 未入力*/
#define D_TTT_BOARD_NOUGHT	(1U)	/* マル */
#define D_TTT_BOARD_CROSS	(2U)	/* バツ */

/* bitboard */
#define D_TTT_NOUGHT_BITBOARD	(0U)	/* マル 配列添え字 */
#define D_TTT_CROSS_BITBOARD	(1U)	/* バツ 配列添え字*/
#define D_TTT_BITBOARD_INITIAL_VALUE	(0U)	/* バツ 配列添え字*/

/* ゲーム終了の判定 */
#define D_TTT_NOT_GAMEOVER	(0U)	/* ゲーム終了でない */
#define D_TTT_GAMEOVER	(1U)	/* ゲーム終了 */
#define D_TTT_NOUGHT_WIN	(2U)	/* マルの勝ち */
#define D_TTT_CROSS_WIN	(4U)	/* バツの勝ち */
#define D_TTT_LINE_SIZE	(8U)	/* 3つ並ぶ線の数 */
#define D_TTT_ROW_1	(0xE000U)	/* 上から1行目 1110 0000 0000 0000 */
#define D_TTT_ROW_2	(0x1C00U)	/* 上から2行目 0001 1100 0000 0000 */
#define D_TTT_ROW_3	(0x0380U)	/* 上から3行目 0000 0011 1000 0000 */
#define D_TTT_COLUMN_1	(0x9200U)	/* 左から1列目 1001 0010 0000 0000 */
#define D_TTT_COLUMN_2	(0x4900U)	/* 左から2列目 0100 1001 0000 0000 */
#define D_TTT_COLUMN_3	(0x2480U)	/* 左から3列目 0010 0100 1000 0000 */
#define D_TTT_SLANTING_1	(0x8880U)	/* 斜め　右下がり 1000 1000 1000 0000 */
#define D_TTT_SLANTING_2	(0x2A00U)	/* 斜め　右上がり 0010 1010 0000 0000 */

/* 手番 */
#define D_TTT_NOUGHT_PLAYER	(0U)	/* マルの手番 */
#define D_TTT_CROSS_PLAYER	(1U)	/* バツの手番 */

/* 関数　戻り値 */
#define D_TTT_VALID	(0U)	/* 有効 */
#define D_TTT_INVALID	(1U)	/* 無効 */
#define D_TTT_ERROR	(99U)	/* 異常 */

/* ゲーム開始 */
#define D_TTT_PLAY_TIC_TAC_TOE	(0U)	/* マルバツゲーム開始する */

#endif /* __TTT_TICTACTOE_IN_C_H__ */
