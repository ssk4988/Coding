import java.io.*;
import java.util.*;

public class graycode {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        boolean[] used = new boolean[1 << n];
        StringBuilder b = new StringBuilder();
        int start = 0;
        while(true){
            if(used[start]) break;
            used[start] = true;
            String s = Integer.toBinaryString(start);
            int diff = n - s.length();
            for(int i = 0; i < diff; i++){
                b.append('0');
            }
            b.append(s);
            b.append("\n");
            for(int i = 0; i < n; i++){
                int next = start ^ (1 << i);
                if(!used[next]){
                    start = next;
                    break;
                }
            }
        }
        System.out.print(b);
        in.close();
    }
}