import java.io.*;
import java.util.*;

public class d {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int nLanes = Integer.parseInt(tokenizer.nextToken());
        int width = Integer.parseInt(tokenizer.nextToken());
        int[] offset = new int[nLanes + 1];
        int[] interval = new int[nLanes + 1];
        int[] speed = new int[nLanes + 1];
        boolean[] left = new boolean[nLanes + 1];
        for (int i = left.length - 1; i > 0; i--) {
            left[i] = (left.length - 1 - i) % 2 == 1;
        }
        for (int i = 0; i < nLanes; i++) {
            int i2 = nLanes - i;
            tokenizer = new StringTokenizer(in.readLine());
            offset[i2] = Integer.parseInt(tokenizer.nextToken());
            if (left[i2]) {
                offset[i2] = width - 1 - offset[i2];
            }
            interval[i2] = Integer.parseInt(tokenizer.nextToken());
            speed[i2] = Integer.parseInt(tokenizer.nextToken()) * (left[i2] ? -1 : 1);
        }
        tokenizer = new StringTokenizer(in.readLine());
        int fx = Integer.parseInt(tokenizer.nextToken());
        int fy = 0;
        String moves = tokenizer.nextToken();
        int nmoves = moves.length();
        int[] dx = new int[] { 1, 0, -1, 0 };
        int[] dy = new int[] { 0, 1, 0, -1 };
        boolean win = false;
        for (int i = 0; i < nmoves; i++) {
            // System.out.println(i);
            int move = 0;
            if (moves.charAt(i) == 'U') {
                move = 1;
            } else if (moves.charAt(i) == 'D') {
                move = 3;
            } else if (moves.charAt(i) == 'L') {
                move = 2;
            }
            fx += dx[move];
            fy += dy[move];
            if (fy > nLanes) {
                win = true;
                break;
            }
            if (fy == 0)
                continue;
            boolean[] unsafe = new boolean[width];
            int absspeed = Math.abs(speed[fy]);
            int currOffset = Math.floorMod(offset[fy] + speed[fy] * i, width);
            // System.out.println("currOffset: " + currOffset + " interval " + interval[fy]
            // + " speed " + speed[fy]);
            int inc = speed[fy] > 0 ? 1 : -1;
            for (int j = currOffset;; j += interval[fy]) {
                for (int k = 1; k <= absspeed; k++) {
                    if (k * inc + j >= 0 && k * inc + j < width) {
                        unsafe[k * inc + j] = true;
                    }
                }
                if (j >= width)
                    break;
            }
            for (int j = currOffset;; j -= interval[fy]) {
                for (int k = 1; k <= absspeed; k++) {
                    if (k * inc + j >= 0 && k * inc + j < width) {
                        unsafe[k * inc + j] = true;
                    }
                }
                if (j < 0)
                    break;
            }
            // System.out.println("Move: " + i + " fx: " + fx + " fy: " + fy + " " +
            // Arrays.toString(unsafe));
            if (unsafe[fx]) {
                win = false;
                break;
            }
            int prevFx = fx - dx[move];
            if (((speed[fy] < 0 && dx[move] > 0) || (speed[fy] > 0 && dx[move] < 0)) && unsafe[prevFx]) {
                win = false;
                break;
            }

        }
        System.out.println(win ? "safe" : "squish");

        in.close();
    }
}