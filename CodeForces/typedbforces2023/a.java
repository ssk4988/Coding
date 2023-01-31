import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int nc = Integer.parseInt(in.readLine());
        for(int cn = 0; cn < nc; cn++){
            int n = Integer.parseInt(in.readLine());
            if(n%2 == 0){
                System.out.println(n/2 + " " + 1);
            }
            else{
                System.out.println(-1);
            }
        }
        in.close();
    }
}
