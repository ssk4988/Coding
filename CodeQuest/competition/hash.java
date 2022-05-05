import java.io.*;
import java.util.*;

public class hash {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder output = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            String val = in.readLine();
            String conv = "";
            for (int i = 0; i < val.length(); i++) {
                int c = val.charAt(i);
                String l = Integer.toString(c, 2);
                while (l.length() < 7) {
                    l = "0" + l;
                }
                conv += l;

            }
            while (conv.length() % 128 != 0)
                conv += '1';
            int a = 792250721;
            int b = 683117105;
            int c = 1215387974;
            int d = 1767829900;
            for (int i = 0; 32 * i < conv.length(); i++) {
                int m = 0;
                for (int j = 0; j < 32; j++) {
                    if (conv.charAt(32 * i + j) == '1') {
                        m++;
                    }
                    if (j + 1 < 32)
                        m <<= 1;
                }
                int s = (b ^ d) & (c | (~b));
                s = a + s;
                s = m + s;
                int l = i % 32;
                s = Integer.rotateLeft(s, l);
                a = d;
                d = c;
                c = b;
                b = s;
            }
            int[] arr = new int[] { a, b, c, d };
            String cl = "";
            for (int i = 0; i < arr.length; i++) {
                String s =""; //Integer.toString(arr[i], 2);
                for(int k = 31; k >= 0; k--){
                    if((arr[i] & 1 << k) > 0){
                        s += "1";
                    }
                    else{
                        s += "0";
                    }
                }
                while(s.length() < 32){
                    s = "0" + s;
                }
                int index = 0;
                while(index + 3 < s.length()){
                    cl += Integer.toHexString(Integer.parseInt(s.substring(index, index + 4),2));
                    index += 4;
                }/*
                for (int j = 28; j >= 0; j -= 4) {
                    int v = 0;
                    for (int k = 3; k >= 0; k--) {
                        if ((arr[i] & 1 << (j + k)) > 0) {
                            v++;
                        }
                        if (k > 0)
                            v <<= 1;
                    }
                    cl += Integer.toHexString(v);
                }*/
            }
            //System.out.println(cl);
            String orr = in.readLine().toLowerCase();
            System.out.println(orr.equals(cl) ? "TRUE" : "FALSE");
        }
        in.close();
        out.close();
    }
}