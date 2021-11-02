import java.io.*;
import java.util.*;

public class ox {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numJumps = Integer.parseInt(tokenizer.nextToken());
        Set<Integer> yearsset = new HashSet<>();
        ArrayList<Integer> years = new ArrayList<>();
        for (int i = 0; i < numCows; i++) {
            int year = Integer.parseInt(in.readLine());
            year /= 12;
            yearsset.add(year);
        }
        years.addAll(yearsset);
        boolean contains0 = years.contains(0);
        if (!contains0) {
            years.add(0);
        }
        Collections.sort(years);

        int yearsElapsed = (years.get(years.size() - 1) + 1);
        numJumps--;
        ArrayList<Integer> gaps = new ArrayList<>();
        for (int i = 1; i < years.size(); i++) {
            int gap = years.get(i) - years.get(i - 1) - 1;
            if(i == 1 && !contains0){
                gap++;
            }
            gaps.add(gap);
        }
        //System.out.println(years);
        //System.out.println(gaps);
        Collections.sort(gaps, (o1, o2) -> o2 - o1);
        while (gaps.size() > 0 && numJumps > 0) {
            yearsElapsed -= gaps.remove(0);
            numJumps--;
        }
        System.out.println(yearsElapsed * 12);

        in.close();
        // out.close();
    }
}