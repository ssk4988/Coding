/*
ID: ssk49881
LANG: JAVA
TASK: evolution
*/

import java.io.*;
import java.util.*;

public class evolution {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("evolution.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("evolution.out")));

        int numPop = Integer.parseInt(in.readLine());
        ArrayList<String> attrList = new ArrayList<>();
        ArrayList<Integer>[] attr = new ArrayList[numPop];
        for (int i = 0; i < numPop; i++) {
            attr[i] = new ArrayList<>();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numattr = Integer.parseInt(tokenizer.nextToken());
            for (int j = 0; j < numattr; j++) {
                String k = tokenizer.nextToken();
                if (!attrList.contains(k)) {
                    attrList.add(k);
                }
                attr[i].add(attrList.indexOf(k));
            }
        }

        boolean works = true;
        for (int i = 0; i < attrList.size(); i++) {
            for (int j = 0; j < i; j++) {
                boolean yesyes = false;
                boolean noyes = false;
                boolean yesno = false;
                for (int k = 0; k < numPop; k++) {
                    if (attr[k].contains(i) && attr[k].contains(j)) {
                        yesyes = true;
                    }
                    if (!attr[k].contains(i) && attr[k].contains(j)) {
                        noyes = true;
                    }
                    if (attr[k].contains(i) && !attr[k].contains(j)) {
                        yesno = true;
                    }
                }
                if (noyes && yesyes && yesno) {
                    works = false;
                    // System.out.println(attrList.get(i) + " " + attrList.get(j));
                    break;
                }
            }
        }
        out.println(works ? "yes" : "no");

        in.close();
        out.close();
    }
}