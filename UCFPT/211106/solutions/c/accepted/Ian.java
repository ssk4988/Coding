import java.util.Arrays;
import java.util.Scanner;

/**
 *
 * @author mbassip2
 */
public class Ian {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String input;

        Scanner sc = new Scanner(System.in);
        input= sc.nextLine();
        Scanner sc1 = new Scanner(input);
        int n= sc1.nextInt();
        int c= sc1.nextInt();
        int halfC= c/2;
        int[] weights= new int[n];
        input= sc.nextLine();
        sc1 = new Scanner(input);
        for(int i= 0; i<n; i++)
            weights[i]= sc1.nextInt();

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
