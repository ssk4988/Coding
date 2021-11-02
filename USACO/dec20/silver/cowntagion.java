import java.io.*;
import java.util.*;

public class cowntagion {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        int numFarms = Integer.parseInt(in.readLine());
        int[] neighbors = new int[numFarms];
        for (int i = 0; i < numFarms - 1; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            neighbors[first]++;
            neighbors[second]++;
        }
        int numDays = numFarms - 1;
        for(int i = 0; i < numFarms; i++){
            if(neighbors[i] > 1 || i == 0){
                if(i != 0){
                    neighbors[i]--;
                }
                numDays += (int)Math.ceil(Math.log(neighbors[i] + 1) / Math.log(2));
            }
        }
        System.out.println(numDays);

        in.close();
        // out.close();
    }
}