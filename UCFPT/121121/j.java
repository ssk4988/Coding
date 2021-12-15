import java.io.*;
import java.util.*;

public class j {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        Set<Integer>[] children2 = new Set[10];
        for(int i = 0; i < children2.length; i++){
            children2[i] = new HashSet<>();
            children2[i].add(i);
        }
        add(children2, 8, 9);
        add(children2, 8, 0);
        add(children2, 7, 8);
        add(children2, 6, 9);
        add(children2, 5, 6);
        add(children2, 5, 8);
        add(children2, 4, 7);
        add(children2, 4, 5);
        add(children2, 3, 6);
        add(children2, 2, 5);
        add(children2, 2, 3);
        add(children2, 1, 4);
        add(children2, 1, 2);
        ArrayList<Integer>[] children = new ArrayList[10];
        for(int i = 0; i < children2.length; i++){
            children[i] = new ArrayList<>();
            children[i].addAll(children2[i]);
            Collections.sort(children[i]);
        }
        ArrayList<Integer> possible = new ArrayList<>();
        for(int i = 0; i < 10; i++){
            solve(possible, children, i, 1, i);
        }
        Collections.sort(possible);
        //System.out.println(possible);
        int n = Integer.parseInt(in.readLine());
        for(int i = 0; i < n; i++){
            //System.out.println("answer: ");
            int val = Integer.parseInt(in.readLine());
            int index = Collections.binarySearch(possible, val);
            if(index >= 0){
                System.out.println(val);
            }
            else{
                index = -index - 1;
                int answer = possible.get(index);
                if(index > 0){
                    if(Math.abs(answer - val) > Math.abs(val - possible.get(index - 1))){
                        answer = possible.get(index-1);
                    }
                }
                System.out.println(answer);
            }
        }

        in.close();
    }
    public static void add(Set<Integer>[] children, int i1, int i2){
        children[i1].add(i2);
        children[i1].addAll(children[i2]);
    }
    public static void solve(ArrayList<Integer> possible, ArrayList<Integer>[] children, int curr, int len, int last){
        if(len > 3) return;
        possible.add(curr);
        
        for(int i : children[last]){
            solve(possible, children, curr * 10 + i, len+1, i);
        }
    }
}