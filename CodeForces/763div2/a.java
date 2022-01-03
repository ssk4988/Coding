import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numCases = Integer.parseInt(in.readLine());
        for(int casenum = 0; casenum < numCases; casenum++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numRows = Integer.parseInt(tokenizer.nextToken());
            int numCols = Integer.parseInt(tokenizer.nextToken());
            int rowr = Integer.parseInt(tokenizer.nextToken());
            int colr = Integer.parseInt(tokenizer.nextToken());
            int rowd = Integer.parseInt(tokenizer.nextToken());
            int cold = Integer.parseInt(tokenizer.nextToken());
            int catchX = Math.abs(rowr-rowd);
            if(rowr>rowd) catchX+=2*(numRows-rowr);
            int catchY = Math.abs(colr-cold);
            if(colr>cold) catchY+=2*(numCols-colr);
            System.out.println(Math.min(catchX, catchY));
        }

        in.close();
        out.close();
    }
}