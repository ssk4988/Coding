/*
ID: ssk49881
LANG: JAVA
TASK: prob7
*/

import java.io.*;
import java.util.*;

public class prob7 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int currentTime = Integer.parseInt(tokenizer.nextToken());
        int capacity = Integer.parseInt(tokenizer.nextToken());
        int numFlips = Integer.parseInt(tokenizer.nextToken());
        int[] flips = new int[numFlips + 1];
        tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < numFlips; i++){
            flips[i] = Integer.parseInt(tokenizer.nextToken());
        }
        flips[flips.length - 1] = currentTime;
        int bottom = capacity;
        int top = 0;
        int now = 0;
        for(int i = 0; i < flips.length; i++){
            int elapsed = flips[i] - now;
            bottom += top - Math.max(0, top - elapsed);
            top = Math.max(0, top - elapsed);
            now = flips[i];
            if(i < flips.length - 1){
               int tmp = bottom;
            bottom = top;
            top = tmp; 
            }
        }
        System.out.println(top);


        in.close();
        out.close();
    }
}