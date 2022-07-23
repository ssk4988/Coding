import java.io.*;
import java.util.*;

public class a {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int m = Integer.parseInt(tokenizer.nextToken());
        int b = Integer.parseInt(tokenizer.nextToken());
        pixel[][] pixels = new pixel[m][n];
        for (int i = 0; i < m; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < n; j++) {
                pixels[i][j] = new pixel(i, j, Integer.parseInt(tokenizer.nextToken()), b);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        pixel p2 = pixels[(i + m + k) % m][(j + n + l) % n];
                        pixels[i][j].neighbors.add(p2);
                        p2.neighbors.add(pixels[i][j]);
                    }
                }
            }
        }
        for (int b1 = 0; b1 < b; b1++) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    pixels[i][j].blur();
                }
            }
        }
        Set<Long> vals = new HashSet<>();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vals.add(pixels[i][j].blur[b][0]);
            }
        }
        System.out.println(vals.size());

        in.close();
    }

    public static class pixel {
        long x = 0;
        long y = 0;
        long[][] blur;
        int numBlurred = 0;
        ArrayList<pixel> neighbors = new ArrayList<>();

        public pixel(int x, int y, int val, int b) {
            this.x = x;
            this.y = y;
            blur = new long[b + 1][2];
            blur[0][0] = val;
            blur[0][1] = 1;
        }

        public void blur() {
            blur[numBlurred + 1][1] = blur[numBlurred][1] * 9;
            for (pixel p : neighbors) {
                blur[numBlurred + 1][0] += p.blur[numBlurred][0];
            }
            numBlurred++;
        }
    }
}