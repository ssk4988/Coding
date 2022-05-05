import java.util.*;
import java.io.*;

public class goodship {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();

        int testCases = Integer.parseInt(in.readLine());
        for (int testCase = 0; testCase < testCases; testCase ++) {
            Set<String> bruh3 = new HashSet<>();
            Set<String> bruh4 = new HashSet<>();
            Set<str> bruh = new HashSet<>();
            Set<str> bruh2 = new HashSet<>();
            StringTokenizer t = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(t.nextToken());
            int y = Integer.parseInt(t.nextToken());
            for (int j = 0; j < x; j ++) {
                str s = new str(in.readLine());

                bruh.add(s);
                bruh3.add(s.s2);
            }
            for (int j = 0; j < y; j ++) {
                str s = new str(in.readLine());
                bruh4.add(s.s2);
                bruh2.add(s);
            }
            for (str a : bruh2) {
                for(str c : bruh){
                    if(c.s1.equals(a.s1)){
                        bruh.remove(c);
                        break;
                    }
                }
            }
            ArrayList<str> output = new ArrayList<>();
            for (str a : bruh) {
                output.add(a);
            }
            Collections.sort(output);
            for (str a : output) {
                b.append(a.s1 + "\n");
            }
        }
        
        System.out.print(b);
        in.close();
    }
    public static class str implements Comparable<str>{
        String s1;
        String s2;
        public str(String s1){
            this.s1 = s1;
            this.s2 = s1.toLowerCase();
        }
        @Override
        public int compareTo(goodship.str o) {
            return this.s2.compareTo(o.s2);
        }
    }
}