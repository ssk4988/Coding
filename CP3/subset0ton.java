/*
ID: ssk49881
LANG: JAVA
TASK: subset0ton
*/

import java.io.*;
import java.util.*;

public class subset0ton {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        ArrayList<Integer> list = new ArrayList<>();
        solve(0, 0, list, n);
        System.out.println(list.size());
        System.out.println(list);
        in.close();
        out.close();
    }

    public static void solve(int solution, int index, ArrayList<Integer> list, int n) {
        list.add(solution);
        if (index == n) {
            return;
        }

        for (int i = index; i < n; i++) {
            solve(solution | (1 << i), i + 1, list, n);
        }
    }
}