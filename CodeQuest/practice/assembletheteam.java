import java.io.*;
import java.util.*;

public class assembletheteam {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b= new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            ArrayList<agent> a = new ArrayList<>();
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            while(tokenizer.hasMoreTokens()){
                String s = tokenizer.nextToken();
                char c = s.charAt(0);
                int val = Integer.parseInt(s.substring(2));
                agent a1 = new agent(val, c);
                a.add(a1);
            }
            Collections.sort(a, new agentcomp());
            int p1 = 0, p2 = 0;
            ArrayList<String> solutions = new ArrayList<>();
            StringBuilder strbr = new StringBuilder();
            for(agent a1 : a){
                strbr.append(a1.name);
            }
            while(p1 < a.size()){
                while(p2 + 1 < a.size() && a.get(p2+1).val - a.get(p1).val <= 10){
                    p2++;
                }
                char[] sol = strbr.substring(p1, p2+1).toCharArray();
                Arrays.sort(sol);
                solutions.add(new String(sol));
                p1++;
                if(p1 > p2) p2 = p1;
            }
            Collections.sort(solutions, new strcomp());
            for(int i = 0; i < solutions.get(0).length(); i++){
                b.append(solutions.get(0).charAt(i));
                if(i+1 < solutions.get(0).length()){
                    b.append(" ");
                }
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }
    public static class strcomp implements Comparator<String>{
        @Override
        public int compare(String o1, String o2) {
            if(o1.length() == o2.length()){
                return o1.compareTo(o2);
            }
            return o2.length() - o1.length();
        }
    }
    public static class agentcomp implements Comparator<agent>{
        @Override
        public int compare(assembletheteam.agent o1, assembletheteam.agent o2) {
            return o1.val - o2.val;
        }
    }
    public static class agent{
        int val;
        char name;
        public agent(int val, char name){
            this.val = val;
            this.name = name;
        }
    }
}