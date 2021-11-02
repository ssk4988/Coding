/*
ID: ssk49881
LANG: JAVA
TASK: fence
*/

import java.io.*;
import java.util.*;

public class fence {
    public static ArrayList<Integer>[] neighbors;
    public static int circuitPos = 0;
    public static int[] circuit;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("fence.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence.out")));
        neighbors = new ArrayList[501];
        for (int i = 0; i < neighbors.length; i++) {
            neighbors[i] = new ArrayList<>();
        }
        int numFences = Integer.parseInt(in.readLine());
        circuit = new int[numFences + 1];
        StringTokenizer tokenizer;
        int f1, f2;
        for (int i = 0; i < numFences; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            f1 = Integer.parseInt(tokenizer.nextToken());
            f2 = Integer.parseInt(tokenizer.nextToken());
            neighbors[f1].add(f2);
            neighbors[f2].add(f1);
        }
        for (int i = 0; i < neighbors.length; i++) {
            Collections.sort(neighbors[i]);
        }
        boolean done = false;
        for (int i = 1; i < neighbors.length; i++) {
            if (neighbors[i].size() % 2 == 1) {
                find_circuit(i);
                done = true;
                break;
            }
        }
        for (int i = 1; i < neighbors.length; i++) {
            if (done) {
                break;
            }
            if (neighbors[i].size() > 0) {
                find_circuit(i);
                done = true;
            }
        }

        for (int i = circuit.length - 1; i >= 0; i--) {
            out.println(circuit[i]);
        }

        in.close();
        out.close();
    }

    public static void find_circuit(int node) {
        if (neighbors[node].size() == 0) {
            circuit[circuitPos] = node;
            circuitPos++;
        } else {
            while (neighbors[node].size() != 0) {
                int neighborNode = neighbors[node].get(0);
                neighbors[node].remove(0);
                neighbors[neighborNode].remove(neighbors[neighborNode].indexOf(node));
                find_circuit(neighborNode);
            }
            circuit[circuitPos] = node;
            circuitPos++;
        }
    }
}