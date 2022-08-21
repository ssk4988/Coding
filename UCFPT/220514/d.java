import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        while(true){
            int sum = 0;
            int i = n;
            while(i > 0){
                sum += i % 10;
                i/=10;
            }
            if(n % sum == 0){
                break;
            }
            n++;
        }
        System.out.println(n);
        in.close();
    }
}