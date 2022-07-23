import java.io.*;
import java.util.*;

public class c {
    static ArrayList<Integer> permutations = new ArrayList<>();
    static int[] vals = new int[4];
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int n = Integer.parseInt(in.readLine());
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        card[] cards = new card[n];
        int[] nsuit = new int[4];
        for(int i = 0; i < n; i++){
            String str= tokenizer.nextToken();
            int suit = 0;
            char s = str.charAt(1);
            char r = str.charAt(0);
            int rank = 0;
            if(r >= '2' && r <= '9'){
                rank = r - '0';
            }
            if(r == 'T') rank = 10;
            if(r == 'J') rank = 11;
            if(r == 'Q') rank = 12;
            if(r == 'K') rank = 13;
            if(r == 'A') rank = 14;
            if(s == 's') suit = 0;
            if(s == 'h') suit = 1;
            if(s == 'd') suit = 2;
            if(s == 'c') suit = 3;
            cards[i] = new card(suit, rank, i);
            nsuit[suit]++;
        }
        card[][] ascending = new card[4][];
        card[][] descending = new card[4][];
        
        for(int i = 0; i < 4; i++){
            ascending[i] = new card[nsuit[i]];
            descending[i] = new card[nsuit[i]];
        }
        nsuit = new int[4];
        for(int i = 0; i < n; i++){
            ascending[cards[i].suit][nsuit[cards[i].suit]] = cards[i];
            descending[cards[i].suit][nsuit[cards[i].suit]] = cards[i];
            nsuit[cards[i].suit]++;
        }
        for(int i = 0; i < 4; i++){
            Arrays.sort(ascending[i], new byRank(true));
            Arrays.sort(descending[i], new byRank(false));
        }
        boolean[] used = new boolean[4];
        generate(used, 0);
        //System.out.println(permutations);
        int answer = n;
        for(int i = 0; i < (1 << 4); i++){
            //set bit means ascending
            boolean[] as = new boolean[4];
            for(int j = 0; j < 4; j++){
                if(((1 << j) & i) == (1 << j)){
                    as[j] = true;
                }
            }
            int pi = 0;
            while(pi < permutations.size()){
                int[] perm = {permutations.get(pi++), permutations.get(pi++), permutations.get(pi++), permutations.get(pi++)};
                int[] arr = new int[n];
                int val = 0;
                //perm[j] = the suit that is j in the order
                for(int j = 0; j < 4; j++){
                    card[] list = as[perm[j]] ? ascending[perm[j]] : descending[perm[j]];
                    for(card c : list){
                        c.index = val++;
                    }
                }
                for(int j = 0; j < n; j++){
                    arr[j] = cards[j].index;
                }
                int[] lis = new int[n];
                Arrays.fill(lis, 1);
                for(int k = 0; k < lis.length; k++){
                    for(int l = 0; l < k; l++){
                        if(arr[l] < arr[k] && lis[l] + 1 > lis[k]){
                            lis[k] = lis[l] + 1;
                        }
                    }
                }
                int maxlis = 0;
                for(int j = 0; j < lis.length; j++){
                    maxlis = Math.max(maxlis, lis[j]);
                }
                answer = Math.min(answer, n - maxlis);
            }
        }
        System.out.println(answer);


        in.close();
        out.close();
    }
    public static void generate(boolean[] used, int length){
        if(length == 4){
            for(int i : vals){
                permutations.add(i);
            }
        }
        for(int i = 0; i < used.length; i++){
            if(used[i]) continue;
            used[i] = true;
            vals[length] = i;
            generate(used, length+1);
            used[i] = false;
        }
    }
    public static class byRank implements Comparator<card>{
        boolean ascending;
        public byRank(boolean ascending){
            this.ascending = ascending;
        }
        @Override
        public int compare(c.card o1, c.card o2) {
            if(ascending){
                return o1.rank - o2.rank;
            }
            return o2.rank - o1.rank;
        }
    }
    public static class card{
        int suit;
        int rank;
        int index = 0;
        int id = 0;
        public card(int suit, int rank, int id){
            this.suit = suit;
            this.rank = rank;
            this.id = id;
        }
    }
}