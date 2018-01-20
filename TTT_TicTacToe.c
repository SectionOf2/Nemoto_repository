/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      コンポーネント名 : TTT	 	        	                        */
/*                                                                              */
/*      ファイル名 : TTT_TicTacToe.c			                        */
/*                                                                              */
/*	機能概要 ： マルバツゲーム				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "TTT_TicTacToe_in.h"



/*------------------------------------------------------------------------------*/
/*	機 能  	局面データ初期化							*/
/*									       	*/
/*	引き数	TTT_Position_T *position 局面データポインタ			*/
/*	戻り値 	なし								*/
/*------------------------------------------------------------------------------*/
static void ttt_initPosition( TTT_Position_T *position )
{
  U1 count;	/* カウンタ */

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    for( count = 0; count < D_TTT_BOARD_SIZE; count++ ) {
      position->board[count] = D_TTT_BOARD_EMPTY;
    }

    position->turns = 0;
    position->currentPlayer = D_TTT_NOUGHT_PLAYER;

    for (count = 0; count < D_TTT_PLAYER_NUM; count++ ) {
      position->bitboard[count] = D_TTT_BITBOARD_INITIAL_VALUE;
    }
  }
}


/*------------------------------------------------------------------------------*/
/*	機 能  	盤面表示								*/
/*									       	*/
/*	引き数	const TTT_Position_T *position 局面データポインタ      		*/
/*	戻り値 	なし								*/
/*------------------------------------------------------------------------------*/
static void ttt_printPosition( const TTT_Position_T *position )
{
  U1 rowCount;	/* 行カウンタ */
  U1 columnCount;	/* 列カウンタ */

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    printf("\n");    
    printf(" +---+---+---+\n");
    for( columnCount = 0; columnCount < D_TTT_COLUMN_SIZE; columnCount++ ) {
      for( rowCount = 0; rowCount < D_TTT_ROW_SIZE; rowCount++ ) {
	printf( " | " );
	
	switch( position->board[columnCount * D_TTT_ROW_SIZE + rowCount] ){
	case D_TTT_BOARD_NOUGHT:
	  printf( "o" );
	  break;
	case D_TTT_BOARD_CROSS:
	  printf( "x" );
	  break;
	case D_TTT_BOARD_EMPTY:
	  printf( "%d", columnCount * D_TTT_ROW_SIZE + rowCount + 1 );
	  break;
	default:
	  /* 処理なし */
	  break;
	}
      }
      printf( " |\n" );
      printf( " +---+---+---+\n" );
    }
    printf( "\n" );

    printf( "Turns : %d\n", position->turns );
    printf( "Player : " );

    if( position->currentPlayer ==  D_TTT_NOUGHT_PLAYER ) {
      printf( "o" );
    } else if( position->currentPlayer ==  D_TTT_CROSS_PLAYER ) {
      printf( "x" );
    } else {
      printf( "Invalid Player" );
    }
    printf( "\n\n" );
  }
}



/*------------------------------------------------------------------------------*/
/*	機 能  	有効着手判定							*/
/*									       	*/
/*	引き数	const TTT_Position_T *position 局面データポインタ		       	*/
/*		U1 point ユーザが入力した着手					*/
/*	戻り値 	U1　着手有効判定結果						*/
/*------------------------------------------------------------------------------*/
static U1 ttt_isInvalidMove( const TTT_Position_T *position, U1 point )
{
   U1 ret;	/* 戻り値 */ 

   /* 初期化 */
   ret = D_TTT_ERROR;

   if ( position == NULL ) {
     exit(EXIT_FAILURE);
   } else {
     if( ( point >= D_TTT_BOARD_MIN_POINT )
	 && ( point < D_TTT_BOARD_SIZE )
	 && ( position->board[point] == D_TTT_BOARD_EMPTY ) ) {     
       ret = D_TTT_VALID;
     } else {
       ret = D_TTT_INVALID;      
     }
   }
   return ret;
}



