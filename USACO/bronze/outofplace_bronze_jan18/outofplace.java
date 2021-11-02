/*
ID: ssk49881
LANG: JAVA
TASK: outofplace
*/

import java.io.*;
import java.util.*;

public class outofplace {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("outofplace.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("outofplace.out")));
        int numCows = Integer.parseInt(in.readLine());
        int[] cows = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            cows[i] = Integer.parseInt(in.readLine());
        }
        int bessIndex = -1;
        for (int i = 0; i < numCows; i++) {
            boolean matches = true;
            ArrayList<Integer> nums = new ArrayList<>();
            for (int j = 0; j < numCows; j++) {
                if (j == i)
                    continue;
                nums.add(cows[j]);
                if (nums.size() >= 2 && nums.get(nums.size() - 1) < nums.get(nums.size() - 2)) {
                    matches = false;
                }
            }
            if (matches) {
                bessIndex = i;
                break;
            }
        }

        boolean increase = false;
        if (bessIndex == 0)
            increase = true;
        else if (cows[bessIndex - 1] < cows[bessIndex])
            increase = true;
        // System.out.println(bessIndex + " " + increase);
        int answer = 0;
        ArrayList<Integer> seen = new ArrayList<>();
        if (increase) {

            for (int i = bessIndex + 1; i < numCows && cows[i] < cows[bessIndex]; i++) {
                if (!seen.contains(cows[i]))
                    seen.add(cows[i]);
            }

        } else {
            for (int i = bessIndex - 1; i >= 0 && cows[i] > cows[bessIndex]; i--) {
                if (!seen.contains(cows[i]))
                    seen.add(cows[i]);
            }
        }
        answer = seen.size();
        out.println(answer);
        in.close();
        out.close();
    }
}