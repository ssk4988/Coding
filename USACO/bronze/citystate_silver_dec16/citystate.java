/*
ID: ssk49881
LANG: JAVA
TASK: citystate
*/

import java.io.*;
import java.util.*;

public class citystate {
    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("citystate.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("citystate.out")));
        int numCities = Integer.parseInt(in.readLine());
        TreeSet<String> states = new TreeSet<>();
        TreeMap<String, Integer> citystate = new TreeMap<>();
        for (int i = 0; i < numCities; i++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            String city = tokenizer.nextToken();
            String state = tokenizer.nextToken();
            city = city.substring(0, 2);
            states.add(state);
            if (!citystate.containsKey(city + state))
                citystate.put(city + state, 1);
            else
                citystate.put(city + state, citystate.get(city + state) + 1);
        }
        int count = 0;
        for (String k : citystate.keySet()) {
            String city = k.substring(0, 2);
            String state = k.substring(2);
            if (city.compareTo(state) >= 0)
                continue;
            if (citystate.containsKey(state + city))
                count += citystate.get(city + state) * citystate.get(state + city);
        }
        System.out.println(states.size());
        out.println(count);
        System.out.println(System.currentTimeMillis() - start_time);

        in.close();
        out.close();
    }
}