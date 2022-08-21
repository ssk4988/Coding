import java.io.*;
import java.lang.reflect.Array;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        Map<String, Integer> map = new HashMap<>();
        rule[] rules = new rule[n];
        ArrayList<top> tops = new ArrayList<>();
        ArrayDeque<rule> queue = new ArrayDeque<>();
        int met = 0;
        for (int i = 0; i < n; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            rules[i] = new rule(i);
            if (tokenizer.countTokens() == 1) {
                String name = tokenizer.nextToken();
                define(name, map, tops);
                rules[i].second = tops.get(map.get(name));
                queue.add(rules[i]);
            } else {
                tokenizer.nextToken();
                String next = tokenizer.nextToken();
                rules[i].req = 1;
                while (!next.equals("then")) {
                    if (next.equals("and") || next.equals("or")) {
                        if (next.equals("and")) {
                            rules[i].req++;
                        }
                        next = tokenizer.nextToken();
                        continue;
                    }
                    define(next, map, tops);
                    rules[i].first.add(tops.get(map.get(next)));
                    tops.get(map.get(next)).references.add(rules[i]);
                    next = tokenizer.nextToken();
                }
                next = tokenizer.nextToken();
                define(next, map, tops);
                rules[i].second = tops.get(map.get(next));
            }
        }
        while (!queue.isEmpty()) {
            rule r = queue.poll();
            if (r.met)
                continue;
            r.met = true;
            met++;
            if (!r.second.used) {
                r.second.used = true;
                for (rule r2 : r.second.references) {
                    r2.curr++;
                    if (!r2.met && r2.curr >= r2.req) {
                        queue.add(r2);
                    }
                }
            }

        }
        // System.out.println(met);
        int count = 0;
        for (top t : tops) {
            if (t.used) {
                count++;
                // System.out.println(t.name);
            }
        }
        System.out.println(count);

        in.close();
        out.close();
    }

    public static void define(String s, Map<String, Integer> map, ArrayList<top> tops) {
        if (!map.containsKey(s)) {
            map.put(s, map.size());
            tops.add(new top(map.size() - 1, s));
        }
    }

    public static class top {
        int id;
        String name;
        boolean used = false;
        ArrayList<rule> references = new ArrayList<>();

        public top(int id, String name) {
            this.id = id;
            this.name = name;
        }
    }

    public static class rule {
        String val;
        int index;
        ArrayList<top> first = new ArrayList<>();
        top second = null;
        boolean type = false; // and is true
        boolean met = false;
        int req = 0;
        int curr = 0;

        public rule(int index) {
            this.index = index;
        }
    }
}