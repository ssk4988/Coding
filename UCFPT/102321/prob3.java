/*
ID: ssk49881
LANG: JAVA
TASK: prob3
*/

import java.io.*;
import java.util.*;

public class prob3 {
    public static int[][] board;
    public static int[][] component;
    public static ArrayList<Integer> componentSize;
    public static int numComponents = 0;

    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        String line;
        int numCases = 1;
        while (!(line = in.readLine()).equals("0 0")) {
            StringTokenizer tokenizer = new StringTokenizer(line);
            int n = Integer.parseInt(tokenizer.nextToken());
            int m = Integer.parseInt(tokenizer.nextToken());
            int numKeys = 0;

            Map<Character, Integer> map = new HashMap<>();
            board = new int[m][n];

            for (int i = 0; i < m; i++) {
                String s = in.readLine();
                for (int j = 0; j < n; j++) {
                    char c = s.charAt(j);
                    if (!map.containsKey(c)) {
                        map.put(c, numKeys);
                        numKeys++;
                    }
                    board[i][j] = map.get(c);
                }
            }
            boolean test = true;
            while (test) {
                test = false;
                numComponents = 0;
                component = new int[m][n];
                componentSize = new ArrayList<>();
                for (int i = 0; i < m; i++) {
                    Arrays.fill(component[i], -1);
                }
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        if (component[i][j] == -1 && board[i][j] != -1) {
                            componentSize.add(0);
                            flood_fill(i * n + j);
                            numComponents++;
                        }
                    }
                }

                for (int compnum = 0; compnum < componentSize.size(); compnum++) {
                    if (componentSize.get(compnum) >= 4) {
                        for (int i = 0; i < m; i++) {
                            for (int j = 0; j < n; j++) {
                                if (component[i][j] == compnum) {
                                    board[i][j] = -1;
                                    test = true;
                                }
                            }
                        }
                    }
                }
                for (int j = 0; j < n; j++) {
                    for (int i = 0; i < m; i++) {
                        if (board[i][j] == -1) {
                            for (int k = i; k > 0; k--) {
                                board[k][j] = board[k - 1][j];
                            }
                            board[0][j] = -1;
                        }
                    }
                }
            }

            // System.out.println(componentSize);
            for (int i = 0; i < m; i++) {
                // System.out.println(Arrays.toString(board[i]));
            }
            int answer = 0;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] != -1) {
                        answer++;
                    }
                }
            }
            System.out.println(numCases + ": " + answer);

            numCases++;
        }

        in.close();
        out.close();
    }

    public static void flood_fill(int index) {
        int m = board.length;
        int n = board[0].length;
        ArrayList<Integer> list = new ArrayList<>();
        list.add(index);
        while (list.size() > 0) {
            ArrayList<Integer> nextList = new ArrayList<>();
            while (list.size() > 0) {
                int next = list.remove(0);
                int m1 = next / n;
                int n1 = next % n;
                component[m1][n1] = numComponents;
                componentSize.set(numComponents, componentSize.get(numComponents) + 1);
                if (m1 > 0 && board[m1 - 1][n1] == board[m1][n1] && component[m1 - 1][n1] == -1) {
                    nextList.add((m1 - 1) * n + n1);
                }
                if (n1 > 0 && board[m1][n1 - 1] == board[m1][n1] && component[m1][n1 - 1] == -1) {
                    nextList.add((m1) * n + n1 - 1);
                }
                if (m1 < m - 1 && board[m1 + 1][n1] == board[m1][n1] && component[m1 + 1][n1] == -1) {
                    nextList.add((m1 + 1) * n + n1);
                }
                if (n1 < n - 1 && board[m1][n1 + 1] == board[m1][n1] && component[m1][n1 + 1] == -1) {
                    nextList.add((m1) * n + n1 + 1);
                }
            }
            list = nextList;
        }
    }
}