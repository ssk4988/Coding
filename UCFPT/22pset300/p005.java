import java.io.*;
import java.util.*;

public class p005 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int h = Integer.parseInt(tokenizer.nextToken());
        int w = Integer.parseInt(tokenizer.nextToken());
        int k = Integer.parseInt(tokenizer.nextToken());
        int[][] board = new int[w][h];
        int[] height = new int[w];
        int[][][] bits = new int[4][][];
        bits[0] = new int[h][w + 1];
        bits[1] = new int[w][h + 1];
        bits[2] = new int[h + w - 1][Math.min(h, w) + 1];
        bits[3] = new int[h + w - 1][Math.min(h, w) + 1];
        tokenizer = new StringTokenizer(in.readLine());
        boolean win = false;
        int moves = 0;
        for (int i = 0; i < h * w && !win; i++) {
            int place = Integer.parseInt(tokenizer.nextToken()) - 1;
            board[place][height[place]] = i % 2 == 0 ? 1 : -1; // 1 is A -1 is B
            for (int j = 0; j < 4; j++) {
                int tree = -1;
                int index = -1;
                if (j == 0) {
                    tree = height[place];
                    index = place;
                }
                else if (j==1){
                    tree = place;
                    index = height[place];
                }
                else if(j==2){
                    tree = w - 1 - (place - height[place]);
                    index = place >= height[place] ? height[place] : place;
                }
                else{
                    tree = place + height[place];
                    index = tree >= w ? w - 1 - place : height[place];
                }
                update(bits[j][tree], index, board[place][height[place]]);
                int cnt = search(bits[j][tree], index);
                if(cnt >= k){
                    win = true;
                }
            }
            height[place]++;
            moves++;
        }
        if (win) {
            System.out.println((moves % 2 == 0 ? "B" : "A") + " " + moves);
        } else {
            System.out.println("D");
        }
        in.close();
    }

    public static void update(int[] bit, int index, int change) {
        index++;
        while (index < bit.length) {
            bit[index] += change;
            index += index & -index;
        }
    }

    public static int sum(int[] bit, int index) {
        int sum = 0;
        while (index > 0) {
            sum += bit[index];
            index -= index & -index;
        }
        return sum;
    }

    public static int search(int[] bit, int index) {
        index++;
        int ans = 1;
        int indsum = sum(bit, index);
        int indsum1 = sum(bit, index - 1);
        int cur = indsum - indsum1;
        int low = index;
        int high = bit.length - 1;
        while (low < high) {
            int mid = low + (high - low + 1) / 2;
            if (sum(bit, mid) - indsum == cur * (mid - index)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        ans += low - index;
        low = 1;
        high = index;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (indsum1 - sum(bit, mid-1) == cur * (index - mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        ans += index - low;

        return ans;
    }
}