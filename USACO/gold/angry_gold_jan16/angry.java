/*
ID: ssk49881
LANG: JAVA
TASK: angry
*/

import java.io.*;
import java.util.*;

public class angry {
    public static ArrayList<Integer> bales = new ArrayList<>();
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("1.in"));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("angry.out")));
        int numCows = Integer.parseInt(in.readLine());
        for(int i = 0; i < numCows; i++){
            bales.add(Integer.parseInt(in.readLine()));
        }

        in.close();
        //out.close();
    }
}