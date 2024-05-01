public class Driver {
    public static void main(String[] args) {
        // create a button
        Button button = new Button();

        // create a red light
        Light redLight = new Light("red");
		// create a green light
        Light greenLight = new Light("green");
		// create a blue light
        Light blueLight = new Light("blue");


        // have the blue light and the red light listen for the button
        button.addObserver(redLight);
        button.addObserver(blueLight);

        // press the button. Blue and red light should call turnOn in response
		// NOTE: your Button class should be generic - do not hard-code these 
		// lights into the Button class.
        button.press();
    }
}
