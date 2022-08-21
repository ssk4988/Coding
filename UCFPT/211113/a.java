/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int count = 0; count < numcases; count++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int[] nums = new int[15];
            int casenum = Integer.parseInt(tokenizer.nextToken());
            for(int i = 0; i < 15; i++){
                nums[i] = Integer.parseInt(tokenizer.nextToken());
            }
            int answers = 0;
            for(int i = 1; i < 14; i++){
                for(int j = 0; i + j < 14; j++){
                    int min = Math.max(nums[i-1], nums[i+j+1]);
                    boolean works = true;
                    for(int k = i; k <= i + j; k++){
                        if(nums[k] <= min){
                            works = false;
                        }
                        
                    }
                    if(works) answers++;
                }
            }
            System.out.printf("%d %d%n", casenum, answers);
        }


        in.close();
        out.close();
    }
}