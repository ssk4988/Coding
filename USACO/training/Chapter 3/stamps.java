/*
ID: ssk49881
LANG: JAVA
TASK: stamps
*/

import java.io.*;
import java.util.*;

public class stamps {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("stamps.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("stamps.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int maxStamps = Integer.parseInt(tokenizer.nextToken());
        int numStamps = Integer.parseInt(tokenizer.nextToken());
        System.out.println(numStamps);
        ArrayList<Integer> stamps = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            tokenizer = new StringTokenizer(line);
            while (tokenizer.hasMoreTokens()) {
                stamps.add(Integer.parseInt(tokenizer.nextToken()));
            }
        }
        Collections.sort(stamps);
        int[] stampsNeeded = new int[maxStamps * stamps.get(stamps.size() - 1) + 2];
        Arrays.fill(stampsNeeded, Integer.MAX_VALUE);
        stampsNeeded[0] = 0;
        int i = 1;
        while (stampsNeeded[i - 1] <= maxStamps && i < stampsNeeded.length) {
            if (stamps.contains(i)) {
                stampsNeeded[i] = 1;
            } else {
                for (int j = 0; j < stamps.size(); j++) {
                    if (stamps.get(j) <= i && stampsNeeded[i - stamps.get(j)] + 1 < stampsNeeded[i]) {
                        stampsNeeded[i] = stampsNeeded[i - stamps.get(j)] + 1;
                    }
                }
            }
            if (i % 10000 == 0) {
                System.out.println(i);
            }
            i++;
        }
        out.println(i - 2);

        in.close();
        out.close();
    }
}