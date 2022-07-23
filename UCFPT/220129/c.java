import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum<numcases;casenum++){
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int y1 = Integer.parseInt(tokenizer.nextToken());
            int y2 = Integer.parseInt(tokenizer.nextToken());
            int count = 0;
            for(int i = y1; i<=y2;i++){
                if(i%4!=0)continue;
                if(i%400==0)count++;
                else if(i%100 != 0 && i%4==0)count++;
            }
            if(count ==1){
                System.out.println("There is " + count + " leap year from " + y1 + " to " + y2 + ".");
            }
            else{
                System.out.println("There are " + count + " leap years from " + y1 + " to " + y2 + ".");
            }
        }

        in.close();
        out.close();
    }
}