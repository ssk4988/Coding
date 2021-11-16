import java.io.*;
import java.util.*;

public class d11p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d11p1.in"));
        ArrayList<String> data = new ArrayList<>();
        String line;
        int width = 0;
        while ((line = in.readLine()) != null) {
            data.add(line);
            width = line.length();
        }
        int height = data.size();
        boolean keepGoing = true;
        int[][] arr = new int[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (data.get(i).charAt(j) == '.') {
                    arr[i][j] = 0;
                }
                if (data.get(i).charAt(j) == 'L') {
                    arr[i][j] = 1;
                }
                if (data.get(i).charAt(j) == '#') {
                    arr[i][j] = 2;
                }
            }
        }
        int[][] arr2 = new int[height][width];
        int times = 0;
        while (keepGoing) {
            times++;
            arr2 = new int[height][width];
            keepGoing = false;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (arr[i][j] == 0) {
                        arr2[i][j] = 0;
                    }
                    if (arr[i][j] == 1) {
                        arr2[i][j] = occupied(arr, i, j) == 0 ? 2 : 1;
                    }
                    if (arr[i][j] == 2) {
                        arr2[i][j] = occupied(arr, i, j) >= 5 ? 1 : 2;
                    }
                }
            }
            for (int i = 0; i < height; i++) {
                String l = "";
                for (int j = 0; j < width; j++) {
                    if (arr[i][j] != arr2[i][j]) {
                        keepGoing = true;
                    }
                    l += Integer.toString(arr[i][j]);
                }
            }
            arr = arr2;

        }
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (arr[i][j] == 2) {
                    count++;
                }
            }
        }
        System.out.println(count);

        in.close();
    }

    public static int occupied(int[][] arr, int height, int width) {
        int count = 0;
        for (int i = 1; height - i >= 0; i++) {
            if (arr[height - i][width] == 2) {
                count++;
                break;
            }
            if (arr[height - i][width] == 1)
                break;
        }
        for (int i = 1; height - i >= 0 && width - i >= 0; i++) {
            if (arr[height - i][width - i] == 2) {
                count++;
                break;
            }
            if (arr[height - i][width - i] == 1)
                break;
        }
        for (int i = 1; height - i >= 0 && width + i < arr[0].length; i++) {
            if (arr[height - i][width + i] == 2) {
                count++;
                break;
            }
            if (arr[height - i][width + i] == 1)
                break;
        }
        for (int i = 1; width - i >= 0; i++) {
            if (arr[height][width - i] == 2) {
                count++;
                break;
            }
            if (arr[height][width - i] == 1)
                break;
        }
        for (int i = 1; height + i < arr.length; i++) {
            if (arr[height + i][width] == 2) {
                count++;
                break;
            }
            if (arr[height + i][width] == 1)
                break;
        }
        for (int i = 1; height + i < arr.length && width - i >= 0; i++) {
            if (arr[height + i][width - i] == 2) {
                count++;
                break;
            }
            if (arr[height + i][width - i] == 1)
                break;
        }
        for (int i = 1; height + i < arr.length && width + i < arr[0].length; i++) {
            if (arr[height + i][width + i] == 2) {
                count++;
                break;
            }
            if (arr[height + i][width + i] == 1)
                break;
        }
        for (int i = 1; width + i < arr[0].length; i++) {
            if (arr[height][width + i] == 2) {
                count++;
                break;
            }
            if (arr[height][width + i] == 1)
                break;
        }
        return count;
    }

}
