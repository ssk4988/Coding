import java.io.*;
import java.util.*;

public class p073 {
    static int[] solution;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s = in.readLine();
        int[] lengths = new int[51];
        int n = -1;
        for (int i = 1; i < lengths.length; i++) {
            lengths[i] = (i >= 10 ? 2 : 1) + lengths[i-1];
            if (lengths[i] == s.length()) {
                n = i;
                break;
            }
        }
        if (n == -1)
            return;
        boolean[] used = new boolean[n + 1];
        int[] perm = new int[n];
        solve(perm, 0, 0, used, s);
        for(int i = 0; i < n; i++){
            System.out.print(solution[i] + (i + 1 < n ? " " : "\n"));
        }
        in.close();
    }

    public static void solve(int[] perm, int depthS, int depth, boolean[] used, String s){
        if(depthS == s.length() && depth == perm.length && solution == null){
            solution = Arrays.copyOf(perm, perm.length);
            return;
        }
        if(perm[perm.length-1] > 0) return;
        if(depthS< s.length()){
            int c = s.charAt(depthS) - '0';
            if(c == 0) return;
            if(c < used.length && !used[c]){
                used[c] = true;
                perm[depth] = c;
                solve(perm, depthS+1, depth+1, used, s);
                used[c] = false;
                perm[depth] = 0;
            }
        }
        if(depthS + 1 < s.length()){
            int c = Integer.parseInt(s.substring(depthS, depthS+2));
            if(c < used.length && !used[c]){
                used[c] = true;
                perm[depth] = c;
                solve(perm, depthS+2, depth+1, used, s);
                used[c] = false;
                perm[depth] = 0;
            }
        }
    }
}