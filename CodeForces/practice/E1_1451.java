import java.io.*;
import java.util.*;

public class E1_1451 {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new InputStreamReader(System.in));
        StringBuilder b = new StringBuilder();
        int n = in.nextInt();
        int[] vals = new int[3];
        int[][] q = {{0, 1}, {0, 2}, {1, 2}};
        boolean[][] known = new boolean[3][17];
        int[] xor = new int[3];
        int[] and = new int[3];
        for(int i = 0; i < 3; i++){
            xor[i] = i < 2 ? query(in, "XOR", q[i][0], q[i][1]) : xor[0] ^ xor[1];
            and[i] = query(in, "AND", q[i][0], q[i][1]);
        }
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 17; j++){
                if((xor[i] & (1 << j)) == 0){
                    int k = and[i] & (1 << j);
                    for(int l = 0; l < 2; l++){
                        known[q[i][l]][j] = true;
                        if(k == 0){
                            vals[q[i][l]] &= ~(1 << j);
                        }
                        else{
                            vals[q[i][l]] |= k;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 17; j++){
                if(known[q[i][0]][j] == known[q[i][1]][j]) continue;
                int kn = q[i][0], ukn = q[i][1];
                if(known[ukn][j]){
                    kn = ukn;
                    ukn = 1 - kn;
                }
                int bit = (1 << j) & vals[kn];
                if((xor[i] & (1 << j)) > 0){
                    bit ^= (1 << j);
                }
                if(bit > 0){
                    vals[ukn] |= bit;
                }
                else{
                    vals[ukn] &= ~(1 << j);
                }
                known[ukn][j] = true;
            }
        }
        int[] a = new int[n];
        for(int i = 0; i < 3; i++){
            a[i] = vals[i];
        }
        for(int i = 3; i < n; i++){
            int v = query(in, "XOR", 0, i);
            a[i] = v ^ a[0];
        }
        b.append("!");
        for(int i = 0; i < n; i++){
            b.append(" " + a[i]);
        }
        b.append("\n");

        System.out.print(b);
        System.out.flush();
        in.close();
    }

    public static int query(Scanner in, String type, int a, int b){
        a++;b++;
        System.out.println(type + " " + a + " " + b);
        System.out.flush();
        int val = in.nextInt();
        return val;
    }
}
