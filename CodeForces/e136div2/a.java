import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        int[] dx = {1, 1, 2, 2, -1, -1, -2, -2};
        int[] dy = {2, -2, 1, -1, 2, -2, 1, -1};
        cases: for(int cn = 0; cn  < nc; cn++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            check: for(int i = 1; i <= n; i++){
                for(int j = 1; j <= m; j++){
                    boolean works = false;
                    for(int k = 0; k < dx.length; k++){
                        if(i + dx[k] >=1 && i + dx[k] <= n && j + dy[k] >= 1 && j + dy[k] <= m){
                            works = true;
                            break;
                        }
                    }
                    if(!works){
                        System.out.println(i + " " + j);
                        continue cases;
                    }
                }
            }
            System.out.println("1 1");
        }
        in.close();
    }
}