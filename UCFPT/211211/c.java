import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer =new StringTokenizer(in.readLine());
        int reports = Integer.parseInt(tokenizer.nextToken());
        int floors = Integer.parseInt(tokenizer.nextToken());
        int maxSafe = 1;
        int minBroken = floors;
        for(int i = 0; i < reports; i++){
            tokenizer = new StringTokenizer(in.readLine());
            int floor = Integer.parseInt(tokenizer.nextToken());
            boolean safe = tokenizer.nextToken().equals("SAFE");
            if(safe){
                maxSafe = Math.max(maxSafe, floor);
            }
            else{
                minBroken = Math.min(minBroken, floor);
            }
        }
        int notbreak= Math.max(maxSafe, minBroken - 1);
        int broke = Math.min(minBroken, maxSafe+1);
        System.out.println(broke + " " + notbreak);
        

        in.close();
    }
}