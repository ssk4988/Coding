/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class race {
    public static int[][] steps;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("race.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("race.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numMeters = Integer.parseInt(tokenizer.nextToken());
        int numVals = Integer.parseInt(tokenizer.nextToken());
        for(int i = 0; i < numVals; i++){
            int val = Integer.parseInt(in.readLine());
            out.println(solve(numMeters, val));
        }
        in.close();
        out.close();
    }
    public static int solve(int dist, int endspeed){
        int rhs = 0;
        int lhs = 0;
        int time = 0;
        for(int speed = 1; ;speed++){
            lhs += speed;
            time++;
            if(lhs + rhs >= dist) return time;
            if(speed >= endspeed){
                rhs += speed;
                time++;
                if(lhs + rhs >= dist) return time;
            }
        }
    }
}