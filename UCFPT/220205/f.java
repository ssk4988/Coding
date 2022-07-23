import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        if(n % 2 == 1){
            System.out.println("0");
        }
        else{
            if(n % 4 != 0){
                System.out.println("1");
            }
            else{
                System.out.println("2");
            }
        }

        in.close();
        out.close();
    }
}