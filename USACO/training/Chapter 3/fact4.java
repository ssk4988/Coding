/*
ID: ssk49881
LANG: JAVA
TASK: fact4
*/

import java.io.*;
//import java.util.*;

public class fact4 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("fact4.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fact4.out")));
        int n = Integer.parseInt(in.readLine());
        int sto = 1;
        String stoString = Integer.toString(sto);
        for (int i = 1; i <= n; i++) {
            int mult = i;
            sto *= mult;
            while (sto % 10 == 0) {
                sto /= 10;
            }
            stoString = Integer.toString(sto);
            while (stoString.length() > 5) {
                stoString = stoString.substring(1);
            }
            sto = Integer.parseInt(stoString);
        }
        out.println(stoString.substring(stoString.length() - 1));

        in.close();
        out.close();
    }
}