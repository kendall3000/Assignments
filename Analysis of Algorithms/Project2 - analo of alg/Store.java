//Dr. Gibson-Lopez' Store.java implementation.
//Providing mainly for the Haversine formula code.
//If coding in Java, you can use this implementation if you'd like, or you can use your own.


public class Store {

	public String id;
	public String address;
	public String city;
	public String state;
	public String zipCode;
	public double latitude;
	public double longitude;
	public double distance;
	
	public Store(String theID, String theAddress, String theCity, String theState, String theZip, double theLat, double theLong) {
		
		id = theID;
		address = theAddress;
		city = theCity;
		state = theState;
		zipCode = theZip;
		latitude = theLat;
		longitude = theLong;
		distance = -1;
	}
	
	public void computeDistance(double otherLat, double otherLong) {
		
		//Haversine Formula
		double radiusOfEarthInMiles = 3958.8;
		
		//First we convert the latitudes and longitudes to radians.
		double lat1 = Math.toRadians(latitude);
		double lat2 = Math.toRadians(otherLat);
		double long1 = Math.toRadians(longitude);
		double long2 = Math.toRadians(otherLong);
		
		//Then we can apply the Haversine Formula to get the distance in miles.
		double a = Math.pow(Math.sin((lat2-lat1)/2), 2) + Math.cos(lat1)*Math.cos(lat2)*Math.pow(Math.sin((long2-long1)/2), 2);
		double c = 2*Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
		distance = radiusOfEarthInMiles*c;
		
	}
	
	public String toString() {
		
		return "Store #" + id + ". " + address + ", " + city + ", " + state + ", " + zipCode + ".";
	}
}
