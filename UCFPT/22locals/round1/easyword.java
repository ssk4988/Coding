import java.io.*;
import java.util.*;

public class easyword {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s= in.readLine();
        HashSet<Character> vowel = new HashSet<>();
        vowel.add('a');
        vowel.add('e');
        vowel.add('i');
        vowel.add('o');
        vowel.add('u');
        boolean works = true;
        boolean v = vowel.contains(s.charAt(0));
        for(int i = 1; i < s.length(); i++){
            if(vowel.contains(s.charAt(i))==v){
                works = false;
            }
            v = vowel.contains(s.charAt(i));
        }
        System.out.println(works ? 1 : 0);
        in.close();
    }
}