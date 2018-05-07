#ifndef HANDSHAKE_H
#define HANDSHAKE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//XCORR
	//If handshakes are more than 0.85 correlated, match.
		#define XCORR_THRESH 0.50
	//Sizes of the query handshake(s).
		#define SERIES_X_SIZE 14
		#define SERIES_Y_SIZE 14
//DTW
	//If handshake is less than 140000 from model handshake, match.
		#define DTW_THRESH 140000
	//Dimension of the accelerometer data
		#define DIMENSION 3
	//Accelerometer batch size
		#define WINDOW_SIZE 14
	
		#define X 0
		#define Y 1
		#define Z 2
//Flags
		#define MATCH 1
		#define NO_MATCH 0

/*====================================================================
	Uses cross correlation to determine if two handshakes match 
	(i.e. >XCORR_THRESH correlated).
	
	Input: The primary axis (y axis) accelerometer data of each handshake.
	Output: 1 if handshakes match, 0 if not.
=====================================================================*/
	int handshake_match_xcorr(int *series_x, int *series_y);

/*====================================================================
	Uses Dynamic Time Warping to determine if two handshakes are a
	match (i.e. distance<DTW_THRESH).
	
	Input: Two sets of accelerometer data of size accel_data[14][3].
	Output: 1 if handshake, 0 if not.
=====================================================================*/
	int handshake_match_dtw(int **accel_data,int **accel_data_2);

/*====================================================================
	For allocating/deallocating matrix of n rows by 3 columns in size
====================================================================*/
	int** allocAccBuf(int len);
	void releaseAccBuf(int** p, int len);

#endif /* HANDSHAKE_H */
