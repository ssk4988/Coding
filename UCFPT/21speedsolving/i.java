import java.io.*;
import java.util.*;

public class i {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        if(n%4==0){
            System.out.println("Even");
        }
        else if(n % 2 == 1){
            System.out.println("Either");
        }
        else{
            System.out.println("Odd");
        }
        in.close();
        out.close();
    }
}