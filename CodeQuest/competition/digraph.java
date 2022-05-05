import java.io.*;
import java.util.*;

public class digraph {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int totaldi = 0;
            int totaltri = 0;
            Map<String, Integer> difreq = new TreeMap<>();
            Map<String, Integer> trifreq = new TreeMap<>();
            for (int i = 0; i < n; i++) {
                String s = in.readLine().toUpperCase();
                StringBuilder v = new StringBuilder();
                for(int j = 0; j < s.length(); j++){
                    if(Character.isLetter(s.charAt(j)) || s.charAt(j) == ' ')
                    {
                        v.append(s.charAt(j));
                    }
                }
                s = v.toString();
                int index = 0;
                while (index < s.length()) {
                    if (index + 1 < s.length() && Character.isLetter(s.charAt(index))
                            && Character.isLetter(s.charAt(index + 1))) {
                        String c = s.substring(index, index + 2);
                        if (!difreq.containsKey(c)) {
                            difreq.put(c, 0);
                        }
                        difreq.put(c, difreq.get(c) + 1);
                        totaldi++;
                    }
                    if (index + 2 < s.length() && Character.isLetter(s.charAt(index))
                            && Character.isLetter(s.charAt(index + 1)) && Character.isLetter(s.charAt(index + 2))) {
                        String c = s.substring(index, index + 3);
                        if (!trifreq.containsKey(c)) {
                            trifreq.put(c, 0);
                        }
                        trifreq.put(c, trifreq.get(c) + 1);
                        totaltri++;
                    }
                    index++;
                }
            }
            for(Map.Entry<String, Integer> e : difreq.entrySet()){
                b.append(String.format("%s: %.3f%%\n", e.getKey(), (double) e.getValue()*100/totaldi));
            }
            for(Map.Entry<String, Integer> e : trifreq.entrySet()){
                b.append(String.format("%s: %.3f%%\n", e.getKey(), (double) e.getValue()*100/totaltri));
            }  
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}