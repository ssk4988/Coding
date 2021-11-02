/*
ID: ssk49881
LANG: JAVA
TASK: cowtour
*/

import java.io.*;
import java.util.*;

public class cowtour {
    public static Pasture[] pastures;
    public static boolean[][] adjacent;

    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        Scanner in = new Scanner(new File("cowtour.in"));
        PrintWriter out = new PrintWriter(new File("cowtour.out"));
        int numPastures = Integer.parseInt(in.nextLine());
        pastures = new Pasture[numPastures];
        for (int i = 0; i < numPastures; i++) {
            String phrase = in.nextLine();
            pastures[i] = new Pasture(Integer.parseInt(phrase.split(" ")[0]), Integer.parseInt(phrase.split(" ")[1]));
        }
        adjacent = new boolean[numPastures][numPastures];
        double[][] distances = new double[numPastures][numPastures];
        for (int i = 0; i < numPastures; i++) {
            String phrase = in.nextLine();
            for (int j = 0; j < phrase.length(); j++) {
                if (phrase.charAt(j) == '1') {
                    adjacent[i][j] = true;
                }
            }
        }
        int numComponents = 0;

        while (numComponents != 2) {
            numComponents = 0;
            for (int i = 0; i < numPastures; i++) {
                if (pastures[i].component == -1) {
                    numComponents++;
                    pastures[i].component = -2;
                    floodfill(numComponents);
                }
                if(numComponents > 2){
                    break;
                }
            }
            System.out.println("Components: " + numComponents + " " + (System.currentTimeMillis() - start_time));

            for (int k = 0; k < numPastures; k++) {
                for (int l = 0; l < k; l++) {
                    if (k == l) {
                        continue;
                    }
                    if (adjacent[k][l]) {
                        distances[k][l] = pastures[k].distanceTo(pastures[l]);
                        distances[l][k] = distances[k][l];
                    } else {
                        distances[k][l] = Double.MAX_VALUE;
                        distances[l][k] = Double.MAX_VALUE;
                    }

                }
            }
            for (int k = 0; k < numPastures; k++) {
                for (int l = 0; l < numPastures; l++) {
                    for (int m = 0; m < l; m++) {
                        if (distances[l][k] + distances[k][m] < distances[l][m]) {
                            distances[l][m] = distances[l][k] + distances[k][m];
                        }
                    }
                }
            }

            double minDiameter = Double.MAX_VALUE;
            int connect1 = -1;
            int connect2 = -1;
            for (int i = 0; i < numPastures; i++) {
                if (pastures[i].component == 1) {
                    for (int j = 0; j < numPastures; j++) {
                        if (pastures[j].component == 2) {
                            double comp1Diameter = Double.MIN_VALUE;
                            double comp2Diameter = Double.MIN_VALUE;
                            for (int k = 0; k < numPastures; k++) {
                                if (pastures[k].component == 1 && distances[i][k] != Double.MAX_VALUE && k != i
                                        && distances[i][k] > comp1Diameter) {
                                    comp1Diameter = distances[i][k];
                                }
                                if (pastures[k].component == 2 && distances[j][k] != Double.MAX_VALUE && k != j
                                        && distances[j][k] > comp2Diameter) {
                                    comp2Diameter = distances[j][k];
                                }
                            }
                            double diameter = comp1Diameter + comp2Diameter + pastures[i].distanceTo(pastures[j]);
                            if (diameter < minDiameter) {
                                minDiameter = diameter;
                                connect1 = i;
                                connect2 = j;
                            }
                        }
                    }
                }
            }
            adjacent[connect1][connect2] = true;
            adjacent[connect2][connect1] = true;
            if (numComponents == 2) {
                out.printf("%f\n", minDiameter);
            }
            for (int i = 0; i < numPastures; i++) {
                pastures[i].component = -1;
            }
        }

        in.close();
        out.close();
    }

    public static void floodfill(int componentNum) {
        int numvisited = 0;
        do {
            numvisited = 0;
            for (int i = 0; i < pastures.length; i++) {
                if (pastures[i].component == -2) {
                    numvisited++;
                    pastures[i].component = componentNum;
                    for (int j = 0; j < pastures.length; j++) {
                        if (adjacent[i][j] && pastures[j].component == -1) {
                            pastures[j].component = -2;
                        }
                    }
                }
            }
        } while (numvisited == 0);
    }
}

class Pasture {
    public int x;
    public int y;
    public int component = -1;

    public Pasture(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public double distanceTo(Pasture p) {
        return Math.sqrt(Math.pow(p.x - this.x, 2) + Math.pow(p.y - this.y, 2));
    }
}