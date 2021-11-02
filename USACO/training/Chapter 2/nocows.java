/*
ID: ssk49881
LANG: JAVA
TASK: nocows
*/

import java.io.*;
import java.util.*;

public class nocows {
    public static long[][] numExpansions;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("nocows.in"));
        PrintWriter out = new PrintWriter(new File("nocows.out"));
        String phrase = in.nextLine();
        int numNodes = Integer.parseInt(phrase.split(" ")[0]);
        int height = Integer.parseInt(phrase.split(" ")[1]);
        numExpansions = new long[101][201]; // depth of subtree (not including root), nodes left to add(not including
                                            // top
                                            // node)
        for (long[] arr : numExpansions) {
            Arrays.fill(arr, -1);
        }
        // numExpansions[0][0] = 1;
        // numExpansions[1][2] = 1;
        numExpansions[1][1] = 1;
        numExpansions[2][3] = 1;
        out.println(expand(height, numNodes) % 9901);
        // System.out.println(dfs(height - 1, numNodes - 1));
        if (numNodes % 2 == 0 || (numNodes - 1) / 2 < (height - 1)) {
            System.out.println(0);
        }
        in.close();
        out.close();
    }

    public static long expand(int depth, int nodes) {
        if (nodes % 2 == 0) {
            numExpansions[depth][nodes] = 0;
            return 0;
        }
        if (numExpansions[depth][nodes] != -1) {
            return numExpansions[depth][nodes];
        }
        if (nodes >= Math.pow(2, depth) || nodes < 2 * depth - 1) {
            numExpansions[depth][nodes] = 0;
            return 0;
        }
        if (depth == 0 || nodes == 0) {
            numExpansions[depth][nodes] = 0;
            return 0;
        }
        if (depth == 1 || nodes == 1) {
            numExpansions[depth][nodes] = 0;
            return 0;
        }
        long sum = 0;
        for (int i = 1; i < nodes - 1; i++) {
            int j = nodes - 1 - i;
            for (int idepth = Math.max(1, (int) (Math.log(i) / Math.log(2) + 1)); idepth <= Math.min(depth - 1,
                    (i + 1) / 2); idepth++) {
                int jdepth = depth - 1;
                if (numExpansions[idepth][i] == -1) {
                    numExpansions[idepth][i] = expand(idepth, i);
                }
                if (numExpansions[jdepth][j] == -1) {
                    numExpansions[jdepth][j] = expand(jdepth, j);
                }
                sum += numExpansions[idepth][i] * numExpansions[jdepth][j];
            }
            for (int jdepth = Math.max(1, (int) (Math.log(j) / Math.log(2) + 1)); jdepth <= Math.min(depth - 1,
                    (j + 1) / 2); jdepth++) {
                if (jdepth == depth - 1) {
                    continue;
                }
                int idepth = depth - 1;
                if (numExpansions[idepth][i] == -1) {
                    numExpansions[idepth][i] = expand(idepth, i);
                }
                if (numExpansions[jdepth][j] == -1) {
                    numExpansions[jdepth][j] = expand(jdepth, j);
                }
                sum += numExpansions[idepth][i] * numExpansions[jdepth][j];
            }
        }
        numExpansions[depth][nodes] = sum;
        numExpansions[depth][nodes] %= 9901;
        return numExpansions[depth][nodes];
    }

    public static long dfs(int depth, int nodes) {
        if (nodes < 2 * depth || nodes > Math.pow(2, depth + 1) - 2) {
            return 0;
        }
        if (numExpansions[depth][nodes] != -1) {
            return numExpansions[depth][nodes];
        }

        if (depth == 0 || nodes == 0) {
            return 0;
        }
        long sum = 0;
        int numNodes1, numNodes2 = 0;
        int child1 = 0;
        int child2 = 0;
        for (int childnodes = 0; childnodes <= nodes - 2; childnodes += 2) {
            numNodes1 = childnodes;
            numNodes2 = nodes - childnodes - 2;
            child1 = 0;
            child2 = 0;
            for (int dp = (int) (Math.log(numNodes1 + 2) / Math.log(2)) - 1; dp < Math.min(depth,
                    numNodes1 / 2 + 1); dp++) {
                if (numExpansions[dp][numNodes1] == -1) {
                    numExpansions[dp][numNodes1] = dfs(dp, numNodes1);
                }
                child1 += numExpansions[dp][numNodes1];
                // System.out.println(dp + " " + numNodes1 + " " +
                // numExpansions[dp][numNodes1]);
            }
            for (int dp = (int) (Math.log(numNodes2 + 2) / Math.log(2)) - 1; dp < Math.min(depth,
                    numNodes2 / 2 + 1); dp++) {
                if (numExpansions[dp][numNodes2] == -1) {
                    numExpansions[dp][numNodes2] = dfs(dp, numNodes2);
                }
                child2 += numExpansions[dp][numNodes2];
                // System.out.println(dp + " " + numNodes2 + " " +
                // numExpansions[dp][numNodes2]);
            }
            if (child1 * child1 != 0) {
                System.out
                        .println(numNodes1 + " " + numNodes2 + " " + child1 + " " + child2 + " " + depth + " " + nodes);
            }
            sum += child1 * child2;
        }
        System.out.println(depth + " " + nodes + " " + sum);

        return sum;
    }
}