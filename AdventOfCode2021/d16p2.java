import java.io.*;
import java.math.BigInteger;
import java.util.*;

public class d16p2 {
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
        // System.out.println(s);
        String str2 = new BigInteger(s, 2).toString(16).toUpperCase();
        IntLong b = new IntLong(0, 0);
        b = parse(b, s);
        System.out.println("version sum: " + versionSum);
        System.out.println("answer: " + b.l);

        in.close();
    }

    public static IntLong parse(IntLong input, String s) {
        IntLong b = new IntLong(input.i, 0);
        int version = Integer.parseInt(s.substring(b.i, b.i + 3), 2);
        versionSum += version;
        b.i += 3;
        int type = Integer.parseInt(s.substring(b.i, b.i + 3), 2);
        b.i += 3;
        // System.out.println("version: " + version + " type: " + type);
        if (type != 4) {
            b = parseOperator(b, version, type, s);
        } else {
            b = parseLiteral(b, version, type, s);
        }

        return b;
    }

    public static IntLong parseOperator(IntLong input, int version, int type, String s) {
        IntLong b = new IntLong(input.i, 0);
        // System.out.println("start operator");
        ArrayList<Long> vals = new ArrayList<>();
        if (s.charAt(b.i++) == '0') {
            // System.out.println(s.substring(b.i, b.i + 15));
            int val = Integer.parseInt(s.substring(b.i, b.i + 15), 2);
            // System.out.println(val + " bits");
            b.i += 15;
            int init = b.i;
            while (b.i - init < val) {
                b = parse(b, s);
                vals.add(b.l);
            }
        } else {
            int val = Integer.parseInt(s.substring(b.i, b.i + 11), 2);
            // System.out.println(val + " packets");
            b.i += 11;
            int i = 0;
            while (i++ < val) {
                b = parse(b, s);
                vals.add(b.l);
            }
        }

        if (type == 0) {
            b.l = 0;
            for (long val : vals) {
                b.l += val;
                if (b.l < 0) {
                    System.out.println("bruh moment");
                }
            }
        } else if (type == 1) {
            b.l = 1;
            for (long val : vals) {
                b.l *= val;
                if (b.l < 0) {
                    System.out.println("bruh moment");
                }
            }
        } else if (type == 3) {
            b.l = Long.MIN_VALUE;
            for (long val : vals) {
                b.l = Math.max(b.l, val);
            }
        } else if (type == 2) {
            b.l = Long.MAX_VALUE;
            for (long val : vals) {
                b.l = Math.min(b.l, val);
            }
        } else if (type == 5) {
            b.l = vals.get(0) > vals.get(1) ? 1 : 0;
        } else if (type == 6) {
            b.l = vals.get(0) < vals.get(1) ? 1 : 0;
        } else if (type == 7) {
            b.l = vals.get(0) == vals.get(1) ? 1 : 0;
        }
        // System.out.println("end operator");
        return b;
    }

    public static IntLong parseLiteral(IntLong input, int version, int type, String s) {
        IntLong b = new IntLong(input.i, 0);
        StringBuilder bString = new StringBuilder();
        int init = b.i;
        while (s.charAt(b.i++) == '1') {
            bString.append(s.substring(b.i, b.i + 4));
            b.i += 4;
        }
        bString.append(s.substring(b.i, b.i + 4));
        b.i += 4;
        BigInteger val2 = new BigInteger(bString.toString(), 2);
        long val = val2.longValue();
        BigInteger val3 = new BigInteger(Long.toString(val));
        if (!val2.toString().equals(Long.toString(val))) {
            System.out.println("bruh moment");
        }
        System.out.println("literal " + val);
        b.l = val;
        return b;
    }

    public static class IntLong {
        int i;
        long l;

        public IntLong(int i, long l) {
            this.i = i;
            this.l = l;
        }
    }
}
