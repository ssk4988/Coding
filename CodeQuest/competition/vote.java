import java.io.*;
import java.util.*;

public class vote {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        StringBuilder b = new StringBuilder();
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());

            int ballots = Integer.parseInt(tokenizer.nextToken());
            int candidates = Integer.parseInt(tokenizer.nextToken());
            int[][] votes = new int[ballots][candidates];
            for (int i = 0; i < ballots; i++) {
                String s = in.readLine();
                for (int j = 0; j < candidates; j++) {
                    votes[i][j] = s.charAt(j) - 'A';
                }
            }
            boolean[] valid = new boolean[26];
            Arrays.fill(valid, true);
            int tallies = 1;
            tally: while (true) {
                int[] vote = new int[candidates];
                for (int i = 0; i < ballots; i++) {
                    int index = 0;
                    while (!valid[votes[i][index]]) {
                        index++;
                    }
                    vote[votes[i][index]]++;
                }
                for (int i = 0; i < candidates; i++) {
                    if (vote[i] >= ballots / 2 + 1) {
                        b.append(String.format("Candidate %s won with %.1f%% of the vote after %d tallies\n",
                                (char) (i + 'A'), 100.0 * vote[i] / ballots, tallies));
                        break tally;
                    }
                }
                ArrayList<Integer> min = new ArrayList<>();
                for (int i = 0; i < candidates; i++) {
                    if(!valid[i])continue;
                    if (min.size() == 0 || vote[i] == vote[min.get(0)]) {
                        min.add(i);
                    }
                    else if(vote[i] < vote[min.get(0)]){
                        min = new ArrayList<>();
                        min.add(i);
                    }
                }
                for(int k : min){
                    valid[k] = false;
                }
                
                tallies++;
            }
        }
        System.out.print(b);
        in.close();
        out.close();
    }
}