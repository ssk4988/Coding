import java.io.*;
import java.util.*;

public class d4p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d4p1.in"));
        String[] orderStr = in.readLine().split(",");
        int[] order = new int[orderStr.length];
        for (int i = 0; i < order.length; i++) {
            order[i] = Integer.parseInt(orderStr[i]);
        }
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            for (int i = 0; i < 5; i++) {
                input.add(in.readLine());
            }
        }
        int[][][] boards = new int[input.size() / 5][5][5];
        for (int i = 0; i < boards.length; i++) {
            for (int j = 0; j < 5; j++) {
                StringTokenizer tokenizer = new StringTokenizer(input.get(5 * i + j));
                for (int k = 0; k < 5; k++) {
                    boards[i][j][k] = Integer.parseInt(tokenizer.nextToken());
                }
            }
        }
        int[] movesToWin = new int[boards.length];
        int[] finalScore = new int[boards.length];
        boolean[][][] used = new boolean[boards.length][5][5];
        for (int i = 0; i < boards.length; i++) {
            moves: for (int move = 0; move < order.length; move++) {
                bsearch: for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 5; k++) {
                        if (order[move] == boards[i][j][k]) {
                            used[i][j][k] = true;
                            boolean win = false;
                            for (int a = 0; a < 5; a++) {
                                if (!used[i][j][a])
                                    break;
                                if (a == 4)
                                    win = true;
                            }
                            for (int a = 0; a < 5; a++) {
                                if (!used[i][a][k])
                                    break;
                                if (a == 4)
                                    win = true;
                            }
                            if (win) {
                                movesToWin[i] = move;
                                break moves;
                            }
                            break bsearch;
                        }
                    }
                }
            }
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    if (!used[i][j][k])
                        finalScore[i] += boards[i][j][k];
                }
            }
            finalScore[i] *= order[movesToWin[i]];
        }
        int maxWindex = 0;
        int minWindex = 0;
        for (int i = 0; i < boards.length; i++) {
            System.out.println(movesToWin[i] + " " + finalScore[i]);
            if (movesToWin[i] > 0 && movesToWin[i] < movesToWin[minWindex]) {
                minWindex = i;
            }
            if (movesToWin[i] > 0 && movesToWin[i] > movesToWin[maxWindex]) {
                maxWindex = i;
            }
        }
        System.out.println(finalScore[minWindex]);
        System.out.println(finalScore[maxWindex]);
        in.close();
    }

}
