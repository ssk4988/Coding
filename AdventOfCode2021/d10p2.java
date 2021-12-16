import java.io.*;
import java.util.*;

public class d10p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d10p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        in.close();
        Map<Character, Integer> m = new HashMap<>();
        m.put('[', -2);
        m.put(']', 2);
        m.put('{', -3);
        m.put('}', 3);
        m.put('(', -1);
        m.put(')', 1);
        m.put('<', -4);
        m.put('>', 4);
        ArrayList<Long> scores = new ArrayList<>();
        outer: for (String s : input) {
            LinkedList<Integer> list = new LinkedList<>();
            for (char c : s.toCharArray()) {
                int k = m.get(c);
                if (list.size() > 0 && k + list.getFirst() == 0) {
                    list.removeFirst();
                } else if (k < 0) {
                    list.addFirst(k);
                } else {
                    continue outer;
                }
            }
            long score = 0;
            while (!list.isEmpty()) {
                int add = list.removeFirst();
                if(add > 0) System.out.println("bruh moment");
                score = score * 5 - add;
            }
            scores.add(score);
        }
        Collections.sort(scores);
        System.out.println(scores.size());
        System.out.println(scores.get(scores.size() / 2));
    }
}
