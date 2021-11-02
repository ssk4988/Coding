/*
ID: ssk49881
LANG: JAVA
TASK: palsquare
*/

import java.io.*;
import java.util.*;

public class palsquare {
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("palsquare.in"));
        PrintWriter out = new PrintWriter(new File("palsquare.out"));
        int b = Integer.parseInt(in.nextLine());

        for(int i = 1; i <= 300; i++){
            String num = convertBase(b, i * i);
            if(isPal(num)){
                out.println(convertBase(b, i) + " " + num);
            }
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