import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s1 = in.readLine();
        String key = in.readLine();
        for(int i = 0; i < s1.length(); i++){
            System.out.print((char)((s1.charAt(i) - 'A' + 52 + (i % 2 == 1 ? 1 : -1) * (key.charAt(i) - 'A'))%26+'A'));
        }
        System.out.println();
        in.close();
    }
}