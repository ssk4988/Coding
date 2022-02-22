import java.io.*;
import java.util.*;

public class hay {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(in.readLine());
        int[] j = new int[n];
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] freqj = new int[n];
        int[] x = new int[n]; //answer array
        int[] end = new int[n]; //k = end[i] where k is last index where j[k] < i
        int[] same = new int[n]; //same[i] = last val where x[same[i]]=x[i]
        int[] lastref = new int[n];
        int[] firstref = new int[n];
        Arrays.fill(lastref, -1);
        Arrays.fill(firstref, -1);
        int[] diff = new int[n]; //how much bigger x[i] is than x[i-1]
        for (int i = 0; i < n; i++) {
            j[i] = Integer.parseInt(tokenizer.nextToken()) - 1;
            lastref[j[i]] = i;
            if(firstref[j[i]] == -1){
                firstref[j[i]] = i;
            }
            freqj[j[i]]++;
            same[i] = i;
        }
        //initialize same
        for(int i = n-1; i > 0 ; i--){
            if(j[i] == j[i-1] && freqj[i-1] == 0){
                same[i-1] = same[i];
            }
        }
        //calc diffs
        for(int i = 1; i < n; i++){
            if(same[i] == same[i-1]){
                diff[i] = 0;
            }
            else{
                
            }
        }
        
        for (int i = 0; i < n; i++) {
            //System.out.println(arr[i]);
        }
        // System.out.println(Arrays.toString(arr));
        in.close();
    }
}