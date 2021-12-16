import java.io.*;
import java.util.*;

public class d8p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d8p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        int answer = 0;
        for (String s : input) {
            String[] s1 = s.substring(0, s.indexOf("|") - 1).split(" ");
            Set<Integer>[] comp = new Set[s1.length];
            int[] ind = new int[10];
            int[] freq = new int[7];
            for (int i = 0; i < s1.length; i++) {
                comp[i] = new HashSet<>();
                for (int j = 0; j < s1[i].length(); j++) {
                    comp[i].add(s1[i].charAt(j) - 'a');
                    freq[s1[i].charAt(j) - 'a']++;
                }
                if (comp[i].size() == 2) {
                    ind[1] = i;
                }
                if (comp[i].size() == 3) {
                    ind[7] = i;
                }
                if (comp[i].size() == 4) {
                    ind[4] = i;
                }
                if (comp[i].size() == 7) {
                    ind[8] = i;
                }
            }
            ArrayList<Integer> place = new ArrayList<>(comp[ind[7]]);
            place.removeAll(comp[ind[1]]);
            int up = place.get(0);
            place = new ArrayList<>(comp[ind[1]]);
            int rightup = freq[place.get(0)] == 8 ? place.get(0) : place.get(1);
            int rightdown = freq[place.get(0)] == 8 ? place.get(1) : place.get(0);
            place = new ArrayList<>(comp[ind[4]]);
            place.removeAll(comp[ind[1]]);
            int center = freq[place.get(0)] == 7 ? place.get(0) : place.get(1);
            int leftup = freq[place.get(0)] == 7 ? place.get(1) : place.get(0);
            place = new ArrayList<>(comp[ind[8]]);
            place.removeAll(comp[ind[7]]);
            place.removeAll(comp[ind[4]]);
            int down = freq[place.get(0)] == 7 ? place.get(0) : place.get(1);
            int leftdown = freq[place.get(0)] == 7 ? place.get(1) : place.get(0);
            String[] output = s.substring(s.indexOf("|") + 1).split(" ");
            for (int i = 0; i < comp.length; i++) {
                if (comp[i].size() == 6 && !comp[i].contains(center)) {
                    ind[0] = i;
                }
                if (comp[i].size() == 5 && !comp[i].contains(leftup) && !comp[i].contains(rightdown)) {
                    ind[2] = i;
                }
                if (comp[i].size() == 5 && !comp[i].contains(leftup) && !comp[i].contains(leftdown)) {
                    ind[3] = i;
                }
                if (comp[i].size() == 5 && !comp[i].contains(leftdown) && !comp[i].contains(rightup)) {
                    ind[5] = i;
                }
                if (comp[i].size() == 6 && !comp[i].contains(rightup)) {
                    ind[6] = i;
                }
                if (comp[i].size() == 6 && !comp[i].contains(leftdown)) {
                    ind[9] = i;
                }
            }
            int num = 0;
            for (int i = 0; i < output.length; i++) {
                Set<Integer> set = new HashSet<>();
                for (int j = 0; j < output[i].length(); j++) {
                    set.add(output[i].charAt(j) - 'a');
                }
                for (int j = 0; j < comp.length; j++) {
                    if (set.equals(comp[ind[j]])) {
                        num = num * 10 + j;
                        break;
                    }
                }
            }
            answer += num;
        }
        System.out.println(answer);
        in.close();
    }
}