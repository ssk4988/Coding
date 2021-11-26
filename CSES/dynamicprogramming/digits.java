import java.io.*;
import java.util.*;

public class digits {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int start = Integer.parseInt(in.readLine());
        boolean[] reachable = new boolean[start + 1];
        int[] steps = new int[start + 1];
        reachable[start] = true;
        for(int i = start; i >= 0; i--){
            if(!reachable[i]){
                continue;
            }
            String s = i + "";
            for(char c : s.toCharArray()){
                int digit = c - '0';
                if(digit == 0 || i - digit < 0){
                    continue;
                }
                if(!reachable[i - digit]){
                    reachable[i - digit] = true;
                    steps[i - digit] = Integer.MAX_VALUE;
                }
                if(steps[i] + 1 < steps[i - digit]){
                    steps[i - digit] = steps[i] + 1;
                }
            }
        }
        System.out.println(steps[0]);

        in.close();
    }
}