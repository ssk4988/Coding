import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int i1 = Integer.parseInt(in.readLine());
        int i2 = Integer.parseInt(in.readLine());
        while(i2 < i1){
            i2 += 360;
        }
        int s1 = i2 - i1;
        int s2 = (360 - s1);
        if(s1 <= s2){
            System.out.println(s1);
        }
        else{
            System.out.println(-s2);
        }

        in.close();
        out.close();
    }
}