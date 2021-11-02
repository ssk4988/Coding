import java.io.*;
import java.util.*;

public class zoom {
    public static ArrayList<String> answers = new ArrayList<>();

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numTest = Integer.parseInt(in.readLine());
        int[] sizes = new int[numTest];
        int[][] arrs = new int[numTest][7];
        for (int i = 0; i < numTest; i++) {
            sizes[i] = Integer.parseInt(in.readLine());
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < sizes[i]; j++) {
                arrs[i][j] = Integer.parseInt(tokenizer.nextToken());
            }
            Arrays.sort(arrs[i]);
        }
        for (int i = 0; i < numTest; i++) {
            answers = new ArrayList<>();
            dfs(arrs[i]);
            answers.remove("");
            System.out.println(answers.size());
            //System.out.println(answers);
        }

        in.close();
    }

    public static void dfs(int[] arr) {
        String s = solve(arr);
        if (!answers.contains(s)) {
            answers.add(s);
        }
        if (arr[2] != 0 && arr[3] != 0) {
            int tmp = arr[2];
            arr[2] = arr[3];
            arr[3] = tmp;
            s = solve(arr);
            if (!answers.contains(s)) {
                answers.add(s);
            }
            tmp = arr[2];
            arr[2] = arr[3];
            arr[3] = tmp;
        }

        for (int i = 0; i < arr.length - 1; i++) {
            if (arr[i] == 0 && arr[i + 1] != 0) {
                int tmp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp;
                dfs(arr);
                tmp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = tmp;
            }
        }
    }

    public static String solve(int[] arr) {
        Set<Integer> a = new HashSet<>();
        Set<Integer> b = new HashSet<>();
        Set<Integer> c = new HashSet<>();
        if (arr[0] != 0) {
            a.add(arr[0]);
        }
        if (arr[6] != 0 && arr[5] != 0) {
            a.add(arr[6] - arr[5]);
        }
        if (arr[4] != 0 && arr[2] != 0) {
            a.add(arr[4] - arr[2]);
        }
        if (arr[3] != 0 && arr[1] != 0) {
            a.add(arr[3] - arr[1]);
        }
        if (arr[1] != 0) {
            b.add(arr[1]);
        }
        if (arr[6] != 0 && arr[4] != 0) {
            b.add(arr[6] - arr[4]);
        }
        if (arr[5] != 0 && arr[2] != 0) {
            b.add(arr[5] - arr[2]);
        }
        if (arr[3] != 0 && arr[0] != 0) {
            b.add(arr[3] - arr[0]);
        }
        if (arr[2] != 0) {
            c.add(arr[2]);
        }
        if (arr[6] != 0 && arr[3] != 0) {
            c.add(arr[6] - arr[3]);
        }
        if (arr[5] != 0 && arr[1] != 0) {
            c.add(arr[5] - arr[1]);
        }
        if (arr[4] != 0 && arr[0] != 0) {
            c.add(arr[4] - arr[0]);
        }
        //System.out.println(a);
        //System.out.println(b);
        //System.out.println(c);
        if (a.size() != 1 || b.size() != 1 || c.size() != 1) {
            return "";
        }
        int a1 = (int) a.toArray()[0];
        int b1 = (int) b.toArray()[0];
        int c1 = (int) c.toArray()[0];
        if (a1 <= 0 || b1 <= 0 || c1 <= 0 || a1 > b1 || a1 > c1 || b1 > c1) {
            return "";
        }
        if(arr[0] != 0 && arr[0] != a1){
            return "";
        }
        if(arr[1] != 0 && arr[1] != b1){
            return "";
        }
        if(arr[2] != 0 && arr[2] != c1){
            return "";
        }
        if(arr[3] != 0 && arr[3] != a1 + b1){
            return "";
        }
        if(arr[4] != 0 && arr[4] != a1 + c1){
            return "";
        }
        if(arr[5] != 0 && arr[5] != b1 + c1){
            return "";
        }
        if(arr[6] != 0 && arr[6] != a1 + b1 + c1){
            return "";
        }
        return a1 + "," + b1 + "," + c1;
    }
}