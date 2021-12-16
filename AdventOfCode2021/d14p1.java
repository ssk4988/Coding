import java.io.*;
import java.util.*;

public class d14p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d14p1.in"));
        int numDays = 40;
        String line;
        String s = in.readLine();
        in.readLine();
        ArrayList<String> input = new ArrayList<>();
        Map<String, Integer> map = new HashMap<>();
        Map<Integer, String> map2 = new HashMap<>();
        Map<String, String> map3 = new HashMap<>();
        while ((line = in.readLine()) != null) {
            String seq = line.substring(0, 2);
            input.add(line);
            map.put(seq, map.size());
            map2.put(map.get(seq), seq);
            map3.put(seq, line.substring(6));
        }
        long[][] start = new long[map.size()][map.size()];
        long[] vec = new long[map.size()];
        for (int i = 0; i + 1 < s.length(); i++) {
            vec[map.get(s.substring(i, i + 2))]++;
        }
        System.out.println(Arrays.toString(vec));
        for (int i = 0; i < start.length; i++) {
            String seq = map2.get(i);
            start[map.get(seq)][map.get(seq.substring(0, 1) + map3.get(seq))]++;
            start[map.get(seq)][map.get(map3.get(seq) + seq.substring(1, 2))]++;
            // System.out.println(Arrays.toString(start[map.get(seq)]));
        }
        for (int i = 0; (1 << i) <= numDays; i++) {
            //System.out.println(i);
            for (int j = 0; j < start.length; j++) {
                //System.out.println(Arrays.toString(start[j]));
            }
            if ((numDays & (1 << i)) == (1 << i)) {
                long[] vec2 = new long[map.size()];
                for (int j = 0; j < vec2.length; j++) {
                    for (int k = 0; k < start[j].length; k++) {
                        vec2[k] += vec[j] * start[j][k];
                   }
                }
                vec = vec2;
                // System.out.println(Arrays.toString(vec));
            }
            long[][] start2 = new long[map.size()][map.size()];
            for (int j = 0; j < start2.length; j++) {
                for (int k = 0; k < start2[j].length; k++) {
                    for (int l = 0; l < start.length; l++) {
                        start2[j][k] += start[j][l] * start[l][k];
                    }
                }
            }
            start = start2;
        }
        System.out.println("answer: ");
        System.out.println(Arrays.toString(vec));
        long[] num = new long[26];
        for (int i = 0; i < vec.length; i++) {
            String seq = map2.get(i);
            num[seq.charAt(0) - 'A'] += vec[i];
            num[seq.charAt(1) - 'A'] += vec[i];
        }
        num[s.charAt(0)-'A']++;
        num[s.charAt(s.length()-1)-'A']++;
        long max = 0;
        long min = Long.MAX_VALUE;
        for(int i = 0; i < num.length; i++){
            num[i] /= 2;
            max = Math.max(max, num[i]);
            if(num[i] > 0){
                min = Math.min(min, num[i]);
            }
        }
        System.out.println(Arrays.toString(num));
        System.out.println(max - min);
        in.close();
    }

}
