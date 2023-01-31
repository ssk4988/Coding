import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            ArrayList<Rect> order =new ArrayList<>();
            ArrayList<Rect> rs = new ArrayList<>();
            for(int i = 0; i < n; i++){
                Rect r = new Rect();
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for(int j = 0; j < 2; j++){
                    for(int k = 0; k < 2; k++){
                        r.c[j][k] = Integer.parseInt(tokenizer.nextToken());
                    }
                }
                r.id = i;
                rs.add(r);
                order.add(r);
            }
            Collections.sort(rs, new xy());
            long area = 0;
            Rect[] last = {null, null};
            for(int i = 0; i < n; i++){
                Rect a = rs.get(i);
                for(int r = a.c[0][0] - 1; r <= a.c[1][0] - 1; r++){
                    if(last[r] == null || last[r].c[1][1] < a.c[1][1]){
                        area += a.c[1][1] - Math.max(a.c[0][1], last[r] != null ? last[r].c[1][1] + 1 : -5) + 1;
                    }
                }
                for(int r = a.c[0][0] - 1; r <= a.c[1][0] - 1; r++){
                    if(last[r] == null || last[r].c[1][1] < a.c[1][1]){
                        if(a.c[1][0] - a.c[0][0] == 0) a.c[0][1] = Math.max(a.c[0][1], last[r] != null ? last[r].c[1][1] + 1 : -5);
                        else if(last[r] != null){
                            last[r].c[1][1] = Math.min(last[r].c[1][1], a.c[0][1] - 1);
                            if(last[r].c[0][1] > last[r].c[1][1]) last[r].reset();
                        }
                        last[r] = a;
                    }
                }
                if(last[0] == a && last[1] == a){

                }
                else if(last[0] == a){
                    last[0].c[0][0] = last[0].c[1][0] = 0 + 1;
                }
                else if(last[1] == a){
                    last[1].c[0][0] = last[1].c[1][0] = 1 + 1;
                }
                else{
                    a.reset();
                }
            }
            System.out.println(area);
            for(int i = 0; i < n; i++){
                Rect a = order.get(i);
                System.out.println(a.c[0][0] + " " + a.c[0][1] + " " + a.c[1][0] + " " + a.c[1][1]);
            }
        }
        //check if rect not used
        in.close();
    }
    static class Vpair {
        int v = 0;
        Pair p;
    }
    static class Pair {
        int[] c = new int[2];
        public Pair(int x, int y){
            c[0] = x;
            c[1] = y;
        }
    }
    static class xy implements Comparator<Rect> {
        @Override
        public int compare(e.Rect o1, e.Rect o2) {
            if(o1.c[0][1] == o2.c[0][1]){
                return o1.c[1][1] - o2.c[1][1];
            }
            return o1.c[0][1] - o2.c[0][1];
        }
    }
    static class Rect{
        int id;
        int[][] c = new int[2][2];
        //dim 1: 1st or 2nd point, dim 2: r or c
        long area(){
            return ((long)c[1][0] - c[0][0]) * ((long)c[1][1] - c[0][1]);
        }
        void reset(){
            c[0][0] = c[0][1] = c[1][0] = c[1][1] = 0;
        }
    }
}
