import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder out = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        person[] people = new person[n];
        for(int i = 0; i < n; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String name = tokenizer.nextToken();
            name = name.substring(0, name.length()-1);
            person p = new person(name);
            while(tokenizer.hasMoreTokens()){
                String c = tokenizer.nextToken();
                if(c.equals("class")){
                    continue;
                }
                int k = 0;
                if(c.equals("upper")){
                    k = 1;
                }
                else if(c.equals("lower")){
                    k = -1;
                }
                p.classes.add(k);
            }
            people[i] = p;
        }
        Arrays.sort(people);
        for(person p : people){
            out.append(p.name + "\n");
        }
        System.out.print(out);
        in.close();
    }
    public static class person implements Comparable<person>{
        String name;
        ArrayList<Integer> classes = new ArrayList<>();
        public person(String name){
            this.name = name;
        }
        @Override
        public int compareTo(b.person o) {
            int max = Math.max(classes.size(), o.classes.size());
            for(int i = 0; i < max; i++){
                int i1 = i >= classes.size() ? 0 : classes.get(classes.size() - 1 - i);
                int i2 = i >= o.classes.size() ? 0 : o.classes.get(o.classes.size() - 1 - i);
                if(i1 != i2){
                    return i2 - i1;
                }
            }
            return name.compareTo(o.name);
        }
    }
}