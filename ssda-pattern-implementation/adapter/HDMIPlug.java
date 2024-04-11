// DO NOT MODIFY THIS CLASS
// notice that this class does not implement VideoPlug

public class HDMIPlug {
	public int width = 1920;
	public int height = 1080;

	// constructor
	public HDMIPlug(){};

	// the actual method we want to run
	// notice it does not take the same parameters
	public digitalDisplay(){
		print "Displaying a " + width + " by " +
			height + " digital image!";
	}
}
