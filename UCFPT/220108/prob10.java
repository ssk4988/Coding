import java.io.*;
import java.util.*;

public class prob10 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int rows = Integer.parseInt(tokenizer.nextToken());
            int cols = Integer.parseInt(tokenizer.nextToken());
            section[][][] s = new section[rows][cols][4];
            boolean[][] type = new boolean[rows][cols];
            for (int i = 0; i < rows; i++) {
                String str = in.readLine();
                for (int j = 0; j < cols; j++) {
                    type[i][j] = str.charAt(j) == '\\';
                    for (int k = 0; k < 4; k++) {
                        s[i][j][k] = new section(i, j, k);
                    }
                }
            }
            barrier[] bs = new barrier[rows * cols];
            barrier[][] b = new barrier[rows][cols];
            for (int i = 0; i < rows; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < cols; j++) {
                    b[i][j] = new barrier(Integer.parseInt(tokenizer.nextToken()), i, j, type[i][j], s);
                    bs[i * cols + j] = b[i][j];
                }
            }
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (b[i][j].type) {
                        s[i][j][0].ns.add(s[i][j][1]);
                        s[i][j][1].ns.add(s[i][j][0]);
                        s[i][j][2].ns.add(s[i][j][3]);
                        s[i][j][3].ns.add(s[i][j][2]);
                    } else {
                        s[i][j][0].ns.add(s[i][j][3]);
                        s[i][j][3].ns.add(s[i][j][0]);
                        s[i][j][1].ns.add(s[i][j][2]);
                        s[i][j][2].ns.add(s[i][j][1]);
                    }
                    if(i > 0){
                        s[i][j][0].ns.add(s[i-1][j][2]);
                        s[i-1][j][2].ns.add(s[i][j][0]);
                    }
                    if(j > 0){
                        s[i][j][3].ns.add(s[i][j-1][1]);
                        s[i][j-1][1].ns.add(s[i][j][3]);
                    }
                    if(i+1 < rows){
                        s[i][j][2].ns.add(s[i+1][j][0]);
                        s[i+1][j][0].ns.add(s[i][j][2]);
                    }
                    if(j+1 < cols){
                        s[i][j][1].ns.add(s[i][j+1][3]);
                        s[i][j+1][3].ns.add(s[i][j][1]);
                    }
                }
            }
            ArrayList<component> cs = new ArrayList<>();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    for(int k = 0; k < 4; k++){
                        if(s[i][j][k].c == null){
                            cs.add(new component(cs.size()));
                            flood(s[i][j][k], null, cs.get(cs.size() - 1));
                        }
                    }
                }
            }
            Arrays.sort(bs);
            int total = 0;
            for(int i = 0; i < bs.length; i++){
                Set<component> set = new HashSet<>();
                for(section n : bs[i].ns){
                    set.add(n.c);
                }
                if(set.size() <2){
                    continue;
                }
                //check later if set size > 2
                total += bs[i].val;
                ArrayList<component> nc = new ArrayList<>();
                for(component c : set){
                    nc.add(c);
                }
                component larger = nc.get(0).children.size() > nc.get(0).children.size() ? nc.get(0) : nc.get(1);
                component smaller = nc.get(0) == larger ? nc.get(1) : nc.get(0);
                for(section sc : smaller.children){
                    sc.c = larger;
                    larger.children.add(sc);
                }
                smaller.children.clear();
            }
            System.out.printf("Case %d: %d\n", (casenum+1), total);
        }

        in.close();
        out.close();
    }
    public static class component{
        int id;
        Set<section> children = new HashSet<>();
        public component(int id){
            this.id = id;
        }
    }
    public static void flood(section s, component find, component fix){
        s.c = fix;
        if(find != null) find.children.remove(s);
        fix.children.add(s);
        for(section n : s.ns){
            if(n.c == find){
                flood(n, find, fix);
            }
        }
    }
    public static class section {
        int x;
        int y;
        int z;
        component c = null;
        ArrayList<section> ns = new ArrayList<>();

        public section(int x, int y, int z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    public static class barrier implements Comparable<barrier> {
        int val;
        int x;
        int y;
        boolean type;
        ArrayList<section> ns = new ArrayList<>();

        public barrier(int val, int x, int y, boolean type, section[][][] s) {
            this.val = val;
            this.x = x;
            this.y = y;
            this.type = type;
            for (int i = 0; i < 4; i++) {
                ns.add(s[x][y][i]);
            }
        }

        @Override
        public int compareTo(prob10.barrier o) {
            return this.val - o.val;
        }
    }
}