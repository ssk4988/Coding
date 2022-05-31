import java.io.*;
import java.util.*;

public class hanoi {
    public static int moves = 0;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        solve(n, 1, 2, 3, b);
        System.out.println(moves);
        System.out.print(b);
        in.close();
    }
    public static void solve(int n, int source, int aux, int dest, StringBuilder b){
        if(n == 1){
            b.append(source + " " + dest + "\n");
            moves++;
            return;
        }
        solve(n-1, source, dest, aux, b);
        b.append(source + " " + dest + "\n");
        moves++;
        solve(n-1, aux, source, dest, b);
    }
}