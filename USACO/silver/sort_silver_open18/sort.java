/*
ID: ssk49881
LANG: JAVA
TASK: sort
*/

import java.io.*;
import java.util.*;

public class sort {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("sort.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        int numEntries = Integer.parseInt(in.readLine());
        Tuple[] arr = new Tuple[numEntries];
        for (int i = 0; i < numEntries; i++) {
            arr[i] = new Tuple(i, Integer.parseInt(in.readLine()));
        }
        Arrays.sort(arr);
        int maxNum = 0;
        for (int i = 0; i < numEntries; i++) {
            maxNum = Math.max(maxNum, arr[i].index - i);
        }
        maxNum++;
        out.println(maxNum);

        in.close();
        out.close();
    }

    public static class Tuple implements Comparable<Tuple> {
        int index;
        int value;

        public Tuple(int index, int value) {
            this.index = index;
            this.value = value;
        }

        @Override
        public int compareTo(sort.Tuple o) {
            if (this.value - o.value == 0) {
                return this.index - o.index;
            }
            return this.value - o.value;
        }
    }
}