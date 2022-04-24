import java.io.*;
import java.util.*;

public class reflection {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            String[] input = new String[n];
            int maxLen = 0;
            line[] lines= new line[n];
            for(int i = 0; i < n; i++){
                input[i] = in.readLine();
                maxLen = Math.max(input[i].length(), maxLen);
            }
            for(int i = 0; i < n; i++){
                int left = 0;
                while(left < input[i].length() && input[i].charAt(left) == ' '){
                    left++;
                }
                int right = maxLen - input[i].length();
                lines[i] = new line(left, right, input[i].substring(left));
            }
            String op = in.readLine();
            if(op.equals("Y")){
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < lines[i].rightspace; j++){
                        b.append(' ');
                    }
                    for(int j = lines[i].val.length() - 1; j >= 0; j--){
                        b.append(lines[i].val.charAt(j));
                    }
                    b.append("\n");
                }
            }
            else if(op.equals("X")){
                for(int i = n-1; i >= 0; i--){
                    for(int j = 0; j < lines[i].leftspace; j++){
                        b.append(' ');
                    }
                    for(int j = 0; j < lines[i].val.length(); j++){
                        b.append(lines[i].val.charAt(j));
                    }
                    b.append("\n");
                }
            }
            else{
                for(int i = n-1; i >= 0; i--){
                    for(int j = 0; j < lines[i].rightspace; j++){
                        b.append(' ');
                    }
                    for(int j = lines[i].val.length() - 1; j >= 0; j--){
                        b.append(lines[i].val.charAt(j));
                    }
                    b.append("\n");
                }
            }
        }
        System.out.print(b);

        in.close();
        out.close();
    }
    public static class line{
        int leftspace = 0;
        int rightspace = 0;
        String val = "";
        public line(int leftspace, int rightspace, String val){
            this.leftspace = leftspace;
            this.rightspace = rightspace;
            this.val = val;
        }
    }
}