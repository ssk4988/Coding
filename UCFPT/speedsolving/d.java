import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int i = Integer.parseInt(in.readLine());
        if(i>=5550000 && i <= 5559999){
            System.out.println(1);
        }
        else{
            System.out.println(0);
        }

        in.close();
        out.close();
    }
}