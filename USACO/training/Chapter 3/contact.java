/*
ID: ssk49881
LANG: JAVA
TASK: contact
*/

import java.io.*;
import java.util.*;
import java.util.Map.Entry;

public class contact {
    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        BufferedReader br = new BufferedReader(new FileReader("contact.in"));
        StringTokenizer l = new StringTokenizer(br.readLine());
        int a = Integer.parseInt(l.nextToken()); //minimum pattern length
        int b = Integer.parseInt(l.nextToken()); //maximum pattern length
        int n = Integer.parseInt(l.nextToken()); //number of patterns to find
        StringBuilder message = new StringBuilder();
        String line;
        while ((line = br.readLine())!=null) {
            message.append(line);
        }
        PrintWriter out = new PrintWriter(new File("contact.out"));
        HashMap<String, Integer> codes = new HashMap<>();
        System.out.println("read message: " + (System.currentTimeMillis() - start_time));
        System.out.println("message length: " + message.length());
        String code;
        for (int i = a; i <= b; i++) {
            for (int j = 0; j + i <= message.length(); j++) {
                code = message.substring(j, j + i);
                if (codes.get(code) == null) {
                    codes.put(code, 1);
                } else {
                    codes.put(code, codes.get(code) + 1);
                }
            }
        }
        System.out.println("parsed message: " + (System.currentTimeMillis() - start_time));
        System.out.println("codes length: " + codes.size());
        ArrayList<Integer> freqs = new ArrayList<>();
        ArrayList<ArrayList<String>> strs = new ArrayList<>();
        for (Entry<String, Integer> entry : codes.entrySet()) {
            if (freqs.contains(entry.getValue())) {
                strs.get(freqs.indexOf(entry.getValue())).add(entry.getKey());
            } else {
                int index = -1 * (Collections.binarySearch(freqs, entry.getValue()) + 1);
                freqs.add(index, entry.getValue());
                strs.add(index, new ArrayList<>());
                strs.get(index).add(entry.getKey());
            }
        }
        System.out.println("merged frequencies: " + (System.currentTimeMillis() - start_time));
        System.out.println("frequencies length: " + freqs.size());
        for (int i = freqs.size() - 1; freqs.size() - i <= n && i >= 0; i--) {
            out.println(freqs.get(i));
            Collections.sort(strs.get(i),
                    (s1, s2) -> s1.length() - s2.length() != 0 ? s1.length() - s2.length() : s1.compareTo(s2));
            for (int j = 0; j < strs.get(i).size() - 1; j++) {
                if (j % 6 == 5) {
                    out.println(strs.get(i).get(j));
                } else {
                    out.print(strs.get(i).get(j) + " ");
                }
            }
            out.println(strs.get(i).get(strs.get(i).size() - 1));
        }
        System.out.println("produced output: " + (System.currentTimeMillis() - start_time));
        br.close();
        out.close();
    }
}