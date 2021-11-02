import java.io.*;
import java.util.*;

public class cite {
    public static int numPapers;
    public static int numArticles;
    public static int numPer;
    public static int[] citations;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numPapers = Integer.parseInt(tokenizer.nextToken());
        numArticles = Integer.parseInt(tokenizer.nextToken());
        numPer = Integer.parseInt(tokenizer.nextToken());
        citations = new int[numPapers];
        tokenizer = new StringTokenizer(in.readLine());
        for(int i = 0; i < numPapers; i++){
            citations[i] = Integer.parseInt(tokenizer.nextToken());
        }
        Arrays.sort(citations);
        int low = 0;
        int high = numPapers;
        int mid;
        for(--low; low < high;){
            mid = low + (high - low + 1)/2;
            boolean w = possible(mid);
            //System.out.println(mid + " " + w);
            if(w){
                low = mid;
            }
            else{
                high = mid - 1;
            }
        }
        System.out.println(low);

        in.close();
    }
    public static boolean possible(int hindex){
        int current = 0;
        int ind = citations.length - 1;
        while(ind >= 0 && citations[ind] >= hindex){
            current++;
            ind--;
        }
        //System.out.println(current);
        if(current >= hindex){
            return true;
        }
        int[] papers = new int[numPer + 1];
        papers[numPer] = numArticles;
        int minCount = numPer;
        int maxCount = numPer;
        int c = current;

        while(current < hindex && ind >= 0){
            int pC = hindex - citations[numPapers - hindex + current - c];
            if(minCount > 0 && pC > 0){
                minCount--;
            }
            for(int i = minCount; i <= maxCount && pC > 0; i++){
                if(i == 0){
                    continue;
                }
                int sub = Math.min(pC, papers[i]);
                pC -= sub;
                papers[i] -= sub;
                papers[i - 1] += sub;
            }
            if(pC > 0){
                return false;
            }
            if(papers[maxCount] == 0){
                maxCount--;
            }
            current++;
            ind--;
        }

        return true;
    }
}