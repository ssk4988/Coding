import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        
        String s = in.readLine();
        int left = 0;
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i) != '('){
                left++;
            }
            else{
                break;
            }
        }
        for(int i = s.length() - 1; i >= 0; i--){
            if(s.charAt(i)!=')'){
                left--;
            }
            else{
                break;
            }
        }
        if(left == 0){
            System.out.println("correct");
        }
        else{
            System.out.println("fix");
        }
        in.close();
        out.close();
    }
}