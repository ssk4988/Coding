/*
ID: ssk49881
LANG: JAVA
TASK: concom
*/

import java.io.*;
import java.util.*;

public class concom {
    public static Company[] companies;
    public static int numCompanies;
    public static ArrayList<Integer> propagatetree = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("concom.in"));
        PrintWriter out = new PrintWriter(new File("concom.out"));
        numCompanies = Integer.parseInt(in.nextLine());
        companies = new Company[101];
        String phrase;
        while (in.hasNextLine()) {
            phrase = in.nextLine();
            int c1 = Integer.parseInt(phrase.split(" ")[0]);
            int c2 = Integer.parseInt(phrase.split(" ")[1]);
            int p = Integer.parseInt(phrase.split(" ")[2]);
            if (companies[c1] == null) {
                companies[c1] = new Company(c1);
            }
            if (companies[c2] == null) {
                companies[c2] = new Company(c2);
            }
            companies[c1].directPercent[c2] = p;
            companies[c1].propagatedPercent[c2] = p;
        }
        for (int i = 1; i < companies.length; i++) {
            if (companies[i] != null) {
                propagate(i);
            }
        }
        for (int i = 1; i < companies.length; i++) {
            for (int j = 1; j < companies.length; j++) {
                if (i == j || companies[i] == null || companies[j] == null) {
                    continue;
                }
                if (companies[i].owns[j] || companies[i].propagatedPercent[j] >= 50) {
                    out.println(i + " " + j);
                }
            }
        }

        in.close();
        out.close();
    }

    public static void propagate(int owner) {
        propagatetree.add(owner);
        ArrayList<Integer> frontier = new ArrayList<>();
        do {
            for (int i = 1; i < companies[owner].owns.length; i++) {
                if (i == owner) {
                    continue;
                }
                if (companies[owner].owns[i] && frontier.contains(i)) {
                    if (!propagatetree.contains(i)) {
                        propagate(i);
                    }
                    for (int j = 1; j < companies[i].propagatedPercent.length; j++) {
                        if (j == owner) {
                            continue;
                        }
                        if (companies[i].propagatedPercent[j] != 0) {
                            companies[owner].propagatedPercent[j] = Math.min(100, companies[owner].propagatedPercent[j] + companies[i].propagatedPercent[j]);
                        }
                        if (companies[owner].propagatedPercent[j] > 100) {
                            System.out.println("ERROR" + owner + " " + j + " " + companies[owner].propagatedPercent[j]);
                        }
                    }
                    frontier.remove(frontier.indexOf(i));
                }
                if (!companies[owner].owns[i] && companies[owner].propagatedPercent[i] >= 50) {
                    companies[owner].owns[i] = true;
                    frontier.add(i);
                }
            }
        } while (frontier.size() != 0);
        propagatetree.remove(propagatetree.indexOf(owner));

    }
}

class Company {
    public int[] directPercent = new int[101];
    public int[] propagatedPercent = new int[101];
    public boolean[] owns = new boolean[101];
    public int number;

    public Company(int number) {
        this.number = number;
    }
}