import java.io.*;
import java.util.*;

public class rectangle {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numCows = Integer.parseInt(in.readLine());
        ArrayList<Tuple> original = new ArrayList<>();
        int[] xvals = new int[numCows];
        int[] yvals = new int[numCows];
        long numSets = 1;
        for (int i = 0; i < numCows; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            xvals[i] = x;
            yvals[i] = y;
            Tuple t = new Tuple(x, y);
            original.add(t);
        }
        Arrays.sort(xvals);
        Arrays.sort(yvals);
        int[] x = new int[numCows];
        int[] y = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            Tuple t = original.get(i);
            t.x = Arrays.binarySearch(xvals, t.x);
            t.y = Arrays.binarySearch(yvals, t.y);
            x[t.y] = t.x;
            y[t.x] = t.y;
        }
        int[][] partialSums = new int[numCows][numCows];
        for (int i = 0; i < numCows; i++) {
            partialSums[i][y[i]] = 1;
        }
        for (int i = 0; i < numCows; i++) {
            for (int j = 0; j < numCows; j++) {
                if (i > 0) {
                    partialSums[i][j] += partialSums[i - 1][j];
                }
                if (j > 0) {
                    partialSums[i][j] += partialSums[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    partialSums[i][j] -= partialSums[i - 1][j - 1];
                }
            }
        }
        for (int i = 0; i < numCows; i++) {
            for (int j = 0; j <= i; j++) {
                int leftBound = Math.min(x[i], x[j]);
                int rightBound = Math.max(x[i], x[j]);
                long numLeft = partialSums[leftBound][i];
                ;
                if (j > 0) {
                    numLeft -= partialSums[leftBound][j - 1];
                }
                long numRight = partialSums[numCows - 1][i];
                if (j > 0) {
                    numRight -= partialSums[numCows - 1][j - 1];
                }
                if (rightBound > 0) {
                    numRight -= partialSums[rightBound - 1][i];
                }
                if (j > 0 && rightBound > 0) {
                    numRight += partialSums[rightBound - 1][j - 1];
                }
                numSets += numLeft * numRight;
            }
        }
        out.println(numSets);

        in.close();
        out.close();
    }

    public static class Tuple {
        int x;
        int y;

        public Tuple(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}