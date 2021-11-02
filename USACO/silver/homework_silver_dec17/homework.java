/*
ID: ssk49881
LANG: JAVA
TASK: homework
*/

import java.io.*;
import java.util.*;

public class homework {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("homework.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("homework.out")));
        int numNums = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] nums = new int[numNums];
        for (int i = 0; i < numNums; i++) {
            nums[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int[] sums = new int[numNums];
        int[] mins = new int[numNums];
        sums[numNums - 1] = nums[numNums - 1];
        mins[numNums - 1] = nums[numNums - 1];
        for (int i = numNums - 2; i >= 0; i--) {
            sums[i] = sums[i + 1] + nums[i];
            mins[i] = Math.min(mins[i + 1], nums[i]);
        }
        double maxAvg = Double.MIN_VALUE;
        ArrayList<Integer> kvals = new ArrayList<>();
        for (int k = 1; k <= numNums - 2; k++) {
            double newD = (sums[k] - mins[k]) * 1.0 / (numNums - k - 1);
            // System.out.println(k + " " + " " + sums[k] + " " + mins[k] + " " + newD);
            if (newD > maxAvg) {
                maxAvg = newD;
                kvals = new ArrayList<>();
                kvals.add(k);
            } else if (newD == maxAvg) {
                kvals.add(k);
            }
        }
        Collections.sort(kvals);
        for (int k : kvals) {
            out.println(k);
        }

        in.close();
        out.close();
    }
}