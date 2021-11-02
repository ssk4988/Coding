/*
ID: ssk49881
LANG: JAVA
TASK: spin
*/

import java.io.*;
import java.util.*;

public class spin {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("spin.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("spin.out")));
        int numWheels = 5;
        Wheel[] wheels = new Wheel[numWheels];
        for (int i = 0; i < numWheels; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int rotationSpeed = Integer.parseInt(tokenizer.nextToken());
            int numWedges = Integer.parseInt(tokenizer.nextToken());
            int[] wedgeStarts = new int[numWedges];
            int[] wedgeExtents = new int[numWedges];
            for (int j = 0; j < numWedges; j++) {
                wedgeStarts[j] = Integer.parseInt(tokenizer.nextToken());
                wedgeExtents[j] = Integer.parseInt(tokenizer.nextToken());
            }
            wheels[i] = new Wheel(numWedges, wedgeStarts, wedgeExtents, rotationSpeed);
            System.out.println("wheel " + i + " " + wheels[i].numStates);
        }
        int maxSeconds = 360;
        System.out.println("maxSeconds: " + maxSeconds);

        int numSeconds = 0;
        boolean metConditions = false;
        for (int seconds = 0; seconds < maxSeconds && !metConditions; seconds++) {
            space: for (int i = 0; i < 360; i++) {
                for (int j = 0; j < numWheels; j++) {
                    if (!wheels[j].states[seconds % wheels[j].numStates][i]) {
                        continue space;
                    }
                }
                metConditions = true;
                numSeconds = seconds;
            }
        }
        if (metConditions) {
            out.println(numSeconds);
        } else {
            out.println("none");
        }

        in.close();
        out.close();
    }
}

class Wheel {
    public int numWedges;
    public int[] wedgeStarts;
    public int[] wedgeExtents;
    public int rotationSpeed;
    public int numStates;
    public boolean[][] states;

    public Wheel(int numWedges, int[] wedgeStarts, int[] wedgeExtents, int rotationSpeed) {
        this.numWedges = numWedges;
        this.wedgeStarts = wedgeStarts;
        this.wedgeExtents = wedgeExtents;
        this.rotationSpeed = rotationSpeed;
        int rotCopy = rotationSpeed;
        int copy360 = 360;
        for (int i = 2; i <= Math.min(rotCopy, copy360); i++) {
            if (rotCopy % i == 0 && copy360 % i == 0) {
                rotCopy /= i;
                copy360 /= i;
                i = 2;
            }
        }
        this.numStates = copy360;
        this.states = new boolean[this.numStates][360];
        for (int i = 0; i < this.numStates; i++) {
            // i is seconds elapsed
            for (int j = 0; j < numWedges; j++) {
                // j is each wedge
                for (int k = this.wedgeStarts[j]; k <= this.wedgeStarts[j] + this.wedgeExtents[j]; k++) {
                    this.states[i][(k + this.rotationSpeed * i) % 360] = true;
                }
            }
        }
    }
}