import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int n = Integer.parseInt(in.readLine());
        for (int i = 0; i < n; i++) {
            int k = Integer.parseInt(in.readLine());
            if(k % 2 == 0){
                b.append("0 " + (k/2) + " " + (k/2) + "\n");
            }
            else{
                b.append("-1\n");
            }
        }
        System.out.print(b);
        in.close();
    }
}