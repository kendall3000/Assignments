public class Light {
    private String color;

    public Light(String color) {
        this.color = color;
    }

    public void turnOn() {
        // light turns on with specified color for 1 second
        System.out.println("Turning on " + color + " light");
    }
}
