import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int m = Integer.parseInt(tokenizer.nextToken());
        int n = Integer.parseInt(tokenizer.nextToken());
        boolean[][] land = new boolean[m][n];
        int[] dx = {1, 0, -1, 0, 1, 1, -1, -1};
        int[] dy = {0, 1, 0, -1, 1, -1, 1, -1};
        for(int i = 0; i < m; i++){
            tokenizer = new StringTokenizer(in.readLine());
            for(int j = 0; j < n; j++){
                land[i][j] = Integer.parseInt(tokenizer.nextToken()) == 1;
            }
        }
        long inter = 0;
        long adj = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(!land[i][j]) continue;
                for(int k = 0; k < dx.length; k++){
                    if(i + dx[k] >= m || i + dx[k] < 0 || j + dy[k] >= n || j + dy[k] <0) continue;
                    if(land[i+dx[k]][j+dy[k]]){
                        inter++;
                        if(k<4) adj++;
                    }
                }
            }
        }
        adj/=2;
        inter/=2;
        System.out.println(adj + " " + inter);
        in.close();
        out.close();
    }
    public static class sq{
        int x = 0;
        int y = 0;
        boolean land = false;
        ArrayList<sq> n1 = new ArrayList<>();
        ArrayList<sq> n2 = new ArrayList<>();
    }
}