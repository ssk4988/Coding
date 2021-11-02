/*
ID: ssk49881
LANG: JAVA
TASK: beads
*/

import java.io.*;
import java.util.*;

public class beads {
    public static void main(String[] args) throws Exception{
        Scanner in = new Scanner(new File("beads.in"));
        PrintWriter out = new PrintWriter(new File("beads.out"));
        int n = Integer.parseInt(in.nextLine());
        char[] beads = in.nextLine().toCharArray();
        int maxBeads = 0;
        for(int i = 0; i < beads.length; i++){
            int beadnum = getBeads(beads, i);
            maxBeads = beadnum > maxBeads ? beadnum : maxBeads;
        }
        out.println(Integer.toString(maxBeads));
        in.close();
        out.close();
    }
    public static int getBeads(char[] beads, int startindex){
        int numBeads = 0;
        int index = beads.length * 10 + startindex;
        char condition = beads[index % beads.length]; //false: blue, true: red
        int iterations = 0;
        int endindex = 0;
        while(condition == 'w' && iterations < beads.length){
            index++;
            iterations++;
            condition = beads[index % beads.length];
        }
        if (iterations >=beads.length){
            return beads.length;
        }
        iterations = 0;
        index = beads.length * 10 + startindex;
        while((beads[index % beads.length] == condition || beads[index % beads.length] == 'w') && iterations < beads.length){
            numBeads++;
            index++;
            iterations++;
        }
        endindex = index;
        if (iterations >=beads.length){
            return beads.length;
        }

        index = beads.length * 10 + startindex - 1;
        condition = beads[index % beads.length];
        while(condition == 'w' && iterations < beads.length){
            index--;
            condition = beads[index % beads.length];
        }
        if (iterations >=beads.length){
            return beads.length;
        }
        index = beads.length * 10 + startindex - 1;
        while((beads[index % beads.length] == condition || beads[index % beads.length] == 'w') && iterations < beads.length){
            numBeads++;
            index--;
            if(index % beads.length == (endindex - 1) % beads.length && iterations != 0){
                break;
            }
        }
        if (iterations >=beads.length){
            return beads.length;
        }

        return numBeads;
    }
}