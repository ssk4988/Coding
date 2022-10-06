import java.io.*;
import java.util.*;

public class g {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        String[] phrases = {"number of", "amount of", "most", "fewest", "least", "more", "fewer", "less", "many", "much", "few", "little"};
        //1 c 2 m
        int[] valid = {1, 2, 3, 1, 2, 3, 1, 2, 1, 2, 1, 2};
        Map<String, Integer> map = new HashMap<>();
        for(int i = 0 ;i < phrases.length; i++){
            map.put(phrases[i], valid[i]);
        }
        String[] nouns = new String[n];
        int[] types = new int[n];
        Map<String, Integer> map2 = new HashMap<>();
        for(int i = 0; i < n; i++){
            tokenizer =new StringTokenizer(in.readLine());
            nouns[i] = tokenizer.nextToken();
            types[i] = tokenizer.nextToken().charAt(0) == 'c' ? 0 : 1;
            map2.put(nouns[i], types[i]);
        }
        StringBuilder b =new StringBuilder();
        for(int i = 0; i < m; i++){
            String s = in.readLine();
            String[] s1 = s.split(" ");
            s = s.substring(0, s.length() - s1[s1.length - 1].length() - 1);
            int type = map.get(s);
            int t = map2.get(s1[s1.length-1]);
            if((type & (1 << t)) > 0){
                b.append("Correct!\n");
            }
            else{
                b.append("Not on my watch!\n");
            }
        }
        System.out.print(b);
        in.close();
    }
}