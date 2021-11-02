/*
ID: ssk49881
LANG: JAVA
TASK: speeding
*/

import java.io.*;
import java.util.*;

public class speeding {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("speeding.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("speeding.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int[] speedlimit = new int[100];
        int[] actualspeed = new int[100];
        int index = 0;
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int dist = Integer.parseInt(tokenizer.nextToken());
            int speed = Integer.parseInt(tokenizer.nextToken());
            int start = index;
            while (index < start + dist) {
                speedlimit[index] = speed;
                index++;
            }
        }
        index = 0;
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int dist = Integer.parseInt(tokenizer.nextToken());
            int speed = Integer.parseInt(tokenizer.nextToken());
            int start = index;
            while (index < start + dist) {
                actualspeed[index] = speed;
                index++;
            }
        }
        int maxSpeed = 0;
        for (int i = 0; i < 100; i++) {
            int diff = actualspeed[i] - speedlimit[i];
            if (diff > maxSpeed)
                maxSpeed = diff;
        }
        out.println(maxSpeed);

        in.close();
        out.close();
    }
}