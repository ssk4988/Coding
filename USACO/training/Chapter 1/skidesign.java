/*
ID: ssk49881
LANG: JAVA
TASK: skidesign
*/

import java.io.*;
import java.util.*;

public class skidesign {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("skidesign.in"));
        PrintWriter out = new PrintWriter(new File("skidesign.out"));
        int n = Integer.parseInt(in.nextLine());
        int[] hills = new int[n];

        for(int i = 0; i < n; i++){
            hills[i] = Integer.parseInt(in.nextLine());
        }
        Arrays.sort(hills);
        int range = hills[hills.length - 1] - hills[0];
        //System.out.println(range);
        int minCost = 100000000;
        if(range <= 17){
            out.println(0);
        }
        else{
            for(int i = hills[0]; i + 17 <= hills[hills.length - 1]; i++){
                int cost = getCost(hills, i);
                if(cost < minCost){
                    minCost = cost;
                }
            }
            out.println(minCost);
        }


        in.close();
        out.close();
    }

    public static int getCost(int[] hills, int minHeight){
        int cost = 0;
        for(int i = 0; i < hills.length; i++){
            if(hills[i] < minHeight){
                cost += Math.pow(minHeight - hills[i], 2);
            }
            if(hills[i] > minHeight + 17){
                cost += Math.pow(hills[i] - minHeight - 17, 2);
            }
        }
        return cost;
    }
}