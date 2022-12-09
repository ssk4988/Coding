import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class d16p1 {
    public static int versionSum = 0;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d16p1.in"));
        String str = in.readLine();
        String s = new BigInteger(str, 16).toString(2);
        System.out.println(s.length());
        System.out.println(str.length());
        while (s.length() < str.length() * 4) {
            s = "0" + s;
        }
        //System.out.println(s);
        String str2 = new BigInteger(s, 2).toString(16).toUpperCase();
        int index = 0;
        while (index < s.length()) {
            if(s.substring(index).indexOf("1") == -1){
                break;
            }
            System.out.println("left: " + s.substring(index));
            System.out.println("start index: " + index);
            index = parse(index, s);
            System.out.println("end parse");
            
        }
        System.out.println("version sum: " + versionSum);

        in.close();
    }

    public static int parse(int index, String s) {
        int version = Integer.parseInt(s.substring(index, index + 3), 2);
        versionSum += version;
        index += 3;
        int type = Integer.parseInt(s.substring(index, index + 3), 2);
        index += 3;
        System.out.println("version: " + version + " type: " + type);
        if (type != 4) {
            index = parseOperator(index, version, type, s);
        } else {
            index = parseLiteral(index, version, type, s);
        }
        return index;
    }

    public static int parseOperator(int index, int version, int type, String s) {
        System.out.println("start operator");
        if (s.charAt(index++) == '0') {
            System.out.println(s.substring(index, index + 15));
            int val = Integer.parseInt(s.substring(index, index + 15),2);
            System.out.println(val + " bits");
            index += 15;
            int init = index;
            while (index - init < val) {
                index = parse(index, s);
            }
        } else {
            int val = Integer.parseInt(s.substring(index, index + 11),2);
            System.out.println(val + " packets");
            index += 11;
            int i = 0;
            while (i++ < val) {
                index = parse(index, s);
            }
        }
        System.out.println("end operator");
        return index;
    }

    public static int parseLiteral(int index, int version, int type, String s) {
        StringBuilder bString = new StringBuilder();
        int init = index;
        while (s.charAt(index++) == '1') {
            bString.append(s.substring(index, index + 4));
            index += 4;
        }
        bString.append(s.substring(index, index + 4));
        index += 4;
        BigInteger val2 = new BigInteger(bString.toString(), 2);
        int val = val2.intValue();
        System.out.println("literal " + val);
        return index;
    }
}
