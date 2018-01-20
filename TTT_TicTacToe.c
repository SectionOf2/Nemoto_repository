/*------------------------------------------------------------------------------*/
/*                                                                              */
/*      �R���|�[�l���g�� : TTT	 	        	                        */
/*                                                                              */
/*      �t�@�C���� : TTT_TicTacToe.c			                        */
/*                                                                              */
/*	�@�\�T�v �F �}���o�c�Q�[��				   		        */
/*                                                                              */
/*------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "TTT_TicTacToe_in.h"



/*------------------------------------------------------------------------------*/
/*	�@ �\  	�ǖʃf�[�^������							*/
/*									       	*/
/*	������	TTT_Position_T *position �ǖʃf�[�^�|�C���^			*/
/*	�߂�l 	�Ȃ�								*/
/*------------------------------------------------------------------------------*/
static void ttt_initPosition( TTT_Position_T *position )
{
  U1 count;	/* �J�E���^ */

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
/*	�@ �\  	�Ֆʕ\��								*/
/*									       	*/
/*	������	const TTT_Position_T *position �ǖʃf�[�^�|�C���^      		*/
/*	�߂�l 	�Ȃ�								*/
/*------------------------------------------------------------------------------*/
static void ttt_printPosition( const TTT_Position_T *position )
{
  U1 rowCount;	/* �s�J�E���^ */
  U1 columnCount;	/* ��J�E���^ */

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
	  /* �����Ȃ� */
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
/*	�@ �\  	�L�����蔻��							*/
/*									       	*/
/*	������	const TTT_Position_T *position �ǖʃf�[�^�|�C���^		       	*/
/*		U1 point ���[�U�����͂�������					*/
/*	�߂�l 	U1�@����L�����茋��						*/
/*------------------------------------------------------------------------------*/
static U1 ttt_isInvalidMove( const TTT_Position_T *position, U1 point )
{
   U1 ret;	/* �߂�l */ 

   /* ������ */
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
/*	�@ �\  	���[�U�̓��͂����ʒu�ɒ��肵�A�ՖʁA�萔���X�V				*/
/*									       	*/
/*	������	TTT_Position_T *position �ǖʃf�[�^�|�C���^		       	*/
/*		U1 point ���[�U�����͂�������					*/
/*	�߂�l 	�Ȃ�								*/
/*------------------------------------------------------------------------------*/
static void ttt_Move( TTT_Position_T *position, U1 point )
{
  U2 bitTmp;	/* �r�b�g�{�[�h�X�V�p�ϐ� */

  /* ������ */
  bitTmp = 0x8000;	/* 1000 0000 0000 0000 */

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    if( position->currentPlayer == D_TTT_NOUGHT_PLAYER ) {	  /* �}���̎�� */
      position->board[point] = D_TTT_BOARD_NOUGHT;
      
      /* �r�b�g�{�[�h�̍X�V */
      if( point > D_TTT_BOARD_MIN_POINT ) {
	bitTmp >>= point;
      }
      position->bitboard[D_TTT_NOUGHT_BITBOARD] |= bitTmp;
    } else if( position->currentPlayer == D_TTT_CROSS_PLAYER ) {	  /* �o�c�̎�� */
      position->board[point] = D_TTT_BOARD_CROSS;

      /* �r�b�g�{�[�h�̍X�V */
      if( point > D_TTT_BOARD_MIN_POINT ) {
	bitTmp >>= point;
      }
      position->bitboard[D_TTT_CROSS_BITBOARD] |= bitTmp;
    } else {
      /* �����Ȃ� */
    }
    
    position->turns++; 
  }
}



/*------------------------------------------------------------------------------*/
/*	�@ �\  	�r�b�g�}�X�N(�Q�[���I������A���s����)�쐬				*/
/*									       	*/
/*	������	const TTT_Position_T *position �ǖʃf�[�^�|�C���^			*/
/*	�߂�l 	U1 �r�b�g�}�X�N(�Q�[���I������A���s����)				*/
/*------------------------------------------------------------------------------*/
static  U1 ttt_isGameOver( const TTT_Position_T *position )
{
  U2 checkLine[D_TTT_LINE_SIZE] = { D_TTT_ROW_1, D_TTT_ROW_2, D_TTT_ROW_3,
		     		   D_TTT_COLUMN_1, D_TTT_COLUMN_2, D_TTT_COLUMN_3,
  		     		   D_TTT_SLANTING_1, D_TTT_SLANTING_2 };	/* ���s����p */
  U1 currentPlayer;	/* ��� */
  U2 bitwiseOperationResult;	/* �r�b�g���Z���� */
  U1 lineCount;	/* �J�E���^ */
  U1 ret;	/* �߂�l */

  /* ������ */
  currentPlayer = position->currentPlayer;
  bitwiseOperationResult = 0;
  lineCount = 0;
  ret = D_TTT_NOT_GAMEOVER;

  if ( position == NULL ) {
    exit(EXIT_FAILURE);
  } else {
    for( lineCount = 0; lineCount < D_TTT_LINE_SIZE; lineCount++ ) {
      bitwiseOperationResult = position->bitboard[currentPlayer] & checkLine[lineCount];
      
      /* ���s�������ꍇ�A�߂�l���X�V���� */
      if( bitwiseOperationResult == checkLine[lineCount] ) {
	ret |= D_TTT_GAMEOVER;
	
	if( currentPlayer == D_TTT_NOUGHT_PLAYER ) {
	  ret |= D_TTT_NOUGHT_WIN;
	} else if( currentPlayer == D_TTT_CROSS_PLAYER ) {
	  ret |= D_TTT_CROSS_WIN;
	} else {
	  /* �����Ȃ� */
	}
	
	/* for�����甲���� */
	break;
      }
    }
    
    /* �c���΂߂�"o" or "x"��3����ł��Ȃ��@���@�ő�萔(9��)�ɒB�����ꍇ�A���������ŃQ�[���I���Ƃ��� */
    if( ( ret == 0 ) && ( position->turns == D_TTT_MAX_TURNS ) ) {
      ret |= D_TTT_GAMEOVER;
    }
  }
  
  return ret;
}



/*------------------------------------------------------------------------------*/
/*	�@ �\  	��ԍX�V								*/
/*									       	*/
/*	������	TTT_Position_T *position �ǖʃf�[�^�|�C���^			*/
/*	�߂�l 	�Ȃ�								*/
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
      /* �����Ȃ� */
    }
  }
}



