import java.io.*;
import java.util.*;

public class dance {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[] p1 = new int[k];
        int[] p2 = new int[k];
        for (int i = 0; i < k; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int i2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            p1[i] = i1;
            p2[i] = i2;
        }
        int[] arr = new int[numCows];
        boolean[][] actpositions = new boolean[numCows][numCows];
        Set<Integer>[] positions = new Set[numCows];
        for (int i = 0; i < numCows; i++) {
            arr[i] = i;
            positions[i] = new HashSet<>();
            positions[i].add(i);
            actpositions[i][i] = true;
        }
        for (int i = 0; i < k; i++) {
            int tmp = arr[p1[i]];
            positions[arr[p1[i]]].add(p2[i]);
            positions[arr[p2[i]]].add(p1[i]);
            arr[p1[i]] = arr[p2[i]];
            arr[p2[i]] = tmp;
        }
        arr = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            arr[i] = i;
        }
        for (int i = k - 1; i >= 0; i--) {
            int tmp = arr[p1[i]];
            arr[p1[i]] = arr[p2[i]];
            arr[p2[i]] = tmp;
        }
        int[] answer = new int[numCows];
        for (int i = 0; i < numCows; i++) {
            if(answer[i] != 0){
                continue;
            }
            ArrayList<Integer> locations = new ArrayList<>();
            int curr = i;
            while (!locations.contains(curr)) {
                locations.add(curr);
                curr = arr[curr];
                if(curr < i){
                    for(int j = 0; j < actpositions[curr].length; j++){
                        actpositions[i][j] = actpositions[i][j] || actpositions[curr][j];
                    }
                    break;
                }
                for(int j : positions[curr]){
                    actpositions[i][j] = true;
                }
                //actpositions[i].addAll(positions[curr]);
            }
            for(boolean j : actpositions[i]){
                if(j){
                    answer[i]++;
                }
            }
            for(int j : locations){
                answer[j] = answer[i];
            }
        }

        for(int i = 0; i < numCows; i++){
            System.out.println(answer[i]);
        }
        /*for (int i = 0; i < numCows; i++) {
            System.out.println(actpositions[i].size());
        }*/

        in.close();
        // out.close();
    }
}