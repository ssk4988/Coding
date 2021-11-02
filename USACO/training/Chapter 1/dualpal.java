/*
ID: ssk49881
LANG: JAVA
TASK: dualpal
*/

import java.io.*;
import java.util.*;

public class dualpal {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("dualpal.in"));
        PrintWriter out = new PrintWriter(new File("dualpal.out"));
        String line = in.nextLine();
        int n = Integer.parseInt(line.split(" ")[0]);
        int s = Integer.parseInt(line.split(" ")[1]);
        int[] solutions = new int[n];
        int currentnumsolutions = 0;
        for(int i = s + 1; currentnumsolutions < n; i++){
            int palBases = 0;
            for(int b = 2; b <= 10; b++){
                if(isPal(convertBase(b, i))){
                    palBases++;
                }
                if(palBases >= 2){
                    solutions[currentnumsolutions] = i;
                    currentnumsolutions++;
                    break;
                }
            }
        }
        for(int solution: solutions){
            out.println(Integer.toString(solution));
        }

        in.close();
        out.close();
    }
    public static boolean isPal(String num){
        boolean matches = true;
        if(num.length() == 1){
            return true;
        }
        for(int i = 0; i < num.length() -1 - i; i++){
            if(num.charAt(i) != num.charAt(num.length() -1 - i)){
                matches = false;
            }
        }
        return matches;
    }

    public static String convertBase(int b, int num){
        String[] digits = "0123456789ABCDEFGHIJKL".split("");
        int copy = num;
        String newNum = "";
        for(int i = (int) Math.floor(Math.log(num) / Math.log(b)); i >= 0; i--){
            newNum = newNum + digits[copy / (int)Math.pow(b, i)];
            copy -= (copy / (int)Math.pow(b, i)) * (int)Math.pow(b, i);
        }
        return newNum;
    }
}