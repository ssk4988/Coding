import java.io.*;
import java.util.*;

public class rna {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        Map<Character, Integer> cmap = new HashMap<>();
        cmap.put('A', 0);
        cmap.put('C', 1);
        cmap.put('G', 2);
        cmap.put('U', 3);
        for (int casenum = 0; casenum < numcases; casenum++) {
            char[] carray = in.readLine().toCharArray();
            int[] recode = new int[carray.length];
            for (int i = 0; i < carray.length; i++) {
                recode[i] = cmap.get(carray[i]);
            }
            int[] codons = new int[64];
            for (int i = 0; i < 64; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                char[] c2 = tokenizer.nextToken().toCharArray();
                int amino = Integer.parseInt(tokenizer.nextToken()) - 1;
                int start = 1;
                int index = 0;
                for (int j = 0; j < 3; j++) {
                    index += cmap.get(c2[j]) * start;
                    start *= 4;
                }
                codons[index] = amino;
            }
            int readLength = Integer.parseInt(in.readLine())/3;
            int[] ramino = new int[recode.length];
            for (int i = 0; i + 2 < recode.length; i++) {
                int start = 1;
                int index = 0;
                for (int j = 0; j < 3; j++) {
                    index += recode[i + j] * start;
                    start *= 4;
                }
                ramino[i] = codons[index];
            }
            Set<String> strs = new HashSet<>();
            for (int k = 0; k < 3; k++) {
                StringBuilder b = new StringBuilder();
                for (int j = 0; k + j + 2 < ramino.length; j += 3) {
                    b.append((char) (ramino[j + k]));
                }
                for (int i = 0; i + readLength <= b.length(); i++) {
                    strs.add(b.substring(i, i + readLength));
                }
            }

            System.out.println(strs.size());
        }
        in.close();
        out.close();
    }
}