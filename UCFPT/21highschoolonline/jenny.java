/*
ID: ssk49881
LANG: JAVA
TASK: jenny
*/

import java.io.*;
import java.util.*;

public class jenny {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        ArrayList<Long>[] answers = new ArrayList[10];
        for (int i = 0; i < answers.length; i++) {
            answers[i] = new ArrayList<>();
        }
        generate(answers, 0, 0, new boolean[10]);
        for(int i = 0; i < answers.length; i++){
            Collections.sort(answers[i]);
            //System.out.println(answers[i].size());
        }
        for (int num = 0; num < n; num++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numDigits = Integer.parseInt(tokenizer.nextToken());
            int jen = Integer.parseInt(tokenizer.nextToken());
            if (numDigits > 9 || jen > answers[numDigits].size()) {
                System.out.println("Brice doesn't stand a chance!");
            } else {
                System.out.println(answers[numDigits].get(jen - 1));
            }
        }

        in.close();
        out.close();
    }

    public static boolean isJenny(long num) {
        if (num == 0 || num == 1)
            return false;
        if (num == 2)
            return true;
        if (num % 2 == 0) return false;
        for(int i = 3; i*i <= num + 2; i+= 2){
            if(num % i == 0 || (num+2) % i == 0){
                return false;
            }
        }
        return true;
    }

    public static void generate(ArrayList<Long>[] answers, int index, long curr, boolean[] using) {
        if (isJenny(curr)) {
            answers[index].add(curr);
        }
        for (int i = 0; i < 10; i++) {
            if (index == 0 && i == 0)
                continue;
            if (using[i]) {
                continue;
            }
            using[i] = true;
            generate(answers, index + 1, curr * 10 + i, using);
            using[i] = false;
        }
    }
}