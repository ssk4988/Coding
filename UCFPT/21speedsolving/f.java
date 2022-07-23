import java.io.*;
import java.util.*;

public class f {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        char[] cs = {'.', '-'};
        ArrayList<String> letters = new ArrayList<>();
        letters.add(cs[0]+"");
        letters.add(cs[1]+"");
        for(int i = 1; i <= 4; i++){
            int len = letters.size();
            for(int j = 0; j < len; j++){
                if(letters.get(j).length() == i){
                    for(int k = 0; k < cs.length; k++){
                        letters.add(letters.get(j) + cs[k]);
                    }
                }
            }
        }
        //System.out.println(letters);
        ArrayList<Integer> cost = new ArrayList<>();
        for(int i = 0; i < letters.size(); i++){
            String s = letters.get(i);
            int c = s.length() - 1;
            for(int j = 0; j < s.length(); j++){
                if(s.charAt(j) == '.'){
                    c+=1;
                }
                else{
                    c+=3;
                }
            }
            cost.add(c);
        }
        Collections.sort(cost);
        //System.out.println(cost);
        int[] count = new int[26];
        String input = in.readLine();
        int slen = 0;
        for(int i= 0; i < input.length(); i++){
            char c = input.charAt(i);
            if(c >= 'a' && c <= 'z'){
                count[c - 'a']++;
                slen++;
            }
            else if(c >= 'A' && c <= 'Z'){
                count[c - 'A']++;
                slen++;
            }
        }
        Arrays.sort(count);
        long answer = 3 * (slen-1);
        for(int i = 0; i < count.length; i++){
            answer += (long)count[count.length - 1 - i] * cost.get(i);
        }
        System.out.println(answer);

        in.close();
        out.close();
    }
}