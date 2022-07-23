/*
ID: ssk49881
LANG: JAVA
TASK: prob7
*/

import java.io.*;
import java.util.*;

public class prob7 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int num = Integer.parseInt(in.readLine());
        for (int count = 0; count < num; count++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            Part[][] parts = new Part[m][n];
            int[][] elevations = new int[m][n];
            for (int i = 0; i < m; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < n; j++) {
                    elevations[i][j] = Integer.parseInt(tokenizer.nextToken());
                    parts[i][j] = new Part(i, j, elevations[i][j], i * m + j);
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > 0 && elevations[i - 1][j] > elevations[i][j]) {
                        parts[i][j].parents.add(parts[i - 1][j]);
                        parts[i - 1][j].children.add(parts[i][j]);
                    }
                    if (j > 0 && elevations[i][j - 1] > elevations[i][j]) {
                        parts[i][j].parents.add(parts[i][j - 1]);
                        parts[i][j - 1].children.add(parts[i][j]);
                    }
                    if (i < m - 1 && elevations[i + 1][j] > elevations[i][j]) {
                        parts[i][j].parents.add(parts[i + 1][j]);
                        parts[i + 1][j].children.add(parts[i][j]);
                    }
                    if (j < n - 1 && elevations[i][j + 1] > elevations[i][j]) {
                        parts[i][j].parents.add(parts[i][j + 1]);
                        parts[i][j + 1].children.add(parts[i][j]);
                    }
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (parts[i][j].parents.size() == 0 && !(i == 0 && j == 0)) {
                        for (Part c : parts[i][j].children) {
                            c.parents.remove(parts[i][j]);
                        }
                    }
                }
            }
            ArrayList<Part> newOnes = new ArrayList<>();
            parts[0][0].paths = 1;
            newOnes.add(parts[0][0]);
            while (newOnes.size() > 0) {
                ArrayList<Part> nextOnes = new ArrayList<>();
                while (newOnes.size() > 0) {
                    Part p = newOnes.remove(newOnes.size() - 1);
                    for (Part c : p.children) {
                        c.parents.remove(p);
                        c.paths = (c.paths + p.paths) % 1000;
                        // System.out.println(c.x + " " + c.y + " child of " + p.x + " " + p.y + "
                        // Parents " + c.parents.size());
                        if (c.parents.size() == 0) {
                            nextOnes.add(c);
                        }
                    }
                }
                newOnes = nextOnes;
            }

            int answer = parts[m - 1][n - 1].paths;
            out.println(answer);
        }
        in.close();
        out.close();
    }

    public static class Part {
        int id;
        int x;
        int y;
        int paths = 0;
        int elevation;
        ArrayList<Part> parents = new ArrayList<>();
        ArrayList<Part> children = new ArrayList<>();

        public Part(int x, int y, int elevation, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
            this.elevation = elevation;
        }
    }
}