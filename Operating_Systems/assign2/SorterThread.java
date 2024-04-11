import java.util.Arrays;
import java.util.Random;

public class SorterThread {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SorterThread <array_size>");
            return;
        }

        int arraySize = Integer.parseInt(args[0]);

        // Initialize random seed
        Random rand = new Random();

        // Allocate memory for the array
        double[] arr = new double[arraySize];

        // Generate random values for the array
        for (int i = 0; i < arraySize; i++) {
            arr[i] = rand.nextDouble() * 1000.0 + 1.0; // Random values between 1.0 and 1000.0
        }

        // Measure time when two threads are used
        long startTime = System.nanoTime();
        SortingThread thread1 = new SortingThread(arr, 0, arraySize / 2);
        SortingThread thread2 = new SortingThread(arr, arraySize / 2, arraySize);

        thread1.start();
        thread2.start();

        // Wait for sorting threads to finish
        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        long endTime = System.nanoTime();
        double elapsedTimeMillis = (endTime - startTime) / 1e6; // Convert to milliseconds

        /*  Calculate overall average
        double avg1 = thread1.getAverage();
        double avg2 = thread2.getAverage();
        double overallAvg = (avg1 + avg2) / 2.0;
        */
        // Print results for two threads
        System.out.println("Sorting is done in " + elapsedTimeMillis + "ms when two threads are used");

        // Measure time when one thread is used
        startTime = System.nanoTime();
        Arrays.sort(arr); // Use Arrays.sort to sort the entire array
        //double oneThreadAverage = Arrays.stream(arr).average().orElse(Double.NaN);

        endTime = System.nanoTime();
        elapsedTimeMillis = (endTime - startTime) / 1e6; // Convert to milliseconds

        // Print results for one thread
        System.out.println("Sorting is done in " + elapsedTimeMillis + "ms when one thread is used");
        //System.out.println("Overall Average: " + overallAvg);
        //System.out.println("Overall Average: " + oneThreadAverage);
    }
}

class SortingThread extends Thread {
    private double[] arr;
    private int startIndex;
    private int endIndex;
    private double average;

    public SortingThread(double[] arr, int startIndex, int endIndex) {
        this.arr = arr;
        this.startIndex = startIndex;
        this.endIndex = endIndex;
    }

    @Override
    public void run() {
        // Sort the subarray using insertion sort (you can change this to selection sort)
        insertionSort();

        // Calculate the average of the subarray
        double sum = 0.0;
        for (int i = startIndex; i < endIndex; i++) {
            sum += arr[i];
        }
        average = sum / (endIndex - startIndex);
    }

    public double getAverage() {
        return average;
    }

    private void insertionSort() {
        // Implement insertion sort here
        for (int i = startIndex + 1; i < endIndex; i++) {
            double key = arr[i];
            int j = i - 1;
            while (j >= startIndex && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
}
