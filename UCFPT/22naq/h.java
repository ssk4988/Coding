import java.io.*;
import java.util.*;

public class h {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        int start = -1;
        for(int i= 0; i < n; i++){
            int val = Integer.parseInt(in.readLine());
            if(start == -1){
                start = val;
            }
            else{
                if(val % start == 0){
                    System.out.println(val);
                    start = -1;
                }
            }
        }
        in.close();
        out.close();
    }
}