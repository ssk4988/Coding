import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            int n = Integer.parseInt(in.readLine());
            int[] arr = new int[n];
            StringTokenizer tokenizer =new StringTokenizer(in.readLine());
            int[] left = new int[n+1];
            for(int i = 0; i < n; i++){
                arr[i] = Integer.parseInt(tokenizer.nextToken()); //reverse array
                left[arr[i]]++;
            }
            //System.out.println(Arrays.toString(arr));
            ArrayList<Integer> b = new ArrayList<>();
            int curr = 0;
            TreeSet<Integer> notUsed = new TreeSet<>();
            for(int i = 0; i <= n; i++){
                notUsed.add(i);
            }
            //Set<Integer> used = new HashSet<>();
            while(curr < n){
                int cCurr = curr;
                notUsed.remove(arr[curr]);
                left[arr[curr]]--;
                curr++;
                //used.add(arr[curr++]);
                int mex = notUsed.first();
                while(true){
                    if(left[mex] <= 0){
                        break;
                    }
                    while(arr[curr]!=mex){
                        notUsed.remove(arr[curr]);
                        left[arr[curr]]--;
                        curr++;
                    }
                    //arr[curr] == mex or curr>n crash
                    notUsed.remove(arr[curr]);
                    left[arr[curr]]--;
                    curr++;
                    mex = notUsed.first();
                }/*
                int maxIndex = curr;
                while(curr < n){
                    notUsed.remove(arr[curr++]);
                    //used.add(arr[curr++]);
                    int cMax = notUsed.first();
                    if(cMax > mex){
                        mex = cMax;
                        maxIndex = curr;
                    }
                }*/
                
                b.add(mex);/*
                for(curr = n-1; curr>=maxIndex; curr--){
                    notUsed.add(arr[curr]);
                }
                curr=maxIndex;*/
                for(int i = curr - 1; i >= cCurr; i--){
                    notUsed.add(arr[i]);
                }
            }
            System.out.println(b.size());
            for(int i = 0; i+1 < b.size(); i++){
                System.out.print(b.get(i) + " ");
            }
            System.out.println(b.get(b.size() - 1));
        }
        in.close();
        out.close();
    }
}