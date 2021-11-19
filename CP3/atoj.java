/*
ID: ssk49881
LANG: JAVA
TASK: atoj
*/

import java.io.*;
import java.util.*;

public class atoj {
    public static void main(String[] args) throws Exception {
        ArrayList<String> strings = new ArrayList<>();
        char[] chars = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
        boolean[] used = new boolean[10];
        solve("", strings, chars, used);
        System.out.println(strings.size());
        Set<String> lSet = new HashSet<>();
        for (String s : strings) {
            lSet.add(s);
        }
        System.out.println(lSet.size());
    }

    public static void solve(String s, ArrayList<String> strings, char[] chars, boolean[] used) {
        if (s.length() == 10) {
            strings.add(s);
            return;
        }
        for (int i = 0; i < 10; i++) {
            if (!used[i]) {
                used[i] = true;
                solve(s + chars[i], strings, chars, used);
                used[i] = false;
            }
        }
    }
}