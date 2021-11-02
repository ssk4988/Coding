/*
ID: ssk49881
LANG: JAVA
TASK: transform
*/

import java.io.*;
import java.util.*;

public class transform {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("transform.in"));
        PrintWriter out = new PrintWriter(new File("transform.out"));
        int size = Integer.parseInt(in.nextLine());
        int[][] initial = new int[size][size];
        int[][] after = new int[size][size];
        for (int i = 0; i < size; i++) {
            char[] charLine = in.nextLine().toCharArray();
            for (int j = 0; j < charLine.length; j++) {
                initial[i][j] = charLine[j] == '@' ? 0 : 1;
            }
        }
        for (int i = 0; i < size; i++) {
            char[] charLine = in.nextLine().toCharArray();
            for (int j = 0; j < charLine.length; j++) {
                after[i][j] = charLine[j] == '@' ? 0 : 1;
            }
        }
        int statusCode = 7;
        if (equal(rotate(1, initial), after)) {
            statusCode = 1;
        } else if (equal(rotate(2, initial), after)) {
            statusCode = 2;
        }
        else if(equal(rotate(3, initial), after)){
            statusCode = 3;
        }
        else if(equal(reflectvertical(initial), after)){
            statusCode = 4;
        }
        else if(equal(reflecthorizontal(initial), after) || equal(rotate(1, reflecthorizontal(initial)), after) || equal(rotate(2, reflecthorizontal(initial)), after) || equal(rotate(3, reflecthorizontal(initial)), after)){
            statusCode = 5;
        }
        else if(equal(initial, after)){
            statusCode = 6;
        }

        out.println(Integer.toString(statusCode));
        in.close();
        out.close();
    }

    public static boolean equal(int[][] first, int[][] second) {
        boolean equal = true;
        for (int i = 0; i < first.length; i++) {
            for (int j = 0; j < first[i].length; j++) {
                if (first[i][j] != second[i][j]) {
                    equal = false;
                }
            }
        }

        return equal;
    }

    public static int[][] rotate(int config, int[][] array) {
        int[][] copy = new int[array.length][array.length];
        if (config == 1) {
            for (int i = 0; i < array.length; i++) {
                for (int j = 0; j < array.length; j++) {
                    copy[j][array.length - 1 - i] = array[i][j];
                }
            }
        }
        if (config == 2) {
            for (int i = 0; i < array.length; i++) {
                for (int j = 0; j < array.length; j++) {
                    copy[array.length - 1 - i][array.length - 1 - j] = array[i][j];
                }
            }
        }
        if (config == 3) {
            for (int i = 0; i < array.length; i++) {
                for (int j = 0; j < array.length; j++) {
                    copy[array.length - 1 - j][i] = array[i][j];
                }
            }
        }

        return copy;
    }

    public static int[][] reflectvertical(int[][] array) {
        int[][] copy = new int[array.length][array.length];
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array.length; j++) {
                copy[i][array.length - 1 - j] = array[i][j];
            }
        }
        return copy;
    }

    public static int[][] reflecthorizontal(int[][] array) {
        int[][] copy = new int[array.length][array.length];
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array.length; j++) {
                copy[array.length - 1 - i][j] = array[i][j];
            }
        }
        return copy;
    }
}