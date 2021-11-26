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
        int num = Integer.parseInt(in.readLine());
        outer: for(int i = 0; i < num; i++){
            String s = in.readLine();
            int a = Integer.parseInt(s);
            if(a % 2 == 0){
                System.out.println(0);
            }
            else{
                for(int j = 0; j < s.length(); j++){
                    int k = s.charAt(j) - '0';
                    if(k % 2 == 0){
                        if(j == 0) System.out.println(1);
                        else System.out.println(2);
                        continue outer;
                    }
                }
                System.out.println(-1);
            }
        }

        in.close();
        out.close();
    }
}