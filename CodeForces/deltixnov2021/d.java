import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int size = Integer.parseInt(tokenizer.nextToken());
        int conditions = Integer.parseInt(tokenizer.nextToken());
        Network[] components = new Network[size];
        Network[] complist = new Network[size];
        for (int i = 0; i < size; i++) {
            Network c = new Network();
            c.id = i;
            c.children.add(i);
            components[i] = c;
            complist[i] = c;
        }
        StringBuilder b = new StringBuilder();
        int free = 0;
        for (int i = 0; i < conditions; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            Network c1 = components[i1];
            Network c2 = components[i2];
            if (c1 == c2)
                free++;
            else {
                for(int j = 0; j < c2.children.size();){
                    c1.children.add(c2.children.get(j));
                    components[c2.children.get(j)] = c1;
                    c2.children.remove(j);
                }
            }

            Arrays.sort(complist);
            int answer = complist[0].children.size();
            for (int j = 0; j < free; j++) {
                answer += complist[1 + j].children.size();
            }
            b.append((answer - 1) + "\n");
        }
        System.out.print(b);

        in.close();
        out.close();
    }

    public static class Network implements Comparable<Network> {
        int id;
        ArrayList<Integer> children = new ArrayList<>();

        @Override
        public int compareTo(Network o) {
            return o.children.size() - this.children.size();
        }
    }
}