import java.io.*;
import java.util.*;

public class d9p2 {
    public static int[] dx = { 0, 1, 0, -1 };
    public static int[] dy = { 1, 0, -1, 0 };
    public static ArrayList<Integer> components = new ArrayList<>();

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
        int[][] component = new int[input.size()][length];
        for (int i = 0; i < input.size(); i++) {
            Arrays.fill(component[i], -1);
            for (int j = 0; j < input.get(i).length(); j++) {
                board[i][j] = input.get(i).charAt(j) - '0';
            }
        }
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
                    flood_fill(board, component, i * board[i].length + j);
                ;
            }
        }
        //System.out.println(components);
        for(int[] i : board){
            //System.out.println(Arrays.toString(i));
        }
        int[] compArr = new int[components.size()];
        for(int[] i : component){
            //System.out.println(Arrays.toString(i));
            for(int j : i){
                if(j < 0) continue;
                compArr[j]++;
            }
        }
        int answer = 1;
        Arrays.sort(compArr);
        for(int i = compArr.length - 1; i > 0 && compArr.length - i <= 3; i--){
            answer *= compArr[i];
        }
        System.out.println(answer);
        System.out.println(Arrays.toString(compArr));
        in.close();
    }

    public static void flood_fill(int[][] board, int[][] component, int index) {
        components.add(0);
        LinkedList<Integer> queue = new LinkedList<>();
        queue.add(index);
        while (!queue.isEmpty()) {
            int ind = queue.poll();
            int x = ind / board[0].length;
            int y = ind % board[0].length;
            component[x][y] = components.size() - 1;
            components.set(component[x][y], components.get(component[x][y]) + 1);
            for (int k = 0; k < dx.length; k++) {
                if (x + dx[k] < board.length && x + dx[k] >= 0 && y + dy[k] < board[x].length && y + dy[k] >= 0
                        && board[x][y] <= board[x + dx[k]][y + dy[k]] && component[x + dx[k]][y + dy[k]] == -1
                        && board[x + dx[k]][y + dy[k]] < 9) {
                    queue.add((x + dx[k]) * board[x].length + y + dy[k]);
                }
            }
        }

    }
}
