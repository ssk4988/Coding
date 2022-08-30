import java.io.*;
import java.util.*;

public class majestic {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int cnt = 0;
        for (int i = 0; i < 3; i++) {
            if (Integer.parseInt(tokenizer.nextToken()) >= 10)
                cnt++;
        }
        if(cnt == 0){
            System.out.println("zilch");
        }
        if(cnt == 1){
            System.out.println("double");
        }
        if(cnt == 2){
            System.out.println("double-double");
        }
        if(cnt == 3){
            System.out.println("triple-double");
        }
        in.close();
    }
}