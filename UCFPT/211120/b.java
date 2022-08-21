/*
ID: ssk49881
LANG: JAVA
TASK: name
*/

import java.io.*;
import java.util.*;

public class b {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String val = in.readLine();
        
        while(!val.equals("0")){
            int prod = Integer.parseInt(val);
            ArrayList<Integer> list = new ArrayList<>();
            list.add(prod);
            while(Integer.toString(prod).length() > 1){
                String s = Integer.toString(prod);
                prod = 1;
                for(int i = 0; i < s.length(); i++){
                    prod *= Integer.parseInt(s.substring(i, i+1));
                }
                list.add(prod);
            }
            for(int i = 0; i < list.size(); i++){
                System.out.print(list.get(i));
                if(i < list.size() - 1){
                    System.out.print(" ");
                }
                
            }
            System.out.println();
            val = in.readLine();
        }

        in.close();
        out.close();
    }
}