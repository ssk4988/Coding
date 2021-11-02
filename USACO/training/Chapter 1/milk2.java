/*
ID: ssk49881
LANG: JAVA
TASK: milk2
*/

import java.io.*;
import java.util.*;

public class milk2 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("milk2.in"));
        PrintWriter out = new PrintWriter(new File("milk2.out"));
        int n = Integer.parseInt(in.nextLine());
        String[] phrases = new String[n];
        int minTime = 100000000;
        int maxTime = 0;
        for (int i = 0; i < n; i++) {
            phrases[i] = in.nextLine();
            int start = Integer.parseInt(phrases[i].split(" ")[0]);
            int end = Integer.parseInt(phrases[i].split(" ")[1]);
            if (end > maxTime) {
                maxTime = end;
            }
            if (start < minTime) {
                minTime = start;
            }
        }
        boolean[] time = new boolean[maxTime];
        Arrays.fill(time, false);
        for (int i = 0; i < n; i++) {
            int start = Integer.parseInt(phrases[i].split(" ")[0]);
            int end = Integer.parseInt(phrases[i].split(" ")[1]);
            for (int j = start; j < end; j++) {
                if (!time[j]) {
                    time[j] = true;
                }
            }
        }
        int maxNone = 0;
        int maxSome = 0;
        int noneCount = 0;
        int someCount = 0;
        for (int i = minTime; i < maxTime; i++) {
            if (!time[i]) {
                if (someCount > maxSome) {
                    maxSome = someCount;
                }
                someCount = 0;
                noneCount++;
            } else {
                if (noneCount > maxNone) {
                    maxNone = noneCount;
                }
                noneCount = 0;
                someCount++;
            }
            if (i == maxTime - 1) {
                maxSome = someCount > maxSome ? someCount : maxSome;
                maxNone = noneCount > maxNone ? noneCount : maxNone;
            }
        }
        out.println(Integer.toString(maxSome) + " " + Integer.toString(maxNone));
        in.close();
        out.close();
    }
}