import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int winner = 0;
        for(int i = 1; i < n; i++){
            int k = query(in, i, winner, n);
            if(k == 1){
                winner = i;
            }
        }
        boolean[] win = new boolean[n];
        win[winner] = true;
        for(int i = 0; i < n; i++){
            if(i == winner) continue;
            int k = query(in, i, winner, n);
            if(k == 1) win[i] = true;
        }
        System.out.print("!");
        for(int i = 0; i < n; i++){
            System.out.print(" " + (win[i] ? 1 : 0));
        }
        System.out.println();
        System.out.flush();
        in.close();
    }
    static int query(Scanner in, int f, int s, int n){
        System.out.print("? " + (f + 1));
        for(int i = 0; i < s; i++){
            System.out.print(0 + " ");
        }
        System.out.print(1);
        for(int i = s + 1; i < n; i++){
            System.out.print(" " + 0);
        }
        System.out.println();
        System.out.flush();
        int k = in.nextInt();
        return k;
    }
}