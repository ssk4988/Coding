/*
ID: ssk49881
LANG: JAVA
TASK: measurement
*/

import java.io.*;
import java.util.*;

public class measurement {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("measurement.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("measurement.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numMeasurements = Integer.parseInt(tokenizer.nextToken());
        int initialValue = Integer.parseInt(tokenizer.nextToken());
        TreeMap<Integer, ArrayList<Integer>> production = new TreeMap<>();
        Map<Integer, Integer> cowProduction = new HashMap<>();
        Set<Integer> ids = new HashSet<>();
        Triple[] measurements = new Triple[numMeasurements];
        for(int i = 0; i < numMeasurements; i++){
            tokenizer = new StringTokenizer(in.readLine());
            int time = Integer.parseInt(tokenizer.nextToken());
            int id = Integer.parseInt(tokenizer.nextToken());
            int increment = Integer.parseInt(tokenizer.nextToken());
            ids.add(id);
            measurements[i] = new Triple(time, id, increment);
        }
        int numChanges = 0;
        Arrays.sort(measurements);
        production.put(initialValue, new ArrayList<>());
        ArrayList<Integer> initialList = production.get(initialValue);
        for(int id : ids){
            initialList.add(id);
            cowProduction.put(id, initialValue);
        }
        Collections.sort(initialList);
        String s = initialList.toString();
        for(Triple measurement : measurements){
            int time = measurement.time;
            int id = measurement.id;
            int increment = measurement.increment;
            int preValue = cowProduction.get(id);
            int postValue = preValue + increment;
            ArrayList<Integer> preList = production.get(preValue);
            ArrayList<Integer> postList = null;
            if(!production.containsKey(postValue)){
                production.put(postValue, new ArrayList<>());
            }
            postList = production.get(postValue);
            int index = Collections.binarySearch(preList, id);
            if(index < 0) index = -(index+1);
            preList.remove(index);
            index = Collections.binarySearch(postList, id);
            if(index < 0) index = -(index+1);
            postList.add(index, id);
            if(preList.size() == 0){
                production.remove(preValue);
            }
            cowProduction.put(id, postValue);
            String ns = production.get(production.lastKey()).toString();
            if(!s.equals(ns)){
                numChanges++;
                s = ns;
            }
        }
        out.println(numChanges);



        in.close();
        out.close();
    }
    public static class Triple implements Comparable<Triple>{
        int time;
        int id;
        int increment;
        public Triple(int time, int id, int increment){
            this.time = time;
            this.id = id;
            this.increment = increment;
        }
        @Override
        public int compareTo(measurement.Triple o) {
            return this.time - o.time;
        }
    }
}