/*------------------------------------------------------------------------------*/
/*	機 能  	ユーザの入力した位置に着手し、盤面、手数を更新				*/
/*									       	*/
/*	引き数	TTT_Position_T *position 局面データポインタ		       	*/
/*		U1 point ユーザが入力した着手					*/
/*	戻り値 	なし								*/
/*------------------------------------------------------------------------------*/
static void ttt_Move( TTT_Position_T *position, U1 point )
{
  U2 bitTmp;	/* ビットボード更新用変数 */

  /* 初期化 */
  bitTmp = 0x8000;	/* 1000 0000 0000 0000 */

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    if( position->currentPlayer == D_TTT_NOUGHT_PLAYER ) {	  /* マルの手番 */
      position->board[point] = D_TTT_BOARD_NOUGHT;
      
      /* ビットボードの更新 */
      if( point > D_TTT_BOARD_MIN_POINT ) {
	bitTmp >>= point;
      }
      position->bitboard[D_TTT_NOUGHT_BITBOARD] |= bitTmp;
    } else if( position->currentPlayer == D_TTT_CROSS_PLAYER ) {	  /* バツの手番 */
      position->board[point] = D_TTT_BOARD_CROSS;

      /* ビットボードの更新 */
      if( point > D_TTT_BOARD_MIN_POINT ) {
	bitTmp >>= point;
      }
      position->bitboard[D_TTT_CROSS_BITBOARD] |= bitTmp;
    } else {
      /* 処理なし */
    }
    
    position->turns++; 
  }
}



/*------------------------------------------------------------------------------*/
/*	機 能  	ビットマスク(ゲーム終了判定、勝敗判定)作成				*/
/*									       	*/
/*	引き数	const TTT_Position_T *position 局面データポインタ			*/
/*	戻り値 	U1 ビットマスク(ゲーム終了判定、勝敗判定)				*/
/*------------------------------------------------------------------------------*/
static  U1 ttt_isGameOver( const TTT_Position_T *position )
{
  U2 checkLine[D_TTT_LINE_SIZE] = { D_TTT_ROW_1, D_TTT_ROW_2, D_TTT_ROW_3,
		     		   D_TTT_COLUMN_1, D_TTT_COLUMN_2, D_TTT_COLUMN_3,
  		     		   D_TTT_SLANTING_1, D_TTT_SLANTING_2 };	/* 勝敗判定用 */
  U1 currentPlayer;	/* 手番 */
  U2 bitwiseOperationResult;	/* ビット演算結果 */
  U1 lineCount;	/* カウンタ */
  U1 ret;	/* 戻り値 */

  /* 初期化 */
  currentPlayer = position->currentPlayer;
  bitwiseOperationResult = 0;
  lineCount = 0;
  ret = D_TTT_NOT_GAMEOVER;

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    for( lineCount = 0; lineCount < D_TTT_LINE_SIZE; lineCount++ ) {
      bitwiseOperationResult = position->bitboard[currentPlayer] & checkLine[lineCount];
      
      /* 勝敗がついた場合、戻り値を更新する */
      if( bitwiseOperationResult == checkLine[lineCount] ) {
	ret |= D_TTT_GAMEOVER;
	
	if( currentPlayer == D_TTT_NOUGHT_PLAYER ) {
	  ret |= D_TTT_NOUGHT_WIN;
	} else if( currentPlayer == D_TTT_CROSS_PLAYER ) {
	  ret |= D_TTT_CROSS_WIN;
	} else {
	  /* 処理なし */
	}
	
	/* for文から抜ける */
	break;
      }
    }
    
    /* 縦横斜めに"o" or "x"が3つ並んでいない　かつ　最大手数(9手)に達した場合、引き分けでゲーム終了とする */
    if( ( ret == 0 ) && ( position->turns == D_TTT_MAX_TURNS ) ) {
      ret |= D_TTT_GAMEOVER;
    }
  }
  
  return ret;
}



