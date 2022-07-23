import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String s = in.readLine();
        int a = 0;
        int b = 0;
        boolean wincondition = false;
        for (int i = 0; i < s.length(); i += 2) {
            boolean type = s.charAt(i) == 'A';
            int score = s.charAt(i + 1) - '0';
            if (type) {
                a += score;
            } else {
                b += score;
            }
        }
        if(a > b){
            System.out.println("A");
        }
        else{
            System.out.println("B");
        }

        in.close();
        out.close();
    }
}