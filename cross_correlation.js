/*
* Author: Chris Garry
* Description:
*	Implements cross-correlation of series x and y as defined by
*
*							sigma_i[(x(i)-mean_x)*(y(i-d)-mean_y)]
*		r(d) =	-----------------------------------------------------------------
*				sqrt(sigma_i[(x(i)-mean_x)^2]) * sqrt(sigma_i[(y(i-d)-mean_y)^2])
*
* References: 
* 	http://paulbourke.net/miscellaneous/correlate/
*/


function InputException(message) {
   this.message = message;
   this.name = "InputException";
}

var cross_correlation=function(series_x, series_y) 
{	
	var sum_x; 
	var sum_y; 
	var mean_x;
	var mean_y;
	var length_x = series_x.length;
	var length_y = series_y.length;
	var sqr_series_x;
	var sqr_series_y;
	var cross_correlate = new Array();
	var delay_max = 2*length_x;

	//If time series of valid length.
		if((length_x!=0)&&(length_y!=0){
			
			//If series of different lengths, pad with zeros.
				var diff = length_x-length_y;

				if(diff>0){
					for(int x=0; x<diff; x++){
						series_y[length_y+x] = 0;
					}
				}

				if(diff<0){
					for(int x=0; x<diff; x++){
						series_x[length_x+x] = 0;
					}
					//Output size is relative to larger array of x,y
					delay_max = 2*length_y;
				}

			//Calculate sum of each series.
				for(int z = 0; z<length_x; z++){
					sum_x += series_x[z];
					sum_y += series_y[z];
				}

			//Calculate mean of each series.
				mean_x = sum_x/length_x;
				mean_y = sum_y/length_y;

			//Compute cross-correlate coefficients
				for(int delay = -delay_max; delay<delay_max; delay++){

					numerator = 0;
					sqr_series_x = 0;
					sqr_series_y = 0;

					for(int i =0; i<length_x; i++){

						//Skip cofficients with out of bound indicies
						var j = i + delay;
						if (j < 0 || j >= length_x){
							continue;
						}
						else{

						var term_1 = (series_x[i]-mean_x);
						var term_2 = (series_y[j]-mean_y);	
							numerator 	 += term_1*term_2;
							sqr_series_x += term_1*term_1;
							sqr_series_y += term_2*term_2;
						}

					}

					cross_correlate[delay] = numerator/Math.sqrt(sqr_series_x*sqr_series_y);
				}

			return cross_correlate;
	  	}

	//Invalid time series input
	  	else{
	  		throw new InputException("Inputs must be of non-zero length.");
	  	}
}