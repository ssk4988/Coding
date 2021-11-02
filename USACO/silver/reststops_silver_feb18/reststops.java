/*
ID: ssk49881
LANG: JAVA
TASK: reststops
*/

import java.io.*;
import java.util.*;

public class reststops {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("reststops.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("reststops.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int totalDistance = Integer.parseInt(tokenizer.nextToken());
        int numRestStops = Integer.parseInt(tokenizer.nextToken());
        long farmerSpeed = Integer.parseInt(tokenizer.nextToken());
        long cowSpeed = Integer.parseInt(tokenizer.nextToken());

        long[] positions = new long[numRestStops];
        long[] tastiness = new long[numRestStops];

        for (int i = 0; i < numRestStops; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            positions[i] = Integer.parseInt(tokenizer.nextToken());
            tastiness[i] = Integer.parseInt(tokenizer.nextToken());
        }

        long totalTastiness = 0;
        long currentPos = 0;

        while (currentPos < totalDistance) {
            int maxIndex = -1;
            long maxTasty = Long.MIN_VALUE;
            for (int i = 0; i < numRestStops; i++) {
                if (positions[i] <= currentPos) {
                    continue;
                }
                if (tastiness[i] > maxTasty) {
                    maxIndex = i;
                    maxTasty = tastiness[i];
                }
            }
            if (maxIndex == -1)
                break;
            // System.out.println(currentPos + " " + totalTastiness + " " + maxIndex);
            long timeToEat = (farmerSpeed - cowSpeed) * (positions[maxIndex] - currentPos);
            totalTastiness += timeToEat * maxTasty;
            currentPos = positions[maxIndex];
        }
        out.println(totalTastiness);

        in.close();
        out.close();
    }

}