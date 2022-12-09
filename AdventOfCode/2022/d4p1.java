import java.io.*;
import java.util.*;

public class d4p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String line;
        int ans = 0;
        while(!(line = in.readLine()).equals("0")){
            String[] sp = line.split(",");
            int a = Integer.parseInt(sp[0].split("-")[0]);
            int b = Integer.parseInt(sp[0].split("-")[1]);
            int c = Integer.parseInt(sp[1].split("-")[0]);
            int d = Integer.parseInt(sp[1].split("-")[1]);
            //if(a <= c && d <= b || c <= a && b <= d){
            if(a <= c && c <= b || a <= d && d <= b){
                ans++;
            }
            else if(a <= c && d <= b || c <= a && b <= d){
                ans++;
            }
        }
        System.out.println(ans);
        in.close();
    }

}
