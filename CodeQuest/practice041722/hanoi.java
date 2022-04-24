import java.io.*;
import java.util.*;

public class hanoi {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b= new StringBuilder();
        for(int casenum = 0; casenum < numcases; casenum++){
            int n = Integer.parseInt(in.readLine());
            b.append(n+"\n");
            solve(n, 'A', 'B', 'C', b);
        }
        System.out.print(b);

        in.close();
        out.close();
    }
    public static void solve(int n, char source, char aux, char dest, StringBuilder b){
        if(n == 1){
            b.append(source+"->"+dest+"\n");
        }
        else{
            solve(n-1, source, dest, aux, b);
            b.append(source+"->"+dest+"\n");
            solve(n-1, aux, source, dest, b);
        }
    }
}