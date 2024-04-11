public class Logger {
    private static Logger instance;
    private StringBuilder log;

    // Private constructor to prevent instantiation from outside
    private Logger() {
        log = new StringBuilder();
    }

    // Public method to get the singleton instance
    public static Logger getInstance() {
        if (instance == null) {
            instance = new Logger();
        }
        return instance;
    }

    // Log something
    public void info(String information) {
        log.append(information);
    }

    // Method to get the log content
    public String getLog() {
        return log.toString();
    }
}
