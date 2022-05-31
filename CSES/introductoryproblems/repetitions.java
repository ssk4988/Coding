import java.io.*;
import java.util.*;

public class repetitions {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s = in.readLine();
        char prev = ' ';
        int max = 0;
        int curr = 0;
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i)==prev){
                curr++;
            }
            else{
                prev = s.charAt(i);
                curr = 1;
            }
            if(curr > max){
                max = curr;
            }
        }
        System.out.println(max);
        in.close();
    }
}