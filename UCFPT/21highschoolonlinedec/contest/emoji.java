import java.io.*;

public class emoji {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int num = Integer.parseInt(in.readLine());
        for(int i = 0; i < num; i++){
            int[] alpha = new int[26];
            boolean works = true;
            char[] arr = in.readLine().toCharArray();
            for(int j = 0; j < arr.length; j++){
                alpha[arr[j] - 'A']++;
            }
            for(int j = 0; j < alpha.length; j++){
                if(alpha[j] > 1) works = false;
            }
            if(works){
                System.out.println("Emote away!");
            }
            else{
                System.out.println("Nope");
            }
        }

        in.close();
        out.close();
    }
}