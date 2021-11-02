/*
ID: ssk49881
LANG: JAVA
TASK: sort3
*/

import java.io.*;
import java.util.*;

public class sort3 {
    public static int[] frequency = { 0, 0, 0 };
    public static int[] list;
    public static int swaps = 0;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("sort3.in"));
        PrintWriter out = new PrintWriter(new File("sort3.out"));
        int n = Integer.parseInt(in.nextLine());
        list = new int[n];
        for (int i = 0; i < n; i++) {
            int nextInt = Integer.parseInt(in.nextLine());
            list[i] = nextInt;
            frequency[nextInt - 1] += 1;
        }
        System.out.println("Initialized");
        for (int originalNum = 1; originalNum <= 3; originalNum++) {
            System.out.println("Fixing region: " + originalNum);
            for (int j = startIndex(originalNum); j < endIndex(originalNum); j++) {
                int misplaced1 = list[j];
                if (misplaced1 != originalNum) {
                    System.out.println("Searching in: " + misplaced1);
                    search: for (int k = startIndex(misplaced1); k < endIndex(misplaced1); k++) {
                        if (list[k] == originalNum) {
                            swap(j, k);
                            break search;
                        }
                    }
                }
            }
        }
        for (int originalNum = 1; originalNum <= 3; originalNum++) {
            System.out.println("Fixing region: " + originalNum);
            for (int j = startIndex(originalNum); j < endIndex(originalNum); j++) {
                int misplaced1 = list[j];
                if (misplaced1 != originalNum) {
                    System.out.println("Searching in: " + misplaced1);
                    search: for (int k = startIndex(misplaced1); k < endIndex(misplaced1); k++) {
                        if (list[k] == 6 - originalNum - misplaced1) {
                            System.out.println("3-way switch in: " + (6 - originalNum - misplaced1));
                            for (int l = startIndex(6 - originalNum - misplaced1); l < endIndex(
                                    6 - originalNum - misplaced1); l++) {
                                if (list[l] == originalNum) {
                                    swap(j, l);
                                    swap(l, k);
                                    break search;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (int num : list) {
            System.out.println(num);
        }
        out.println(swaps);

        in.close();
        out.close();
    }

    public static int startIndex(int num) {
        int sum = 0;
        for (int i = 0; i < num - 1; i++) {
            sum += frequency[i];
        }
        return sum;
    }

    public static int endIndex(int num) {
        int sum = 0;
        for (int i = 0; i < num; i++) {
            sum += frequency[i];
        }
        return sum;
    }

    public static void swap(int index1, int index2) {
        int tmp = list[index1];
        list[index1] = list[index2];
        list[index2] = tmp;
        swaps++;
    }
}