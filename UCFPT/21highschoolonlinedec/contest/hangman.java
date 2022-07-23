import java.io.*;
import java.util.*;
import java.util.regex.Pattern;

public class hangman {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int num = Integer.parseInt(in.readLine());
        for(int i = 0; i < num; i++){
            String category = in.readLine();
            int numDict = Integer.parseInt(in.readLine());
            String[] dict = new String[numDict];
            for(int j= 0; j<numDict;j++){
                dict[j] = in.readLine();
            }
            int games = Integer.parseInt(in.readLine());
            for(int j = 0; j < games; j++){
                String s= in.readLine();

                String reg = "^" + s.replaceAll("_", ".") + "$";
                //System.out.println("reg: " + reg);
                boolean works = false;
                Pattern pattern = Pattern.compile(reg);
                
                for(int k = 0; k < numDict; k++){
                    boolean b = pattern.matcher(dict[k]).find();
                    if(b){
                        works = true;
                        Map<Integer, Boolean> m = new HashMap<>();
                        for(int l = 0; l < s.length(); l++){
                            int key = dict[k].charAt(l) - '.';
                            if(!m.containsKey(key)){
                                m.put(key, (s.charAt(l) == '_' ? false : true));
                            }
                            if(m.get(key) != (s.charAt(l) == '_' ? false : true)){
                                works = false;
                                break;
                            }
                        }
                    }
                }
                if(works){
                    System.out.println("No cheaters here!");
                }
                else{
                    System.out.println("That's not a word for a(n) " + category + "!");
                }
            }
        }

        in.close();
        out.close();
    }
}