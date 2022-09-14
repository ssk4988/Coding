import java.io.*;
import java.util.*;

public class easyexpr {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int a = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        int c = Integer.parseInt(tokenizer.nextToken());
        int sum = a + b + c;
        int product = a * b * c;
        if(a * 2 == sum || b * 2 == sum || c * 2 == sum){
            System.out.println(1);
        }
        else if (a * a == product || b * b == product || c * c == product){
            System.out.println(2);
        }
        else{
            System.out.println(3);
        }
        in.close();
    }
}