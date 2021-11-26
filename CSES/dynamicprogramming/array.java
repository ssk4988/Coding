import java.io.*;
import java.util.*;

public class array {
    public static int numnum;
    public static int maxNum;
    public static int[][] ways;
    public static boolean[][] calculated;
    public static int[] array;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numnum = Integer.parseInt(tokenizer.nextToken());
        maxNum = Integer.parseInt(tokenizer.nextToken());
        ways = new int[numnum][maxNum + 1];
        calculated = new boolean[numnum][maxNum + 1];
        array = new int[numnum];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numnum; i++) {
            array[i] = Integer.parseInt(tokenizer.nextToken());
        }
        for (int i = 0; i < numnum; i++) {
            for (int j = i + 2; j <= maxNum; j++) {
                calculated[i][j] = true;
            }
        }
        ways[0][0] = 1;
        ways[0][1] = 1;
        calculated[0][0] = true;
        calculated[0][1] = true;
        for (int i = 1; i < numnum; i++) {
            for (int j = 0; j <= maxNum; j++) {
                if (calculated[i][j]) {
                    continue;
                }
                ways[i][j] += ways[i - 1][j];
                ways[i][j] += ways[i - 1][Math.min(maxNum, Math.abs(j + 1))];
                ways[i][j] += ways[i - 1][Math.min(maxNum, Math.abs(j - 1))];
                ways[i][j] %= 1000000007;
                calculated[i][j] = true;
            }
        }
        int answer = 1;
        int startindex = 0;
        int width = 0;
        while (startindex < numnum && array[startindex] == 0) {
            width++;
            startindex++;
        }
        answer *= Math.pow(3, width);
        answer %= 1000000007;
        //System.out.println(answer);
        int endindex = numnum - 1;
        width = 0;
        while (array[endindex] == 0 && endindex > startindex) {
            width++;
            endindex--;
        }
        answer *= Math.pow(3, width);
        answer %= 1000000007;
        //System.out.println(answer);
        int index = startindex;
        width = 0;
        int pre = index < numnum ? array[index] : 0;
        int post = -1;
        while (index <= endindex) {
            if (array[index] == 0) {
                width++;
                if (width == 1) {
                    pre = array[index - 1];
                }
            } else {
                post = array[index];
                //System.out.println(width + " " + Math.abs(post - pre) + " " + ways[width][Math.abs(post - pre)]);
                answer *= ways[width][Math.abs(post - pre)];
                answer %= 1000000007;
                width = 0;
            }
            index++;
        }
        System.out.println(answer);

        in.close();
    }
}