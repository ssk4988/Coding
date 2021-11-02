/*
ID: ssk49881
LANG: JAVA
TASK: combo
*/

import java.io.*;
import java.util.*;

public class combo {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("combo.in"));
        PrintWriter out = new PrintWriter(new File("combo.out"));
        int n = Integer.parseInt(in.nextLine());
        String solutions = "";
        int numSolutions = 0;
        String solution = "";
        String phrase = in.nextLine();
        int first = Integer.parseInt(phrase.split(" ")[0]);
        int second = Integer.parseInt(phrase.split(" ")[1]);
        int third = Integer.parseInt(phrase.split(" ")[2]);
        for (int i = -2; i < 3; i++) {
            for (int j = -2; j < 3; j++) {
                for (int k = -2; k < 3; k++) {
                    solution = "";
                    solution += Integer.toString((first + i + n * 10) % n);
                    solution += "t";
                    solution += Integer.toString((second + j + n * 10) % n);
                    solution += "t";
                    solution += Integer.toString((third + k + n * 10) % n);
                    solution += "t";
                    solution += "m";
                    if (solutions.indexOf(solution) == -1) {
                        solutions += solution;
                        numSolutions++;
                    }
                }
            }
        }
        phrase = in.nextLine();
        first = Integer.parseInt(phrase.split(" ")[0]);
        second = Integer.parseInt(phrase.split(" ")[1]);
        third = Integer.parseInt(phrase.split(" ")[2]);

        for (int i = -2; i < 3; i++) {
            for (int j = -2; j < 3; j++) {
                for (int k = -2; k < 3; k++) {
                    solution = "";
                    solution += Integer.toString((first + i + n * 10) % n);
                    solution += "t";
                    solution += Integer.toString((second + j + n * 10) % n);
                    solution += "t";
                    solution += Integer.toString((third + k + n * 10) % n);
                    solution += "t";
                    solution += "m";
                    if (solutions.indexOf(solution) == -1) {
                        solutions += solution;
                        numSolutions++;
                    }
                }
            }
        }
        out.println(numSolutions);

        in.close();
        out.close();
    }
}