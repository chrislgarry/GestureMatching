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

#endif /* HANDSHAKE_H */
