import java.io.*;
import java.util.*;

public class d12p1 {
    public static int answer = 0;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d12p1.in"));
        ArrayList<String> input = new ArrayList<>();
        String line;
        while ((line = in.readLine()) != null) {
            input.add(line);
        }
        in.close();

        Map<String, Integer> rename = new HashMap<>();
        ArrayList<Boolean> big = new ArrayList<>();
        for (String s : input) {
            String[] arr = s.split("-");
            for (int i = 0; i < arr.length; i++) {
                if (!rename.containsKey(arr[i])) {
                    rename.put(arr[i], rename.size());
                    char c = arr[i].charAt(0);
                    big.add(c <= 'Z' && c >= 'A');
                }
            }
        }
        cave[] caves = new cave[rename.size()];
        for (String k : rename.keySet()) {
            int i = rename.get(k);
            caves[i] = new cave(i, k);
            caves[i].big = big.get(i);
        }
        for (String s : input) {
            String[] arr = s.split("-");
            caves[rename.get(arr[0])].neighbors.add(caves[rename.get(arr[1])]);
            caves[rename.get(arr[1])].neighbors.add(caves[rename.get(arr[0])]);
        }
        dfs(caves[rename.get("start")], true);
        System.out.println(answer);
    }
    public static void dfs(cave curr, boolean canTwice){
        if(curr.name.equals("end")){
            answer++;
            return;
        }
        if(!curr.big && curr.numVisited > 0){
            if(!canTwice || curr.name.equals("start")){
                return;
            }
            else{
                canTwice = false;
            }
        }
        curr.numVisited++;
        for(cave c : curr.neighbors){
            dfs(c, canTwice);
        }
        curr.numVisited--;
        if(!curr.big && curr.numVisited > 0 && !canTwice){
            canTwice = true;
        }
    }

    public static class cave {
        int id = 0;
        String name;
        boolean big = true;
        int numVisited = 0;
        ArrayList<cave> neighbors = new ArrayList<>();

        public cave(int id, String name) {
            this.id = id;
            this.name = name;
        }
    }
}
