// Arup Guha
// 2/18/2015
// Solution to Mercer Problem #1: Cherry Blossom Counting

import java.util.*;

public class prob1 {

    public static void main(String[] args) {

        // Set up storate for blossoms.
        Scanner stdin = new Scanner(System.in);
        int numLocations = stdin.nextInt();
        int[] numBlossoms = new int[numLocations];

        // Read in number of blossoms at each location.
        for (int i=0; i<numLocations; i++)
            numBlossoms[i] = stdin.nextInt();

        // Calculate cumulative frequencies from left to right.
        int[] cumulativeFreq = new int[numLocations+1];
        cumulativeFreq[0] = 0;
        for (int i=1; i<=numLocations; i++)
            cumulativeFreq[i] = cumulativeFreq[i-1] + numBlossoms[i-1];

        // Process each query.
        int numQueries = stdin.nextInt();
        for (int loop=0; loop<numQueries; loop++) {

            // Get bounds.
            int start = stdin.nextInt();
            int end = stdin.nextInt();

            // Output the result by subtracting cumulative frequencies.
            System.out.println(cumulativeFreq[end] - cumulativeFreq[start-1]);
        }
    }
}
