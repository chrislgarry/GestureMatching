/*
	Author: Chris Garry, chrislgarry AT gmail DOT com
	
	Description:
		The following code implements a handshake matching algorithm
    using cross correlation given accelerometer data from a Pebble Smart
		Watch. 

	License:

		This code is for education purposes only.

		Reference for cross_correlation():
			Paul Bourke, August 1996, Cross Correlation, AutoCorrelation -- 2D Pattern Identification 
			http://paulbourke.net/miscellaneous/correlate/
*/

#include "handshake.h"

//HELPER FUNCTIONS==========================================================================
	
	//Computes the cross correlation coefficients for series_x and series_y
	double *cross_correlation(int *series_x, int *series_y){	

		double sum_x = 0.0;
		double sum_y = 0.0;
		double mean_x = 0.0;
		double mean_y = 0.0;
		int delay_max = SERIES_X_SIZE;
		double *cross_correlate = (double*)malloc(((delay_max*2)+1)*sizeof(double));

		//Calculate the sum of each series
			int z;
			for(z = 0; z<SERIES_X_SIZE; z++){
				sum_x += series_x[z];
				sum_y += series_y[z];
			}

		//Calculate mean of each series.
			mean_x = sum_x/SERIES_X_SIZE;
			mean_y = sum_y/SERIES_Y_SIZE;

		//Compute cross-correlate coefficients
			double term_1, term_2, numerator;
			double sqr_series_x = 0.0;
			double sqr_series_y = 0.0;
			int delay, i;
			for(delay = -delay_max; delay<=delay_max; delay++){

				numerator = 0;
				sqr_series_x = 0;
				sqr_series_y = 0;

				for(i =0; i<SERIES_X_SIZE; i++){

					//Assume cofficients with out of bound indicies have x[i]=0, y[i]=0
					int j = i - delay;
					if (j < 0 || j >= SERIES_X_SIZE){
						term_1 = (series_x[i]-mean_x);
						term_2 = (-1*mean_y);	
						numerator += term_1*term_2;
						sqr_series_x += term_1*term_1;
						sqr_series_y += term_2*term_2;			
					}
					else{
						term_1 = (series_x[i]-mean_x);
						term_2 = (series_y[j]-mean_y);	
						numerator += term_1*term_2;
						sqr_series_x += term_1*term_1;
						sqr_series_y += term_2*term_2;
					}

				}

				cross_correlate[delay+delay_max] = numerator/sqrt(sqr_series_x*sqr_series_y);
				printf("delay:%d correlate:%f\n",delay, cross_correlate[delay+delay_max]);
			}

		return cross_correlate;
	}
    
//END HELPER FUNCTIONS======================================================================


//LIBRARY FUNCTIONS=========================================================================
	int handshake_match_xcorr(int *series_x, int *series_y){

		//Compute the cross correlation coefficients
			double *coefficients = cross_correlation(series_x,series_y);

		//Determine if a correlation coefficient >XCORR_THRESH exists.
			int i;
			for(i=0; i<SERIES_X_SIZE*2; i++){
				if(fabs(coefficients[i]) > XCORR_THRESH){
					return MATCH;
				}
			}

		return NO_MATCH;
	}
//END LIBRARY FUNCTIONS=====================================================================


//TEST======================================================================================
	int main(){

		//TEST XCORR==============================================================
			int test_xcorr_1[14] = {-1020,-1774,-972,34,294,-498,-1796,-1034,432,-1144,-1892,-1482,-508,-1176};
			int test_xcorr_2[14] = {-1014,-1166,-920,64,148,-734,-1024,-1012,-1856,366,-1842,-1330,-108,-1746};

		    if(handshake_match_xcorr(test_xcorr_1, test_xcorr_2)){
		    	printf("\nXCORR RESULT: MATCH.\n");
		    }
		    else{
		    	printf("\nXCORR RESULT: NO MATCH.\n");
		    }

		return 0;
	 }
