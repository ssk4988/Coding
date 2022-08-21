import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        card[] cards = new card[n];
        int[] freq = new int[3001];
        for (int i = 0; i < n; i++) {
            int[][] board = new int[5][5];
            for (int j = 0; j < 5; j++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                for (int k = 0; k < 5; k++) {
                    board[j][k] = Integer.parseInt(tokenizer.nextToken());
                    freq[board[j][k]]++;
                }
            }
            cards[i] = new card(i, board);
            if (i + 1 < n)
                in.readLine();
        }
        int p1 = Integer.MAX_VALUE;
        int p2 = Integer.MAX_VALUE;
        for (int v = 0; v < freq.length; v++) {
            if (freq[v] <= 1)
                continue;
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    for (int r1 = 0; r1 < 5; r1++) {
                        boolean icontains = false;
                        for (int c1 = 0; c1 < 5; c1++) {
                            if (cards[i].board[r1][c1] == v) {
                                icontains = true;
                                break;
                            }
                        }
                        if (!icontains)
                            continue;
                        icontains = false;
                        pair: for (int r2 = 0; r2 < 5; r2++) {
                            for (int c2 = 0; c2 < 5; c2++) {
                                if (cards[j].board[r2][c2] == v) {
                                    icontains = true;
                                    break;
                                }
                            }
                            if (!icontains)
                                continue;
                            Set<Integer> others = new HashSet<>();
                            for (int c = 0; c < 5; c++) {
                                if (cards[i].board[r1][c] != v)
                                    others.add(cards[i].board[r1][c]);
                                if (cards[j].board[r2][c] != v)
                                    others.add(cards[i].board[r2][c]);
                            }
                            boolean works = true;
                            for (int k = 0; k < n && works; k++) {
                                if (k == i || k == j)
                                    continue;
                                test: for (int r3 = 0; r3 < 5; r3++) {
                                    boolean doesntwork = true;
                                    for (int c = 0; c < 5; c++) {
                                        if (!others.contains(cards[k].board[r3][c])) {
                                            doesntwork = false;
                                        }
                                    }
                                    if(doesntwork){
                                        works = false;
                                    }
                                }
                            }
                            if (works && (i < p1 || (i == p1 && j < p2))) {
                                p1 = i;
                                p2 = j;
                            }
                        }
                    }
                }
            }
        }
        if(p1 == Integer.MAX_VALUE){
            System.out.println("no ties");
        }
        else{
            System.out.println((p1+1) + " " + (p2+1));
        }

        in.close();
        out.close();
    }

    public static class card {
        int id;
        int[][] board = new int[5][5];
        Set<Integer> totalset = new HashSet<>();
        Set<Integer>[] sets = new Set[5];

        public card(int id, int[][] board) {
            this.id = id;
            this.board = board;
            for (int i = 0; i < 5; i++) {
                sets[i] = new HashSet<>();
                for (int j = 0; j < 5; j++) {
                    sets[i].add(this.board[i][j]);
                    totalset.add(this.board[i][j]);
                }
            }
        }
    }
}