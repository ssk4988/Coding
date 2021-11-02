/*
ID: ssk49881
LANG: JAVA
TASK: heritage
*/

import java.io.*;
import java.util.*;

public class heritage {
    public static String inorderStr;
    public static String preorderStr;
    public static int preorderIndex = 0;
    public static HashMap<String, node> nodesmap = new HashMap<String, node>();
    public static PrintWriter out;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("heritage.in"));
        out = new PrintWriter(new BufferedWriter(new FileWriter("heritage.out")));

        inorderStr = in.readLine();
        preorderStr = in.readLine();
        for (int i = 0; i < inorderStr.length(); i++) {
            nodesmap.put(inorderStr.substring(i, i + 1), new node());
        }
        String parentIndex = preorderStr.substring(0, 1);
        if (preorderIndex < preorderStr.length() - 1) {
            preorderIndex++;
            reconstruct(parentIndex, inorderStr);
        }
        traverse(parentIndex);
        out.println();
        in.close();
        out.close();
    }

    public static void reconstruct(String splitter, String str) {
        String next = preorderStr.substring(preorderIndex, preorderIndex + 1);
        String[] arr = str.split(splitter);
        for (int i = 0; i < arr.length; i++) {
            next = preorderStr.substring(preorderIndex, preorderIndex + 1);
            System.out.println(arr[i] + " " + next);
            if (arr[i].contains(next)) {
                nodesmap.get(splitter).children.add(next);
                if (preorderIndex < preorderStr.length() - 1) {
                    preorderIndex++;
                    reconstruct(next, arr[i]);
                }
            }
        }
    }

    public static void traverse(String index) {
        for (String newIndex : nodesmap.get(index).children) {
            traverse(newIndex);
        }
        out.print(index);
    }

    public static class node {
        public ArrayList<String> children = new ArrayList<>();
    }
}