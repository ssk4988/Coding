/*
ID: ssk49881
LANG: JAVA
TASK: prob6
*/

import java.io.*;
import java.util.*;

public class prob6 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String[] codes = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
                "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
        String line;
        while (!(line = in.readLine()).equals("#")) {
            int[] ways = new int[line.length() + 1];
            ways[0] = 1;
            for(int i = 0; i < ways.length; i++){
                for(int j = 1; j + i < ways.length; j++){
                    String s = line.substring(i, i + j);
                    boolean iscode = false;
                    for(String c : codes){
                        if(c.equals(s)){
                            iscode = true;
                        }
                    }
                    if(iscode){
                        ways[i + j] += ways[i];
                    }
                }
            }
            System.out.println(ways[ways.length - 1]);
        }
        in.close();
        out.close();
    }
}