import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int max = 100;
        Map<String, Integer> freq = new HashMap<>();
        /*for (int i = 0; i <= max; i++) {
            // System.out.println(i + " " + square(i));
            String s = square(i);
            if (!freq.containsKey(s)) {
                freq.put(s, 0);
            }
            freq.put(s, freq.get(s) + 1);
        }
        for (String s : freq.keySet()) {
            if (freq.get(s) != 2) {
                // System.out.println("bruh" + s);
            }
        }*/
        /*
         * for(int i = 0; i < 10; i++){
         * for(int j = 0; j < 10; j++){
         * System.out.println((j * 10 + i) + " " + square(j*10+i));
         * }
         * }
         */
        String val = in.readLine();
        if (val.length() % 2 == 0) {
            // not work
        }
        ArrayList<String> possibilities = new ArrayList<>();
        possibilities.add("");
        long ten = 1;
        int maxLen = (val.length() + 1)/2;
        for (int i = 0; i < val.length(); i++) {
            String suf = val.substring(val.length() - 1 - i);
            ArrayList<String> a2 = new ArrayList<>();
            for (String j : possibilities) {
                for (int k = 0; k < 10; k++) {
                    String nstr = j.length() >= maxLen ? j : k + j;
                    String o = square(nstr);
                    //System.out.println((ten * k + j)+" "+o);
                    if(o.length() < suf.length()) break;
                    if (o.substring(o.length() - 1 - i).equals(suf)) {
                        a2.add(nstr);
                    }
                    if(nstr.equals(j)) break;
                }
            }
            possibilities = a2;
            //System.out.println(suf + " " + a2);
            ten *= 10;
        }
        long answer = -1;
        for(int i= 0; i < possibilities.size(); i++){
            long j = Long.parseLong(possibilities.get(i));
            if(!square(possibilities.get(i)).equals(val)) break;
            if(answer == -1 || j < answer){
                answer = j;
            }
        }
        System.out.println(answer);

        in.close();
        out.close();
    }

    public static String square(String lstr) {
        long l = Long.parseLong(lstr);
        int[] d = new int[lstr.length()];
        for (int i = 0; i < d.length; i++) {
            d[i] = lstr.charAt(i) - '0';
        }
        long[] digits = new long[lstr.length() * 2 - 1];
        for (int i = 0; i < lstr.length(); i++) {
            for (int j = 0; j < lstr.length(); j++) {
                digits[i + j] += (d[i] * d[j]);
            }
        }
        StringBuilder b = new StringBuilder();
        boolean notZero = false;
        for (int i = 0; i < digits.length; i++) {
            digits[i] %= 10;
            /*if (!notZero && digits[i] != 0) {
                notZero = true;
            }
            if (!notZero && digits[i] == 0) {

            } else {
                b.append(digits[i]);
            }*/
            b.append(digits[i]);
        }
        return b.toString();
    }
}