/*
ID: ssk49881
LANG: JAVA
TASK: inflate
*/

import java.io.*;
import java.util.*;

public class inflate {
    public static Category[] categories;
    public static int[] maxPointsInMinutes;
    public static int[] remainders;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("inflate.in"));
        PrintWriter out = new PrintWriter(new File("inflate.out"));
        String phrase = in.nextLine();
        int maxTime = Integer.parseInt(phrase.split(" ")[0]);
        int numCategories = 0;
        for (int j = 1; j < phrase.split(" ").length; j++) {
            if (phrase.split(" ")[j].length() != 0) {
                numCategories = Integer.parseInt(phrase.split(" ")[j]);
                break;
            }
        }
        maxPointsInMinutes = new int[maxTime + 1];
        categories = new Category[numCategories];
        for (int i = 0; i < numCategories; i++) {
            phrase = in.nextLine();
            int points = Integer.parseInt(phrase.split(" ")[0]);
            int minutes = Integer.parseInt(phrase.split(" ")[1]);
            categories[i] = new Category(points, minutes);
        }
        for (int i = 0; i < categories.length; i++) {
            for (int j = 0; j + categories[i].minutes < maxTime + 1; j++) {
                if (maxPointsInMinutes[j] + categories[i].points > maxPointsInMinutes[j + categories[i].minutes]) {
                    maxPointsInMinutes[j + categories[i].minutes] = maxPointsInMinutes[j] + categories[i].points;
                }
            }
        }
        int max = 0;
        for (int i = 0; i < maxTime + 1; i++) {
            if (maxPointsInMinutes[i] > max) {
                max = maxPointsInMinutes[i];
            }
        }
        out.println(max);

        in.close();
        out.close();
    }
}

class Category implements Comparable<Category> {
    public int points;
    public int minutes;
    public double ratio;

    public Category(int points, int minutes) {
        this.points = points;
        this.minutes = minutes;
        this.ratio = (double) points / minutes;
    }

    @Override
    public int compareTo(Category o) {
        if (o.ratio > this.ratio) {
            return 1;
        }
        if (o.ratio < this.ratio) {
            return -1;
        }
        return 0;
    }
}