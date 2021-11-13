/*
ID: ssk49881
LANG: JAVA
TASK: prob2
*/

import java.io.*;
import java.util.*;

public class prob2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        for(int i = 0; i < n; i++){
            int snow = Integer.parseInt(in.readLine());
            int ft = snow / 12;
            int inch = snow % 12;
            int rn = snow / 10;
            out.println(ft + " feet, " + inch + " inches of snow is the equivalent of " + rn + " inches of rain");
        }
        in.close();
        out.close();
    }
}