/*------------------------------------------------------------------------------*/
/*	機 能  	手番更新								*/
/*									       	*/
/*	引き数	TTT_Position_T *position 局面データポインタ			*/
/*	戻り値 	なし								*/
/*------------------------------------------------------------------------------*/
static  void ttt_updateCurrentPlayer( TTT_Position_T *position )
{
  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {    
    if( position->currentPlayer == D_TTT_NOUGHT_PLAYER ) {
      position->currentPlayer = D_TTT_CROSS_PLAYER;
    } else if( position->currentPlayer == D_TTT_CROSS_PLAYER ) {
      position->currentPlayer = D_TTT_NOUGHT_PLAYER;
    } else {
      /* 処理なし */
    }
  }
}



/*------------------------------------------------------------------------------*/
/*	機 能  	マルバツゲームを実行						*/
/*									       	*/
/*	引き数	なし								*/
/*	戻り値 	U1 0								*/
/*------------------------------------------------------------------------------*/
U1 main( void )
{
  TTT_Position_T position;	/* 局面 */
  TTT_Position_T *pPosition;	/* 局面ポインタ */
  U1 inputPointTmp;	/* ユーザの入力した着手 */
  U1 inputPoint;	/* ユーザの入力した着手-1 */
  U1 checkInvalidMove;	/* 着手の有効フラグ */
  U1 checkGameOverTmp;	/* 終了判定、勝敗判定用ビットマスク */
  U1 checkGameOver;	/* 終了判定 */
  U1 checkNoughtWin;	/* マル　勝利判定 */
  U1 checkCrossWin;	/* バツ　勝利判定 */
  C1 checkContinue;	/* ゲーム開始判定 */
    
  /* 初期化 */
  pPosition = &position;

  /* タイトル画面 */
  printf( "Play Tic Tac Toe\n" );
  printf( "Input '0' -> Start, other -> Exit\n\n" );
  scanf( "%c", &checkContinue );
  getchar();
  
  while( checkContinue -'0' ==  D_TTT_PLAY_TIC_TAC_TOE ) {
    printf( "*******************************************************\n" );

    /* 局面　初期化 */
    ttt_initPosition( pPosition );
    ttt_printPosition( pPosition );
    
    checkGameOver = D_TTT_NOT_GAMEOVER;    
    while( checkGameOver != D_TTT_GAMEOVER ) {
      printf( "Please Input 1 to 9 : " );
      scanf( "%d", &inputPointTmp );
      inputPoint = inputPointTmp -1;
      
      /* 着手が有効か判定する */
      checkInvalidMove = ttt_isInvalidMove( pPosition, inputPoint );
      
      while ( checkInvalidMove != D_TTT_VALID ) {
	printf( "\n" );
	printf( "Invalid Input !\n" );
	printf( "Please Input 1 to 9 : " );
	scanf( "%d", &inputPointTmp );
	inputPoint = inputPointTmp -1;
	checkInvalidMove = ttt_isInvalidMove( pPosition, inputPoint );
      }

      /* 盤面を更新する */
      ttt_Move( pPosition, inputPoint );
      
      /* ゲームが終了したかを判定する */
      checkGameOverTmp = ttt_isGameOver( pPosition );
      checkGameOver = checkGameOverTmp & D_TTT_GAMEOVER;
      
      /* 手番を更新する */
      ttt_updateCurrentPlayer( pPosition );

      /* 盤面を表示する */
      ttt_printPosition( pPosition );
    }
    
    checkNoughtWin = checkGameOverTmp & D_TTT_NOUGHT_WIN;
    checkCrossWin = checkGameOverTmp & D_TTT_CROSS_WIN;
    
    printf( "\n\n" );
    if( checkNoughtWin == D_TTT_NOUGHT_WIN ) {
      printf( "o Win\n\n" );
    } else if( checkCrossWin == D_TTT_CROSS_WIN ) {
      printf( "x Win\n\n" );
    } else {
      printf( "Draw\n\n" );
    }

    printf( "*******************************************************\n\n" );
    /* タイトル画面 */
    printf( "Play Tic Tac Toe\n" );
    printf( "Input '0' -> Start, other -> Exit\n\n" );
    scanf( "%c", &checkContinue );
    getchar();
  }
  
  return 0;
}
