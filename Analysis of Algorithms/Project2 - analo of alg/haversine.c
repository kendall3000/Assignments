/*#include <stdio.h>
#include <math.h>

double haversine(double lat1, double long1, double lat2, double long2)
{
	double radiusOfEarthInMiles = 3958.8;
	
	double degreesToRadians = M_PI / 180.0;
	
	//Convert degrees to radians:
	lat1 *= degreesToRadians;
	long1 *= degreesToRadians;
	lat2 *= degreesToRadians;
	long2 *= degreesToRadians;
	
	double a = pow(sin((lat2-lat1)/2), 2) + cos(lat1)*cos(lat2)*pow(sin((long2-long1)/2), 2);
	double c = 2*atan2(sqrt(a), sqrt(1-a));
	
	return radiusOfEarthInMiles*c;
}

int main(){
	
	double lat1 = 29.5827351;
	double long1 = -98.621094;

	double lat2 = 29.4259671;
	double long2 = -98.4883306;

	double dist = haversine(lat1,long1,lat2,long2);

	printf("The distance between UTSA Main campus: (%f,%f) and the Alamo: (%f,%f) is %f miles.\n",lat1,long1,lat2,long2,dist);
	
}
*/