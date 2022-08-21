import java.io.*;
import java.util.*;

public class p006 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(tokenizer.nextToken());
        int len = Integer.parseInt(tokenizer.nextToken());
        ArrayList<str> list = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            list.add(new str(i, in.readLine()));
        }
        boolean[] wrong = new boolean[len];
        for (int i = 0; i < len; i++) {
            calc(list, 0, i, i);
            wrong[i] = wrong(list);
        }
        int bestLen = n;
        int bestL = 0;
        int bestR = len - 1;
        int l = 0;
        int r = 0;
        while (l < len && r < len) {
            calc(list, 0, l, r);
            while (r + 1 < len && !wrong(list) && !right(list)) {
                r++;
                for (int i = 0; i < n; i++) {
                    int tmp = list.get(i).right;
                    if (list.get(i).left != list.get(i).right) {
                        calc(list.subList(list.get(i).left, list.get(i).right + 1), list.get(i).left, r, r);
                    }
                    i = tmp;
                }
            }
            if (right(list)) {
                int low = l;
                int high = r;
                while (low < high) {
                    int mid = low + (high - low + 1) / 2;
                    calc(list, 0, mid, r);
                    if (right(list)) {
                        low = mid;
                    } else {
                        high = mid - 1;
                    }
                }
                l = low;
                if (bestLen > (r - l + 1)) {
                    bestLen = r - l + 1;
                    bestL = l;
                    bestR = r;
                }
            }
            l = ++r;
        }
        System.out.println((bestL + 1) + " " + (bestR + 1));
        in.close();
    }

    public static boolean calc(List<str> list, int offset, int left, int right) {
        comp c = new comp(left, right);
        Collections.sort(list, c);
        for (int i = 0; i < list.size(); i++) {
            int len = 1;
            while (i + len < list.size() && c.compare(list.get(i), list.get(i + len)) == 0) {
                len++;
            }
            for (int j = i; j < i + len; j++) {
                list.get(j).left = i + offset;
                list.get(j).right = i + len - 1 + offset;
            }
            i = i + len - 1;
        }
        return true;
    }

    public static boolean right(ArrayList<str> list) {
        boolean right = true;
        for (str s : list) {
            if (s.id != s.left || s.id != s.right)
                right = false;
        }
        return right;
    }

    public static boolean wrong(ArrayList<str> list) {
        boolean wrong = false;
        for (str s : list) {
            if (s.id < s.left || s.id > s.right)
                wrong = true;
        }
        return wrong;
    }

    public static class comp implements Comparator<str> {
        int left = 0;
        int right = 0;

        @Override
        public int compare(p006.str o1, p006.str o2) {
            for (int i = left; i <= right; i++) {
                if (o1.val.charAt(i) != o2.val.charAt(i))
                    return o1.val.charAt(i) - o2.val.charAt(i);
            }
            return 0;
        }

        public comp(int left, int right) {
            this.left = left;
            this.right = right;
        }
    }

    public static class str {
        String val;
        int id;
        int left = -1;
        int right = -1;

        public str(int id, String val) {
            this.val = val;
            this.id = id;
        }
    }
}