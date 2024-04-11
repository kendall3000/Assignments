import java.util.ArrayList;
import java.util.List;

public class Button {
    private List<Light> observers = new ArrayList<>();

    public void addObserver(Light light) {
        observers.add(light);
    }

    public void removeObserver(Light light) {
        observers.remove(light);
    }

    public void press() {
        // Notify all observers when the button is pressed
        for (Light light : observers) {
            light.turnOn();
        }
    }
}
