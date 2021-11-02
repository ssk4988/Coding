import java.io.*;
import java.util.*;

public class paint {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numSeg = Integer.parseInt(tokenizer.nextToken());
        int numQ = Integer.parseInt(tokenizer.nextToken());
        int[] fence = new int[numSeg];
        String s = in.readLine();
        for(int i = 0; i < numSeg; i++){
            fence[i] = s.charAt(i) - 'A';
        }
        int[][] prevOcc = new int[26][numSeg];
        for(int[] i : prevOcc){
            Arrays.fill(i, -1);
        }
        boolean[][] prevLight = new boolean[26][numSeg];
        for(int col = 0; col < 26; col++){
            int prev = -1;
            boolean lighter = false;
            for(int i = 0; i < numSeg; i++){
                if(fence[i] < col){
                    lighter = true;
                }
                if(fence[i] == col){
                    prevOcc[col][i] = prev;
                    prev = i;
                    prevLight[col][i] = lighter;
                    lighter = false;
                }
            }
        }
        int[][] nextOcc = new int[26][numSeg];
        for(int[] i : nextOcc){
            Arrays.fill(i, numSeg);
        }
        boolean[][] nextLight = new boolean[26][numSeg];
        for(int col = 0; col < 26; col++){
            int next = numSeg;
            boolean lighter = false;
            for(int i = numSeg - 1; i >= 0; i--){
                if(fence[i] < col){
                    lighter = true;
                }
                if(fence[i] == col){
                    nextOcc[col][i] = next;
                    next = i;
                    nextLight[col][i] = lighter;
                    lighter = false;
                }
            }
        }
        int[] frontNum = new int[numSeg];
        frontNum[0] = 1;
        for(int i = 1; i < numSeg; i++){
            int col = fence[i];
            frontNum[i] = frontNum[i - 1];
            if(prevOcc[col][i] < 0 || prevLight[col][i]){
                frontNum[i]++;
            }
        }
        int[] backNum = new int[numSeg];
        backNum[numSeg - 1] = 1;
        for(int i = numSeg - 2; i >= 0; i--){
            int col = fence[i];
            backNum[i] = backNum[i + 1];
            if(nextOcc[col][i] >= numSeg || nextLight[col][i]){
                backNum[i]++;
            }
        }
        for(int i = 0; i < numQ; i++){
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int num = 0;
            if(first > 0){
                num += frontNum[first - 1];
            }
            if(second < numSeg - 1){
                num += backNum[second + 1];
            }
            System.out.println(num);
        }

        in.close();
        // out.close();
    }
}