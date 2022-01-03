import java.io.*;
import java.util.*;

public class e {
    public static int[] dx = { 1, 0, -1, 0 };
    public static int[] dy = { 0, 1, 0, -1 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringBuilder b = new StringBuilder();
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int m = Integer.parseInt(tokenizer.nextToken());
            int n = Integer.parseInt(tokenizer.nextToken());
            sq[][] board = new sq[m][n];
            sq lab = null;
            for (int i = 0; i < m; i++) {
                String s = in.readLine();
                for (int j = 0; j < n; j++) {
                    board[i][j] = null;
                    if(s.charAt(j)!='#'){
                        board[i][j] = new sq(i, j, s.charAt(j) == 'L');
                        if(board[i][j].isLab){
                            lab = board[i][j];
                            board[i][j].force = true;
                        }
                    }
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if(board[i][j] == null) continue;
                    for(int k = 0; k < dx.length; k++){
                        int di = i + dx[k];
                        int dj = j + dy[k];
                        board[i][j].near[k] = null;
                        if(di >= 0 && di < m && dj >= 0 && dj < n){
                            board[i][j].near[k] = board[di][dj];
                            if(board[di][dj] != null){
                                board[i][j].numValid++;
                                if(board[di][dj].isLab){
                                    board[i][j].numForce++;
                                }
                            }
                        }
                        
                    }
                }
            }
            Queue<sq> queue = new ArrayDeque<>();
            for(sq s : lab.near){
                if(s != null){
                    queue.add(s);
                }
            }
            while(!queue.isEmpty()){
                sq s = queue.poll();
                if(!s.force && s.numForce+1>= s.numValid){
                    s.force = true;
                    for(sq ne : s.near){
                        if(ne!=null){
                            ne.numForce++;
                            queue.add(ne);
                        }
                    }
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if(board[i][j] == null){
                        b.append('#');
                    }
                    else if(board[i][j].isLab){
                        b.append('L');
                    }
                    else if(board[i][j].force){
                        b.append('+');
                    }
                    else{
                        b.append('.');
                    }
                }
                b.append("\n");
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }

    public static class sq {
        int r;
        int c;
        sq[] near = new sq[4];
        boolean isLab = false;
        boolean force = false;
        int numValid = 0;
        int numForce = 0;

        public sq(int r, int c, boolean isLab) {
            this.r = r;
            this.c = c;
            this.isLab = isLab;
        }
    }
}