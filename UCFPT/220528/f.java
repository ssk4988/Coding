import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        StringBuilder out = new StringBuilder();
        while (!(line = in.readLine()).equals("0 0")) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            long[] offset = new long[n];
            int[] parent = new int[n];
            int[] sizes = new int[n];
            Arrays.fill(sizes, 1);
            Arrays.fill(parent, -1);
            for (int i = 0; i < m; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                if (tokenizer.nextToken().equals("!")) {
                    int a = Integer.parseInt(tokenizer.nextToken()) - 1;
                    int b = Integer.parseInt(tokenizer.nextToken()) - 1;
                    long w = Integer.parseInt(tokenizer.nextToken());
                    union(a, b, parent, sizes, offset, w);
                } else {
                    int a = Integer.parseInt(tokenizer.nextToken()) - 1;
                    int b = Integer.parseInt(tokenizer.nextToken()) - 1;
                    if (connected(parent, offset, a, b)) {
                        long bw = getWeight(parent, offset, b);
                        long aw = getWeight(parent, offset, a);
                        out.append((bw - aw) + "\n");
                    } else {
                        out.append("UNKNOWN\n");
                    }
                }
            }
        }
        System.out.print(out);
        in.close();
    }
    public static int getParent(int[] parent, long[] offset, int k){
        if(parent[k] == -1){
            return k;
        }
        else{
            parent[k] = getParent(parent, offset, parent[k]);
            offset[k] += offset[parent[k]];
            return parent[k];
        }
    }
    public static long getWeight(int[] parent, long[] offset, int k){
        getParent(parent, offset, k);
        return offset[k];
    }
    public static boolean connected(int[] parent, long[] offset, int a, int b){
        return getParent(parent, offset, a) == getParent(parent, offset, b);
    }
    public static boolean union(int a, int b, int[] parent, int[] sizes, long[] offset, long w){
        int ap = getParent(parent, offset, a);
        int bp = getParent(parent, offset, b);
        if(ap == bp)
            return false;
        if(sizes[ap] < sizes[bp]){
            int tmp = a;
            a = b;
            b = tmp;
            tmp = ap;
            ap = bp;
            bp = tmp;
            w *= -1;
        }
        parent[b] = a;
        sizes[ap] += sizes[bp];
        offset[b] = w + offset[a];
        return true;
    }
}