/*------------------------------------------------------------------------------*/
/*	�@ �\  	�}���o�c�Q�[�������s						*/
/*									       	*/
/*	������	�Ȃ�								*/
/*	�߂�l 	U1 0								*/
/*------------------------------------------------------------------------------*/
U1 main( void )
{
  TTT_Position_T position;	/* �ǖ� */
  TTT_Position_T *pPosition;	/* �ǖʃ|�C���^ */
  U1 inputPointTmp;	/* ���[�U�̓��͂������� */
  U1 inputPoint;	/* ���[�U�̓��͂�������-1 */
  U1 checkInvalidMove;	/* ����̗L���t���O */
  U1 checkGameOverTmp;	/* �I������A���s����p�r�b�g�}�X�N */
  U1 checkGameOver;	/* �I������ */
  U1 checkNoughtWin;	/* �}���@�������� */
  U1 checkCrossWin;	/* �o�c�@�������� */
  C1 checkContinue;	/* �Q�[���J�n���� */
    
  /* ������ */
  pPosition = &position;

  /* �^�C�g����� */
  printf( "Play Tic Tac Toe\n" );
  printf( "Input '0' -> Start, other -> Exit\n\n" );
  scanf( "%c", &checkContinue );
  getchar();
  
  while( checkContinue -'0' ==  D_TTT_PLAY_TIC_TAC_TOE ) {
    printf( "*******************************************************\n" );

    /* �ǖʁ@������ */
    ttt_initPosition( pPosition );
    ttt_printPosition( pPosition );
    
    checkGameOver = D_TTT_NOT_GAMEOVER;    
    while( checkGameOver != D_TTT_GAMEOVER ) {
      printf( "Please Input 1 to 9 : " );
      scanf( "%d", &inputPointTmp );
      inputPoint = inputPointTmp -1;
      
      /* ���肪�L�������肷�� */
      checkInvalidMove = ttt_isInvalidMove( pPosition, inputPoint );
      
      while ( checkInvalidMove != D_TTT_VALID ) {
	printf( "\n" );
	printf( "Invalid Input !\n" );
	printf( "Please Input 1 to 9 : " );
	scanf( "%d", &inputPointTmp );
	inputPoint = inputPointTmp -1;
	checkInvalidMove = ttt_isInvalidMove( pPosition, inputPoint );
      }

      /* �Ֆʂ��X�V���� */
      ttt_Move( pPosition, inputPoint );
      
      /* �Q�[�����I���������𔻒肷�� */
      checkGameOverTmp = ttt_isGameOver( pPosition );
      checkGameOver = checkGameOverTmp & D_TTT_GAMEOVER;
      
      /* ��Ԃ��X�V���� */
      ttt_updateCurrentPlayer( pPosition );

      /* �Ֆʂ�\������ */
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
    /* �^�C�g����� */
    printf( "Play Tic Tac Toe\n" );
    printf( "Input '0' -> Start, other -> Exit\n\n" );
    scanf( "%c", &checkContinue );
    getchar();
  }
  
  return 0;
}
