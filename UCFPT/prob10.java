import java.io.*;
import java.util.*;

public class prob10 {
    public static int[] numSolutions = new int[10001];
    public static int counter = 0;
    public static int MAX_ELEMENT = 10;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());

        for (int i = 0; i < MAX_ELEMENT / 2; i++) {
            int[] start = new int[i + 1];
            for (int j = 0; j <= i; j++) {
                start[j] = 2 * j + 1;
            }
            System.out.println(Arrays.toString(start));

            check(start, 1, 0);
            System.out.println(counter);
            counter = 0;
        }
        for (int i = 0; i < n; i++) {
            int x = Integer.parseInt(in.readLine());
            System.out.println(numSolutions[x]);
        }

        in.close();
        // out.close();
    }

    public static void check(int[] test, int start, int index) {
        if (index == test.length) {
            counter++;
            int sum = 0;
            for (int i : test) {
                sum += i * i;
            }
            if (sum <= 10000) {
                numSolutions[sum]++;
            }
            System.out.println(Arrays.toString(test) + " counter: " + counter + " index: " + index + " start: " + start);
        }

        for (int i = index == 0 ? start : Math.max(start, test[index - 1] + 2); i <= MAX_ELEMENT
                && ((index == test.length - 1 && i <= MAX_ELEMENT)
                        || (index < test.length - 1 && test[index + 1] - test[index] >= 2)); i++) {
            test[index] = i;
            check(test, i + 1, index + 1);

            // test[i] = original + 1;
        }
    }
}