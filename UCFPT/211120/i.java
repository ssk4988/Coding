/*
ID: ssk49881
LANG: JAVA
TASK: i
*/

import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String input = in.readLine();
        int numWords = 1;
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == ' ') {
                numWords++;
            }
        }
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int lower = Integer.parseInt(tokenizer.nextToken());
        int higher = Integer.parseInt(tokenizer.nextToken());
        int[] prefix = new int[numWords + 1];
        int count = 1; // numwords+1
        for (int i = 0; i < input.length(); i++) {
            if (input.charAt(i) == ' ') {
                prefix[count++] = i;
            }
            if (i + 1 == input.length()) {
                prefix[count++] = i + 1;
            }
        }
        int[] lineEnds = new int[count + 1];
        for (int i = 0; i < lineEnds.length; i++) {
            lineEnds[i] = i;
        }
        for (int i = lower; i <= higher; i++) {
            int answer = prefix[1];
            while (lineEnds[0] < numWords && prefix[lineEnds[0] + 1] <= i) {
                lineEnds[0]++;
            }
            for (int j = 1; lineEnds[j - 1] < numWords; j++) {
                if (lineEnds[j] <= lineEnds[j - 1])
                    lineEnds[j] = lineEnds[j - 1] + 1;
                answer += prefix[lineEnds[j - 1] + 1] - prefix[lineEnds[j - 1]];
                while (lineEnds[j] < numWords && prefix[lineEnds[j] + 1] <= i + 1 + prefix[lineEnds[j - 1]])
                    lineEnds[j]++;
            }
            System.out.println(answer);
        }
        in.close();
        out.close();
    }
}