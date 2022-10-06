import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int d = Integer.parseInt(tokenizer.nextToken()); // dist
        int g = Integer.parseInt(tokenizer.nextToken()); // num grabs
        int[][] c = new int[n][2];
        for (int i = 0; i < n; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            c[i][0] = Integer.parseInt(tokenizer.nextToken());
            c[i][1] = Integer.parseInt(tokenizer.nextToken());
        }
        ArrayList<edge> es = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            tryedge: for (int j = i + 1; j < n; j++) {
                int[] dc = { c[j][0] - c[i][0], c[j][1] - c[i][1] };
                boolean set = false;
                boolean pos = false;
                for (int k = 0; k < n; k++) {
                    if (k == i || k == j)
                        continue;
                    int[] ca = { c[k][0] - c[i][0], c[k][1] - c[i][1] };
                    int cp = dc[0] * ca[1] - dc[1] * ca[0];
                    if (!set) {
                        set = true;
                        pos = cp > 0;
                    }
                    if ((cp > 0) != pos) {
                        continue tryedge;
                    }
                }
                edge e1 = new edge(i, j);
                es.add(e1);
            }
        }
        if (es.size() != n)
            throw new Exception("bruh");
        ArrayList<Integer> vs = new ArrayList<>();
        vs.add(0);
        int prev = -1;
        double perimeter = 0;
        while (vs.size() < n) {
            int i = vs.size() - 1;
            for (edge e1 : es) {
                if (e1.v1 == vs.get(i) && e1.v2 != prev) {
                    vs.add(e1.v2);
                    // perimeter += Math.sqrt(Math.pow(c[e1.v1][0] - c[e1.v2][0], 2) +
                    // Math.pow(c[e1.v1][1] - c[e1.v2][1], 2));
                    break;
                } else if (e1.v2 == vs.get(i) && e1.v1 != prev) {
                    vs.add(e1.v1);
                    // perimeter += Math.sqrt(Math.pow(c[e1.v1][0] - c[e1.v2][0], 2) +
                    // Math.pow(c[e1.v1][1] - c[e1.v2][1], 2));
                    break;
                }
            }
            prev = vs.get(i);
        }
        //System.out.println(perimeter);
        double area = 0;
        for (int i = 0; i < vs.size(); i++) {
            int j = i + 1;
            if (j >= vs.size())
                j = 0;
            area += c[vs.get(i)][0] * c[vs.get(j)][1];
            area -= c[vs.get(i)][1] * c[vs.get(j)][0];
            perimeter += Math.sqrt(
                    Math.pow(c[vs.get(i)][0] - c[vs.get(j)][0], 2) + Math.pow(c[vs.get(i)][1] - c[vs.get(j)][1], 2));
        }

        area = Math.abs(area) / 2;
        //System.out.println(area);
        area += perimeter * d * g;
        area += Math.PI * Math.pow(d * g, 2);
        System.out.println(area);
        in.close();
    }

    static class edge {
        int v1, v2;

        public edge(int v1, int v2) {
            this.v1 = v1;
            this.v2 = v2;
        }
    }
}