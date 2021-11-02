import java.io.*;
import java.util.*;

public class triangles {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("triangles.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("triangles.out")));
        int numPosts = Integer.parseInt(in.readLine());
        int[][] posts = new int[numPosts][2];
        HashMap<Integer, ArrayList<Integer>> horizontal = new HashMap<>();
        HashMap<Integer, ArrayList<Integer>> vertical = new HashMap<>();
        for(int i = 0; i < numPosts; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(tokenizer.nextToken());
            int y = Integer.parseInt(tokenizer.nextToken());
            posts[i][0] = x;
            posts[i][1] = y;
            if(!horizontal.containsKey(y)){
                horizontal.put(y, new ArrayList<>());
            }
            if(!vertical.containsKey(x)){
                vertical.put(x, new ArrayList<>());
            }
            horizontal.get(y).add(i);
            vertical.get(x).add(i);
        }
        int maxArea = 0;
        for(int i = 0; i < numPosts; i++){
            int maxLength = 0;
            int maxHeight = 0;
            for(int id : vertical.get(posts[i][0])){
                if(Math.abs(posts[id][1] - posts[i][1]) > maxHeight){
                    maxHeight = Math.abs(posts[id][1] - posts[i][1]);
                }
            }
            for(int id : horizontal.get(posts[i][1])){
                if(Math.abs(posts[id][0] - posts[i][0]) > maxLength){
                    maxLength = Math.abs(posts[id][0] - posts[i][0]);
                }
            }
            if(maxLength * maxHeight > maxArea){
                maxArea = maxLength * maxHeight;
            }
        }
        out.println(maxArea);

        in.close();
        out.close();
    }
}