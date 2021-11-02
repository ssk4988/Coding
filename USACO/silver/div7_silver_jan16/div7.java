/*
ID: ssk49881
LANG: JAVA
TASK: div7
*/

import java.io.*;
import java.util.*;

public class div7 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("div7.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
        int numNums = Integer.parseInt(in.readLine());
        int[] nums = new int[numNums];
        for (int i = 0; i < numNums; i++) {
            nums[i] = Integer.parseInt(in.readLine()) % 7;
        }
        int[] sums = new int[numNums];
        sums[0] = nums[0];
        for (int i = 1; i < numNums; i++) {
            sums[i] = (sums[i - 1] + nums[i]) % 7;
        }
        int[] start = new int[7];
        int[] end = new int[7];
        Arrays.fill(start, Integer.MAX_VALUE);
        Arrays.fill(end, Integer.MIN_VALUE);
        for (int i = 0; i < numNums; i++) {
            start[sums[i]] = Math.min(start[sums[i]], i);
            end[sums[i]] = Math.max(end[sums[i]], i);
        }
        int maxDist = 0;
        for (int i = 0; i < 7; i++) {
            if (start[i] <= numNums) {
                maxDist = Math.max(maxDist, end[i] - start[i]);
            }
        }
        out.println(maxDist);

        in.close();
        out.close();
    }
}