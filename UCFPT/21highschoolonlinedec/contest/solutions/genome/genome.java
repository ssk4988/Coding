package solutions.genome;

import java.util.Scanner;

public class genome {

    static final long MOD = (long) (1e9 + 7);

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int testCases = scan.nextInt();
        for(int i = 1; i <= testCases; i++) {
            char[][] pattern = new char[4][];
            for(int j = 0; j < 4; j++) pattern[j] = scan.next().toCharArray();
            char[] initial = scan.next().toCharArray();
            int[] initialFreq = new int[4];
            long n = scan.nextLong();
            String alpha = "ACTG";

            for(char x : initial) initialFreq[alpha.indexOf(x)]++;
            long[][] mat = new long[4][4];
            for(int j = 0; j < 4; j++) {
                for(char x : pattern[j]) {
                    mat[j][alpha.indexOf(x)]++;
                }
            }
            long[][] res = matrixExpo(mat, n);
            long[] ans = new long[4];
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 4; k++) {
                    ans[k] += initialFreq[j] * res[j][k];
                    ans[k] %= MOD;
                }
            }
            System.out.print("Genome #" + i + ": ");
            for(int j = 0; j < 4; j++) System.out.print(ans[j] + " ");
            System.out.println();
        }
        scan.close();
    }

    static long[][] matrixMultiply(long[][] mat1, long[][] mat2) {
        long[][] res = new long[mat1.length][mat2[0].length];
        for(int i = 0; i < res.length; ++i) {
            for(int j = 0; j < res[i].length; ++j) {
                for(int k = 0; k < mat2.length; ++k) {
                    res[i][j] += mat1[i][k] * mat2[k][j];
                    res[i][j] %= MOD;
                }
            }
        }
        return res;
    }

    static long[][] matrixExpo(long[][] mat, long expo) {
        if(expo == 0)
            return identity(mat.length);
        if(expo == 1)
            return mat;
        long[][] ret = matrixExpo(mat, expo/2);
        ret = matrixMultiply(ret, ret);
        if(expo % 2 == 1)
            ret = matrixMultiply(ret, mat);
        return ret;
    }

    static long[][] identity(int size) {
        long[][] mat = new long[size][size];
        for(int i = 0; i < size; ++i)
            mat[i][i] = 1;
        return mat;
    }

}
