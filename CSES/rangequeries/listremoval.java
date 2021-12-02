import java.io.*;
import java.util.*;

public class listremoval {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int size = Integer.parseInt(in.readLine());
        int size2 = size + (size & -size);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int[] arr = new int[size];
        int[] tree = new int[size2 * 2];
        for(int i = 0; i < size; i++){
            arr[i] = Integer.parseInt(tokenizer.nextToken());
        }
        tokenizer = new StringTokenizer(in.readLine());
        StringBuilder b = new StringBuilder();
        for(int i = 0; i < size; i++){
            int ind = Integer.parseInt(tokenizer.nextToken())-1;
            int before = val(tree, 0, ind);

            System.out.println(ind + " " + before);
            b.append(arr[ind + before]);
            if(i < size - 1) b.append(" ");
            update(tree, ind + before);
        }
        System.out.println(b);


        in.close();
        out.close();
    }
    public static int val(int[] tree, int index1, int index2){
        int size = tree.length / 2;
        int val = 0;
        index1 += size;
        index2 += size;
        while(index1 <= index2){
            if(index1 % 2 == 1) val += tree[index1++];
            if(index2 % 2 == 0) val += tree[index2--];
            index1 /= 2;
            index2 /= 2;
        }
        return val;
    }
    public static void update(int[] tree, int index){
        int size = tree.length / 2;
        index += size;
        tree[index]++;
        for(index/=2; index>=1;index/=2){
            tree[index] = tree[2*index] + tree[2*index+1];
        }
    }
}