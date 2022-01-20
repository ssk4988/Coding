import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        c: for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int[] t = new int[n];
            group[] g = new group[m];
            group[] sorted = new group[m];
            tokenizer = new StringTokenizer(in.readLine());
            int max = 100000;
            int totalStudents = 0;
            for (int i = 0; i < n; i++) {
                t[i] = Integer.parseInt(tokenizer.nextToken());
            }
            Arrays.sort(t);
            for (int i = 0; i < m; i++) {
                g[i] = new group(i, Integer.parseInt(in.readLine()));
                sorted[i] = g[i];
                totalStudents += g[i].numStudents;
                tokenizer = new StringTokenizer(in.readLine());
                for (int j = 0; j < g[i].numStudents; j++) {
                    g[i].ages[j] = Integer.parseInt(tokenizer.nextToken());
                    g[i].sum += g[i].ages[j];
                }
                g[i].mean = (int) ((g[i].sum + g[i].numStudents - 1) / g[i].numStudents);
            }
            Arrays.sort(sorted);
            int[] tp = new int[max + 1];
            for (int i = 0; i < t.length; i++) {
                tp[t[i]]++;
            }
            for (int i = tp.length - 1; i > 0; i--) {
                tp[i - 1] += tp[i];
            }
            int[] gp = new int[max + 1];
            for (int i = 0; i < g.length; i++) {
                gp[g[i].mean]++;
            }
            for (int i = gp.length - 1; i > 0; i--) {
                gp[i - 1] += gp[i];
            }
            int inv = -1;
            for (int i = 0; i < gp.length; i++) {
                if (gp[i] - 1 > tp[i]) {
                    for (int j = 0; j < totalStudents; j++) {
                        b.append('0');
                    }
                    b.append("\n");
                    continue c;
                }
                if (inv == -1 && gp[i] - 1 == tp[i]) {
                    inv = i;
            boolean[][] w = new boolean[3][n];
            int dif = n - m;
            int[][] pre = new int[3][n];
            for (int j = -1; j < 2; j++) {
                for (int i = 0; i < g.length; i++) {
                    if (i + j < 0) {
                        w[j + 1][i] = true;
                    }
                    else if(i + j >= g.length){
                        w[j+1][i] = false;
                    } 
                    else {
                        w[j + 1][i] = g[i].mean <= t[dif + i + j];
                    }
                    if (!w[j + 1][i]) {
                        pre[j + 1][i]++;
                    }
                }
            }
            int a = 1;
            for (int i = 0; i < pre.length; i++) {
                for (int j = 1; j < pre[i].length; j++) {
                    pre[i][j] += pre[i][j - 1];
                }
            }
            for (int i = 0; i < g.length; i++) {
                for (int j = 0; j < g[i].numStudents; j++) {
                    int mean = (int) ((g[i].sum - g[i].ages[j] + g[i].numStudents - 2) / (g[i].numStudents - 1));
                    if ((inv == -1 && (mean <= g[i].mean || gp[mean] + 1 <= tp[mean]))
                            || (g[i].mean >= inv && mean < inv)) {
                        b.append('1');
                    } else {
                        b.append('0');
                    }
                    boolean works = true;
                    int index = findFirst(g, mean);
                    //redo
                    int left = Math.min(index, i) > 0 ? pre[1][Math.min(index, i) - 1] : 0;
                    //redo
                    int right = pre[1][pre[1].length - 1] - pre[1][Math.min(Math.max(index, i), pre[1].length - 1)];
                    int mid = 0;
                    if(index < i){
                        mid = pre[2][i-1] - (index > 0 ? pre[2][index - 1] : 0);
                    }
                    if(i < index){
                        mid = pre[0][index - 1] - (i > 0 ? pre[0][i-1] : 0);
                    }
                    if(mean > t[t.length - 1]) mid++;
                    if(left + right + mid > 0){
                        b.append('0');
                    }
                    else{
                        b.append('1');
                    }
                }
            }
            b.append("\n");
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static class group implements Comparable<group> {
        int id;
        int numStudents;
        int[] ages;
        int mean = 0;
        long sum = 0;

        public group(int id, int numStudents) {
            this.id = id;
            this.numStudents = numStudents;
            ages = new int[numStudents];
        }

        @Override
        public int compareTo(e.group o) {
            return this.mean - o.mean;
        }
    }

    public static int findFirst(group[] arr, int mean) {
        int low = 0;
        int high = arr.length;

        while (low < high) {
            int mid = low + (high - low) / 2;
            if (mean - arr[mid].mean <= 0) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
}