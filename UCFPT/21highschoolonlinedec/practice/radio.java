import java.io.*;
import java.util.*;

public class radio {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numDays = Integer.parseInt(in.readLine());
        for (int i = 0; i < numDays; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numStations = Integer.parseInt(tokenizer.nextToken());
            int numPreset = Integer.parseInt(tokenizer.nextToken());
            int numSwitches = Integer.parseInt(tokenizer.nextToken());
            Map<String, Integer> index = new HashMap<>();
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < numStations; j++) {
                index.put(tokenizer.nextToken(), j);
            }
            Set<Integer> isPreset = new HashSet<>();
            tokenizer = new StringTokenizer(in.readLine());
            for (int j = 0; j < numPreset; j++) {
                isPreset.add(index.get(tokenizer.nextToken()));
            }
            int[] distToPreset = new int[numStations];
            Arrays.fill(distToPreset, 1000);
            for (int j : isPreset) {
                distToPreset[j] = 0;
            }
            for (int j = 1; j < 2 * numStations + 1; j++) {
                int jind = j % numStations;
                distToPreset[jind] = Math.min(distToPreset[(j - 1) % numStations] + 1, distToPreset[jind]);
            }
            for (int j = 2 * numStations; j >= 0; j--) {
                int jind = j % numStations;
                distToPreset[jind] = Math.min(distToPreset[(j + 1) % numStations] + 1, distToPreset[jind]);
            }
            System.out.printf("Day #%d:%n", (i + 1));
            for (int j = 0; j < numSwitches; j++) {
                tokenizer = new StringTokenizer(in.readLine());
                int s1 = index.get(tokenizer.nextToken());
                int s2 = index.get(tokenizer.nextToken());
                int answer = Math.min(distToPreset[s2] + 1,
                        Math.min(Math.abs(s2 - s1), Math.abs(s1 + numStations - s2)));
                System.out.println(answer + " " + distToPreset[s1] + " " + distToPreset[s2] + " " + (s2 - s1) + " "
                        + (s1 + numStations - s2));
            }
            System.out.println();
        }
        in.close();
        out.close();
    }
}