import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int a = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        int cnt = 0;
        while(a != b){
            if(a > b){
                if(a%2==0){
                    a/=2;
                }else{
                    a++;
                }
            }
            else{
                a++;
            }
            cnt++;
        }
        System.out.println(cnt);

        in.close();
        out.close();
    }
}