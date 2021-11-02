/*
ID: ssk49881
LANG: JAVA
TASK: hoofball
*/

import java.io.*;
import java.util.*;

public class hoofball {
    public static int[] positions;
    public static int numCows;
    public static int[] closest;
    public static int[] component;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("hoofball.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hoofball.out")));

        numCows = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        positions = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            positions[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(positions);
        boolean[] getsPassedTo = new boolean[numCows];
        closest = new int[numCows];

        for (int i = 0; i < numCows; i++) {
            if (i > 0 && i < numCows - 1) {
                closest[i] = Math.abs(positions[i] - positions[i - 1]) <= Math.abs(positions[i] - positions[i + 1])
                        ? i - 1
                        : i + 1;
            } else if (i == 0) {
                closest[0] = 1;
            } else if (i == numCows - 1) {
                closest[numCows - 1] = numCows - 2;
            }

            // System.out.println(positions[i] + " " + positions[closest[i]]);
            getsPassedTo[closest[i]] = true;
        }
        int numComponents = 0;
        component = new int[numCows];
        Arrays.fill(component, -1);
        for (int i = 0; i < numCows; i++) {
            if (!getsPassedTo[i] && component[i] == -1) {
                numComponents++;
                component[i] = -2;
                flood_fill(numComponents);
            }
        }
        for (int i = 0; i < numCows; i++) {
            if (component[i] == -1) {
                numComponents++;
                component[i] = -2;
                flood_fill(numComponents);
            }
        }
        out.println(numComponents);

        in.close();
        out.close();
    }

    public static void flood_fill(int componentNum) {
        int numvisited = 1;
        while (numvisited > 0) {
            numvisited = 0;
            for (int i = 0; i < numCows; i++) {
                if (component[i] == -2) {
                    numvisited++;
                    component[i] = componentNum;
                    if (component[closest[i]] == -1) {
                        component[closest[i]] = -2;
                    }
                }
            }
        }
    }
}