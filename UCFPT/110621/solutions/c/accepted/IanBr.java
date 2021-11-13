import java.io.*;
import java.util.*;
import java.util.stream.*;

/**
 *
 * @author mbassip2
 */
public class IanBr {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        final BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        final String input = br.readLine();
        Scanner sc1 = new Scanner(input);
        int n= sc1.nextInt();
        int c= sc1.nextInt();
        int halfC= c/2;

        int[] weights = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(weights);

        int ans= 0; // number of drones required
        int i= n-1;  // Start with the heavist book
        int j= 0; // Index of lightest book
        while(i > j){
            if(weights[j] > (c - weights[i])){ //Lower and successors too large
                ans++;                         //Current upper goes on its own
                i--;
            }
            else{//Pair the heaviest with the lightest
                j++;
                i--;
                ans++;
            }
        }
        if(i==j)               // Last one
            ans++;
        System.out.println(ans);
    }

}
