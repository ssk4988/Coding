/*
ID: ssk49881
LANG: JAVA
TASK: angry
*/

import java.io.*;
import java.util.*;

public class angry {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("angry.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        int numBales = Integer.parseInt(in.readLine());
        int[] positions = new int[numBales];
        for (int i = 0; i < numBales; i++) {
            positions[i] = Integer.parseInt(in.readLine());
        }
        int answer = 0;
        for (int i = 0; i < numBales; i++) {
            int[] explodeTimes = new int[numBales];
            Arrays.fill(explodeTimes, -1);
            explodeTimes[i] = 1;
            int willExplode = 1;
            for (int t = 1; willExplode > 0; t++) {
                willExplode = 0;
                for (int j = 0; j < numBales; j++) {
                    if (explodeTimes[j] != t)
                        continue;
                    for (int k = 0; k < numBales; k++) {
                        if (explodeTimes[k] == -1 && Math.abs(positions[j] - positions[k]) <= t) {
                            explodeTimes[k] = t + 1;
                            willExplode++;
                        }
                    }
                }
            }
            int count = 0;
            for (int j = 0; j < numBales; j++) {
                if (explodeTimes[j] != -1)
                    count++;
            }
            answer = Math.max(answer, count);
        }
        out.println(answer);

        in.close();
        out.close();
    }
}