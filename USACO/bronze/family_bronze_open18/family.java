/*
ID: ssk49881
LANG: JAVA
TASK: family
*/

import java.io.*;
import java.util.*;

public class family {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("family.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("family.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numEntries = Integer.parseInt(tokenizer.nextToken());
        String target1 = tokenizer.nextToken();
        String target2 = tokenizer.nextToken();
        String relation = "";
        int numCows = numEntries + 1;
        ArrayList<String> cowIndex = new ArrayList<>();
        int[] parentOf = new int[numCows];
        Arrays.fill(parentOf, -1);
        ArrayList<Integer>[] childrenOf = new ArrayList[numCows];
        for (int i = 0; i < numCows; i++) {
            childrenOf[i] = new ArrayList<>();
        }

        for (int i = 0; i < numEntries; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            String cow1 = tokenizer.nextToken();
            String cow2 = tokenizer.nextToken();
            if (!cowIndex.contains(cow1))
                cowIndex.add(cow1);
            if (!cowIndex.contains(cow2))
                cowIndex.add(cow2);
            int cowindex1 = cowIndex.indexOf(cow1);
            int cowindex2 = cowIndex.indexOf(cow2);
            parentOf[cowindex2] = cowindex1;
            childrenOf[cowindex1].add(cowindex2);
        }

        int targetindex1 = cowIndex.indexOf(target1);
        int targetindex2 = cowIndex.indexOf(target2);

        relation = solve(targetindex1, targetindex2, parentOf, childrenOf, out);

        if (relation.equals("SIBLINGS"))
            out.println(relation);
        else if (!(relation.equals("COUSINS") || relation.equals("NOT RELATED"))) {
            out.println(target2 + " is the " + relation + " of " + target1);
        } else {
            relation = solve(targetindex2, targetindex1, parentOf, childrenOf, out);

            if (!(relation.equals("COUSINS") || relation.equals("NOT RELATED"))) {
                out.println(target1 + " is the " + relation + " of " + target2);
            } else {
                out.println(relation);
            }
        }

        in.close();
        out.close();
    }

    public static String solve(int targetindex1, int targetindex2, int[] parentOf, ArrayList<Integer>[] childrenOf,
            PrintWriter out) {
        String relation = "";
        int cowParent = parentOf[targetindex1];
        int numBack = 0;
        while (cowParent != targetindex2 && cowParent != -1 && parentOf[cowParent] != -1) {
            cowParent = parentOf[cowParent];
            numBack++;
        }
        if (cowParent == targetindex2) {
            while (numBack > 0) {
                if (numBack > 1) {
                    relation += "great-";
                } else {
                    relation += "grand-";
                }
                numBack--;
            }
            relation += "mother";
        }
        if (relation.length() == 0) {
            cowParent = parentOf[targetindex1];
            numBack = 0;
            while (cowParent != -1 && !childrenOf[cowParent].contains(targetindex2) && parentOf[cowParent] != -1) {
                cowParent = parentOf[cowParent];
                numBack++;
            }
            if (cowParent != -1 && childrenOf[cowParent].contains(targetindex2)) {
                if (numBack == 0)
                    relation = "SIBLINGS";
                else {
                    while (numBack > 1) {
                        relation += "great-";
                        numBack--;
                    }
                    relation += "aunt";
                }
            }
        }
        if (relation.length() == 0) {
            cowParent = parentOf[targetindex1];
            while (cowParent != -1 && parentOf[cowParent] != -1) {
                cowParent = parentOf[cowParent];
            }
            if (cowParent == -1)
                cowParent = targetindex1;
            ArrayList<Integer> tree = new ArrayList<>();
            ArrayList<Integer> queue = new ArrayList<>();
            queue.add(cowParent);
            while (!queue.isEmpty()) {
                int k = queue.remove(0);
                for (int j : childrenOf[k]) {
                    queue.add(j);
                }
                tree.add(k);
            }
            if (tree.contains(targetindex2))
                relation += "COUSINS";
            else
                relation += "NOT RELATED";
        }
        return relation;

    }
}