//  Modify this class so it uses the HDMIPlug's 
// digitalDisplay() implementation. Note that you 
// still must use a VidePlug (i.e., don't just replace
// plug with an HDMIPlug object.

public class VideoSocket {

    // Main method
    public main() {
        // Create an instance of HDMIPlug
        HDMIPlug hdmiPlug = new HDMIPlug();

        // Create an adapter instance using HDMIPlug
        HDMIAdapter adapter = new HDMIAdapter(hdmiPlug);

        // sse the VideoSocket with the adapter
        // plug MUST be of type VideoPlug
        VideoPlug plug = adapter; // Use the adapter instead of VGAPlug

        // call plug.display()
        plug.display();

        // use plug in a method which only takes objects 
		// of type VideoPlug (i.e., it can't take HDMIPlugs)
        // this line MUST be run on the plug
        someOtherClass.plugDiagnostic(plug);
    }
}
