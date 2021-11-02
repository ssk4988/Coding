/*
ID: ssk49881
LANG: JAVA
TASK: prefake
*/

import java.io.*;
import java.util.*;

public class prefake {
    public static String[] numerals;
    public static HashMap<String, Integer> hashMap;

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("prefake.in"));
        PrintWriter out = new PrintWriter(new File("prefake.out"));
        int pages = Integer.parseInt(in.nextLine());
        int maxPages = 3500;
        numerals = new String[maxPages + 1];
        hashMap = new HashMap<>();
        numerals[1] = "I";
        numerals[5] = "V";
        numerals[10] = "X";
        numerals[50] = "L";
        numerals[100] = "C";
        numerals[500] = "D";
        numerals[1000] = "M";
        hashMap.put("I", 0);
        hashMap.put("V", 0);
        hashMap.put("X", 0);
        hashMap.put("L", 0);
        hashMap.put("C", 0);
        hashMap.put("D", 0);
        hashMap.put("M", 0);
        for(int i = 1; i <= pages; i++){
            numerals[i] = generateNumeral(i);
        }
        if(hashMap.get("I") != 0){
            out.println("I " + hashMap.get("I"));
        }
        if(hashMap.get("V") != 0){
            out.println("V " + hashMap.get("V"));
        }
        if(hashMap.get("X") != 0){
            out.println("X " + hashMap.get("X"));
        }
        if(hashMap.get("L") != 0){
            out.println("L " + hashMap.get("L"));
        }
        if(hashMap.get("C") != 0){
            out.println("C " + hashMap.get("C"));
        }
        if(hashMap.get("D") != 0){
            out.println("D " + hashMap.get("D"));
        }
        if(hashMap.get("M") != 0){
            out.println("M " + hashMap.get("M"));
        }
        System.out.println("I " + hashMap.get("I"));
        System.out.println("V " + hashMap.get("V"));
        System.out.println("X " + hashMap.get("X"));
        System.out.println("L " + hashMap.get("L"));
        System.out.println("C " + hashMap.get("C"));
        System.out.println("D " + hashMap.get("D"));
        System.out.println("M " + hashMap.get("M"));

        in.close();
        out.close();
    }

    public static String generateNumeral(int num) {
        String numStr = Integer.toString(num);
        String newNum = "";
        for (int i = 0; i < numStr.length(); i++) {
            if (numStr.charAt(i) == '1') {
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 1);
            } else if (numStr.charAt(i) == '2') {
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 2);
            } else if (numStr.charAt(i) == '3') {
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 3);
            } else if(numStr.charAt(i) == '4'){
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 1);
                increment(numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))], 1);
            }
            else if (numStr.charAt(i) == '5') {
                newNum += numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))], 1);
            }else if(numStr.charAt(i) == '6'){
                newNum += numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (5 *Math.pow(10, numStr.length() - i - 1))], 1);
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 1);
            }else if (numStr.charAt(i) == '7') {
                newNum += numerals[(int) (5*Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))], 1);
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 2);
            } else if (numStr.charAt(i) == '8') {
                newNum += numerals[(int) (5*Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (5 * Math.pow(10, numStr.length() - i - 1))], 1);
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 3);
            } else if(numStr.charAt(i) == '9'){
                newNum += numerals[(int) (Math.pow(10, numStr.length() - i - 1))];
                newNum += numerals[(int) (10 * Math.pow(10, numStr.length() - i - 1))];
                increment(numerals[(int) (Math.pow(10, numStr.length() - i - 1))], 1);
                increment(numerals[(int) (10 * Math.pow(10, numStr.length() - i - 1))], 1);
            }
        }
        return newNum;
    }

    public static void increment(String str, int num){
        hashMap.put(str, hashMap.get(str) + num);
    }
}