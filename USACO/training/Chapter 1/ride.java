/*
ID: ssk49881
LANG: JAVA
TASK: ride
*/

import java.io.*;
import java.util.*;

public class ride {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("ride.in"));
        PrintWriter out = new PrintWriter(new File("ride.out"));
        char[] comet = in.nextLine().toCharArray();
        char[] group = in.nextLine().toCharArray();
        int cometprod = 1;
        int groupprod = 1;
        for(int i = 0; i < comet.length; i++){
            cometprod *= comet[i] - 'A' + 1;
        }
        for(int i = 0; i < group.length; i++){
            groupprod *= group[i] - 'A' + 1;
        }
        out.println(cometprod % 47 == groupprod % 47 ? "GO" : "STAY");
        in.close();
        out.close();
    }
}