import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        boolean[][] knight = new boolean[5][5];
        int cnt = 0;
        for(int i = 0; i < 5; i++){
            String s = in.readLine();
            for(int j = 0; j < 5; j++){
                knight[i][j] = s.charAt(j) == 'k';
                if(knight[i][j]) cnt++;
            }
        }
        boolean valid = cnt == 9;
        int[] dx = new int[]{1, 1, -1, -1, 2, 2, -2, -2};
        int[] dy = new int[]{2, -2, 2, -2, 1, -1, 1, -1};
        for(int i = 0; i < 5; i++){
            for(int j = 0; j< 5; j++){
                if(!knight[i][j]) continue;
                for(int k = 0; k < dx.length; k++){
                    if(i + dx[k] >= 0 && i + dx[k] < 5 && j + dy[k] >= 0 && j + dy[k] < 5 && knight[i + dx[k]][j + dy[k]]){
                        valid = false;
                    }
                }
            }
        }
        System.out.println(valid ? "valid" : "invalid");
        in.close();
    }
}