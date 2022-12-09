import java.io.*;
import java.util.*;

public class d9p1 {
    public static int[] dx = { 0, 1, 0, -1 };
    public static int[] dy = { 1, 0, -1, 0 };

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d9p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        int length = 0;
        while ((line = in.readLine()) != null) {
            input.add(line);
            length = line.length();
        }
        int[][] board = new int[input.size()][length];
        for (int i = 0; i < input.size(); i++) {
            for (int j = 0; j < input.get(i).length(); j++) {
                board[i][j] = input.get(i).charAt(j) - '0';
            }
        }
        int answer = 0;
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                boolean less = true;
                for (int k = 0; k < dx.length; k++) {
                    if (i + dx[k] < board.length && i + dx[k] >= 0 && j + dy[k] < board[i].length && j + dy[k] >= 0
                            && board[i][j] >= board[i + dx[k]][j + dy[k]]) {
                        less = false;
                    }
                }
                if (less)
                    answer += 1 + board[i][j];
            }
        }
        System.out.println(answer);

        in.close();
    }

}
