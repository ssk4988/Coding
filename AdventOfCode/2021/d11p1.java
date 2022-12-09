import java.io.*;
import java.util.*;

public class d11p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d11p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        int numdays = 500;
        int m = input.size();
        int n = input.get(0).length();
        oct[][] octs = new oct[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                octs[i][j] = new oct(input.get(i).charAt(j) - '0', numdays);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (k == 0 && l == 0)
                            continue;
                        if (i + k < 0 || i + k >= m || j + l < 0 || j + l >= n)
                            continue;
                        oct o = octs[i + k][j + l];
                        octs[i][j].neighbors.add(o);
                    }
                }
            }
        }
        for (int day = 1; day <= numdays; day++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    octs[i][j].val[day] = octs[i][j].val[day - 1] + 1;
                }
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (octs[i][j].val[day] >= 10) {
                        octs[i][j].flash(day);
                    }
                }
            }
            int num = m * n;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (octs[i][j].flashed[day]) {
                        num--;
                    }
                }
            }
            if(num == 0){
                System.out.println("flashed " + day);
            }
        }
        int answer = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(octs[i][j].val[numdays]);
                answer += octs[i][j].numFlashes;
            }
            System.out.println();
        }
        System.out.println(answer);
        in.close();
    }

    public static class oct {
        int[] val;
        int numFlashes = 0;
        boolean[] flashed;
        ArrayList<oct> neighbors = new ArrayList<>();

        public oct(int init, int numdays) {
            val = new int[numdays + 1];
            val[0] = init;
            flashed = new boolean[numdays + 1];
        }

        public void flash(int turn) {
            if (flashed[turn] || val[turn] < 10)
                return;
            val[turn] = 0;
            flashed[turn] = true;
            for (oct o : neighbors) {
                if(o.flashed[turn]) continue;
                if (o.val[turn] < 10) {
                    o.val[turn]++;
                }
                if (o.val[turn] >= 10) {
                    o.flash(turn);
                }
            }
            numFlashes++;
        }
    }
}