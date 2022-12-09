import java.io.*;
import java.util.*;

public class d7p1 {
    public static ArrayList<ArrayList<Integer>> children;
    public static ArrayList<ArrayList<Integer>> parents;
    public static ArrayList<ArrayList<Integer>> nums;
    public static TreeMap<String, Integer> bagIndex;
    public static int[][] contains;
    public static int[] contains2;
    public static int bagIndex1;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d7p1.in"));
        bagIndex = new TreeMap<>();
        bagIndex1 = 0;
        String line;
        children = new ArrayList<>();
        parents = new ArrayList<>();
        nums = new ArrayList<>();
        while ((line = in.readLine()) != null) {
            line = line.substring(0, line.length() - 1);
            String inbag = line.split(" contain ")[0].split(" bags")[0];
            if(!bagIndex.containsKey(inbag)){
                bagIndex.put(inbag, bagIndex1);
                bagIndex1++;
                children.add(new ArrayList<>());
                parents.add(new ArrayList<>());
                nums.add(new ArrayList<>());
            }
            String[] outbags1 = line.split(" contain ")[1].split(", ");
            if(outbags1[0].split(" ")[0].equals("no")){
                continue;
            }
            for(String b : outbags1){
                int numb = Integer.parseInt(b.split(" ")[0]);
                String l = b.split(" ")[1] + " " + b.split(" ")[2];
                if(!bagIndex.containsKey(l)){
                    bagIndex.put(l, bagIndex1);
                    bagIndex1++;
                    children.add(new ArrayList<>());
                    parents.add(new ArrayList<>());
                    nums.add(new ArrayList<>());
                }
                children.get(bagIndex.get(inbag)).add(bagIndex.get(l));
                parents.get(bagIndex.get(l)).add(bagIndex.get(inbag));
                nums.get(bagIndex.get(inbag)).add(numb);
            }
        }
        
        
        int shinyGoldIndex = bagIndex.get("shiny gold");
        int numBags = 0;
        ArrayList<Integer> alreadyParents = new ArrayList<>();
        ArrayList<Integer> queue = new ArrayList<>();
        queue.addAll(parents.get(shinyGoldIndex));
        while(queue.size() > 0){
            int newInd = queue.remove(0);
            if(!alreadyParents.contains(newInd)){
                numBags++;
                queue.addAll(parents.get(newInd));
                alreadyParents.add(newInd);
            }
        }
        System.out.println(numBags);
        
        contains = new int[bagIndex1][bagIndex1];
        contains2 = new int[bagIndex1];
        Arrays.fill(contains2, -1);
        for(int i = 0; i < bagIndex1; i++){
            ArrayList<Integer> l = children.get(i);
            if(l.size() == 0) contains2[i] = 0;
            for(int j = 0; j < l.size(); j++){
                contains[i][l.get(j)] = nums.get(i).get(j);
            }
        }
        for(int i = 0; i < bagIndex1; i++){
            solve(i);
        }
        System.out.println(contains2[shinyGoldIndex]);


        in.close();
    }
    public static void solve(int index){
        if(contains2[index] != -1){
            return;
        }
        int sum = 0;
        for(int i = 0; i < bagIndex1; i++){
            if(contains[index][i] > 0){
                sum += contains[index][i];
                solve(i);
                sum += contains[index][i] * contains2[i];
            }
        }
        contains2[index] = sum;
    }

}
