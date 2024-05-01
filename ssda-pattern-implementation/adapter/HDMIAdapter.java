// Adapter class to adapt HDMIPlug to VideoPlug interface
public class HDMIAdapter implements VideoPlug {
    private HDMIPlug hdmiPlug;

    // Constructor
    public HDMIAdapter(HDMIPlug hdmiPlug) {
        this.hdmiPlug = hdmiPlug;
    }

    // Implementing the display method of VideoPlug interface
    @Override
    public void display() {
        // Use HDMIPlug's digitalDisplay method
        hdmiPlug.digitalDisplay();
    }
}
