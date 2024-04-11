// DO NOT MODIFY THIS CLASS - what if we need to use it elsewhere?
public class VGAPlug implements VideoPlug{

	// constructor
	public VGAPlug(){};
	
	public display(int width, int height){
		print "Displaying a " + width + " by " +
			height + " analog image!";
	}
}
