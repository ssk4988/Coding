/*
ID: ssk49881
LANG: JAVA
TASK: factory
*/

import java.io.*;
import java.util.*;

public class factory {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("factory.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("factory.out")));
        int numPoints = Integer.parseInt(in.readLine());
        ArrayList<Integer>[] children = new ArrayList[numPoints];
        for (int i = 0; i < numPoints; i++) {
            children[i] = new ArrayList<>();
        }
        for (int i = 0; i < numPoints - 1; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int parent = Integer.parseInt(tokenizer.nextToken()) - 1;
            int child = Integer.parseInt(tokenizer.nextToken()) - 1;
            children[parent].add(child);
        }
        int answer = -1;
        for (int i = 0; i < numPoints; i++) {
            if (children[i].size() == 0) {
                // System.out.println(list.size());
                if(answer == -1) answer = i + 1;
                else{
                    answer = -1;
                    break;
                }
            }
        }
        out.println(answer);

        in.close();
        out.close();
    }
}