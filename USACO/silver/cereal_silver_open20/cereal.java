/*
ID: ssk49881
LANG: JAVA
TASK: cereal
*/

import java.io.*;
import java.util.*;

public class cereal {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("cereal.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cereal.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numCereals = Integer.parseInt(tokenizer.nextToken());
        int[] current = new int[numCereals];
        Cow[] previous = new Cow[numCereals];
        Cow[] cows = new Cow[numCows];
        Arrays.fill(current, -1);
        for (int i = 0; i < numCows; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            cows[i] = new Cow(i, first, second);
        }
        int cowCounter = 0;
        int currIndex = -1;
        int[] answers = new int[numCows];
        for (int i = numCows - 1; i >= 0; i--) {
            currIndex = i;
            int position = cows[currIndex].first;
            while (true) {
                if (current[position] == -1) {
                    current[position] = currIndex;
                    cowCounter++;
                    break;
                } else if (current[position] < currIndex) {
                    break;
                } else if (current[position] > currIndex) {
                    int next = current[position];
                    current[position] = currIndex;
                    if (cows[next].first == position) {
                        position = cows[next].second;
                        currIndex = next;
                    } else {
                        break;
                    }
                }
            }
            answers[i] = cowCounter;
        }
        for (int i = 0; i < answers.length; i++) {
            out.println(answers[i]);
        }

        in.close();
        out.close();
    }

    public static class Cow {
        int id;
        int first;
        int second;
        boolean hasFirst = false;
        boolean hasSecond = false;
        Cow childFirst = null;
        Cow childSecond = null;

        public Cow(int id, int first, int second) {
            this.id = id;
            this.first = first;
            this.second = second;
        }

        @Override
        public String toString() {
            return this.id + " ";
        }
    }
}