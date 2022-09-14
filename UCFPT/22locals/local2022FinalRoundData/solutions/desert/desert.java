
import java.util.*;
import java.io.*;

public class desert {

    public static void main(String[] Args) throws Exception {
        FS sc = new FS(System.in);
        int n = sc.nextInt();
        long[][] locs = new long[n][2];
        for (int i = 0; i < n; i++) {
            locs[i][0] = sc.nextInt();
            locs[i][1] = sc.nextInt();
        }

        ArrayList<Edge> elist = new ArrayList<Edge>();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                long dx = locs[i][0]-locs[j][0];
                long dy = locs[i][1]-locs[j][1];
                Edge e = new Edge(dx*dx+dy*dy,i,j);
                elist.add(e);
            }
        }
        Collections.sort(elist);

        DS ds = new DS(n);
        for (Edge e : elist)
            ds.merge(e.dist, e.i1, e.i2);
        
        ArrayList<Integer> oIndices = ds.indices[ds.find(0)];
        ArrayList<Long> weights = ds.weights[ds.find(0)];
        int[] indexOf = new int[n];
        for (int i = 0; i < n; i++)
            indexOf[oIndices.get(i)] = i;
        
        long[][] table = new long[14][n-1];
        for (int i = 0; i < n-1; i++)
            table[0][i] = weights.get(i);

        for (int j = 1; (1<<(j-1)) < n-1; j++) {
            for (int i = 0; i < n-1; i++) {
                table[j][i] = table[j-1][i];
                int ii = (i+(1<<(j-1)));
                if (ii < n - 1&& table[j][i] < table[j-1][ii])
                    table[j][i] = table[j-1][ii];
            }
        }

        PrintWriter out = 
                new PrintWriter(new BufferedWriter(
                new OutputStreamWriter(System.out)));

        int q = sc.nextInt();
        int[] lookup = new int[n+1];
        int j = 0;
        for (int i = 0; i <= n; i++) {
            if ((1<<(j+1)) < i)
                j++;
            lookup[i] = j;
        }
        for (int i = 0; i < q; i++) {
            int a = indexOf[sc.nextInt()-1], b = indexOf[sc.nextInt()-1];
            if (a > b){
                a ^= b;
                b ^= a;
                a ^= b;
            }
            j = lookup[b-a];
//            while ((1<<(j+1)) < (b-a))
//                j++;
            long a1 = table[j][a];
            long a2 = table[j][b-(1<<j)];
            out.println(Math.sqrt((a1<a2)?a2:a1));
        }
        out.close();
    }

    public static class DS {
        int[] p;
        ArrayList<Long>[] weights;
        ArrayList<Integer>[] indices;
        DS(int n) {
            p = new int[n];
            weights = new ArrayList[n];
            indices = new ArrayList[n];
            for (int i = 0; i < n; i++) {
                p[i] = -1;
                weights[i] = new ArrayList<Long>();
                indices[i] = new ArrayList<Integer>();
                indices[i].add(i);
            }
        }
        int find(int x) {
            return (p[x] < 0) ? x : (p[x] = find(p[x]));
        }
        void merge(long dist, int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (p[a] > p[b]) {
                a ^= b;
                b ^= a;
                a ^= b;
            }

            weights[a].add(dist);
            for (Long x : weights[b])
                weights[a].add(x);
            for (Integer x : indices[b])
                indices[a].add(x);
            
            p[a] += p[b];
            p[b] = a;
        }
    }

    public static class Edge implements Comparable<Edge>{
        long dist;
        int i1, i2;
        Edge(long d, int a, int b) {
            dist = d;
            i1 = a;
            i2 = b;
        }
        public int compareTo(Edge o) {
            return Long.compare(dist, o.dist);
        }
    }
    
    public static class FS {
        BufferedReader br;
        StringTokenizer st;

        FS(InputStream in) throws Exception{
            br = new BufferedReader(new InputStreamReader(in));
            st = new StringTokenizer(br.readLine());
        }

        String next() throws Exception {
            if (st.hasMoreTokens())
                return st.nextToken();
            st = new StringTokenizer(br.readLine());
            return next();
        }

        int nextInt() throws Exception {
            return Integer.parseInt(next());
        }
    }
}
