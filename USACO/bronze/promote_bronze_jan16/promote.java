/*
ID: ssk49881
LANG: JAVA
TASK: promote
*/

import java.io.*;
import java.util.*;

public class promote {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("promote.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("promote.out")));
        
        int[] bronze = new int[2];
        int[] silver = new int[3];
        int[] gold = new int[3];
        int[] platinum = new int[3];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        bronze[0] = Integer.parseInt(tokenizer.nextToken());
        bronze[1] = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        silver[0] = Integer.parseInt(tokenizer.nextToken());
        silver[1] = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        gold[0] = Integer.parseInt(tokenizer.nextToken());
        gold[1] = Integer.parseInt(tokenizer.nextToken());
        tokenizer = new StringTokenizer(in.readLine());
        platinum[0] = Integer.parseInt(tokenizer.nextToken());
        platinum[1] = Integer.parseInt(tokenizer.nextToken());

        platinum[2] = platinum[1] - platinum[0];
        gold[2] = gold[1] - gold[0] + platinum[2];
        silver[2] = silver[1] - silver[0] + gold[2];
        out.println(silver[2]);
        out.println(gold[2]);
        out.println(platinum[2]);

        in.close();
        out.close();
    }
}