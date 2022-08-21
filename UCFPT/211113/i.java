/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int[] heroes = new int[n];
        int[] villains = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < n; i++){
            heroes[i] = Integer.parseInt(tokenizer.nextToken());
        }
        tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < n; i++){
            villains[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int[] beat = new int[n];
        int[] defeat = new int[n];
        int answer = 20000;
        for(int i = n - 1; i >= 0; i--){
            beat[i] = heroes[i] <= villains[i] ? villains[i] - heroes[i] + 1 : 0;
            defeat[i] = beat[i];
            if(i + 1 < n){
                defeat[i] = Math.min(defeat[i], Math.max(villains[i] > heroes[i] ? villains[i] - heroes[i] : 0, defeat[i+1]));
            }
            else{
                defeat[i] = Math.min(defeat[i], villains[i] > heroes[i] ? villains[i] - heroes[i] : 0);
            }
        }
        System.out.println(defeat[0]);
        in.close();
        out.close();
    }
}