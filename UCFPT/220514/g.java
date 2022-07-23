import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        ArrayList<point> p = new ArrayList<>();
        for(int i = 0; i < n; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int s = Integer.parseInt(tokenizer.nextToken());
            int f = Integer.parseInt(tokenizer.nextToken());
            p.add(new point(s, f));
        }
        Collections.sort(p);
        int cnt = 0;
        int end = 0;
        for(int i = 0; i < p.size(); i++){
            if(p.get(i).x < end) continue;
            cnt++;
            end = p.get(i).y;
        }
        System.out.println(cnt);
        in.close();
    }
    public static class point implements Comparable<point>{
        public int x;
        public int y;
        public point(int x, int y){
            this.x = x;
            this.y = y;
        }
        @Override
        public int compareTo(g.point o) {
            if(this.y - o.y == 0) return this.x - o.x;
            return this.y - o.y;
        }
    }
}