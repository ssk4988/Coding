/*
ID: ssk49881
LANG: JAVA
TASK: planting
*/

import java.io.*;
import java.util.*;

public class planting {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("planting.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("planting.out")));

        int numFarms = Integer.parseInt(in.readLine());
        ArrayList<Integer>[] connected = new ArrayList[numFarms];
        for(int i = 0; i < numFarms; i++){
            connected[i] = new ArrayList<>();
        }
        for(int i = 0; i < numFarms - 1; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int num1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int num2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            connected[num1].add(num2);
            connected[num2].add(num1);
        }
        int max = Integer.MIN_VALUE;
        for(int i = 0; i < numFarms; i++){
            TreeSet<Integer> neighbors = new TreeSet<>();
            for(int j : connected[i]){
                neighbors.add(j);
            }
            //System.out.println(i + " " + neighbors.size());
            if(neighbors.size() > max) max = neighbors.size();
        }
        out.println(max + 1);

        in.close();
        out.close();
    }
}