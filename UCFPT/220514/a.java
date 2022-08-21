import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while(!(line = in.readLine()).equals("-1")){
            int n = Integer.parseInt(line);
            int dist = 0;
            int t = 0;
            for(int i = 0; i <n ; i++){
                StringTokenizer tokenizer =new StringTokenizer(in.readLine());
                int s = Integer.parseInt(tokenizer.nextToken());
                int t2  = Integer.parseInt(tokenizer.nextToken());
                dist += (t2 - t) * s;
                t = t2;
            }
            System.out.println(dist + " miles");
        }
        in.close();
    }
}