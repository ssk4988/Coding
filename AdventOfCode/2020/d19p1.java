import java.io.*;
import java.util.*;

public class d19p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d19p1.in"));
        Map<Integer, String> txtRules = new HashMap<>();
        String line;
        int aind = -1;
        int bind = -1;
        while((line = in.readLine()) != null && line.length() > 0){
            int ruleNum = Integer.parseInt(line.split(": ")[0]);
            txtRules.put(ruleNum, line.split(": ")[1].replace("\"", ""));
            if(txtRules.get(ruleNum).equals("a")){
                aind = ruleNum;
            }
            if(txtRules.get(ruleNum).equals("b")){
                bind = ruleNum;
            }
        }
        Map<Integer, Boolean> defined = new HashMap<>();
        Map<Integer, ArrayList<String>> rules = new HashMap<>();
        for(int key : txtRules.keySet()){
            rules.put(key, new ArrayList<>());
            defined.put(key, false);
        }
        
        defined.put(aind, true);
        defined.put(bind, true);
        rules.get(aind).add("a");
        rules.get(bind).add("b");
        int numDefined = 2;
        int prevDefined = 0;
        while(numDefined > prevDefined){
            prevDefined = numDefined;
            outer: for(int key : txtRules.keySet()){
                if(defined.get(key)){
                    continue outer;
                }

                String rule = txtRules.get(key);
                for(String s : rule.replace(" | ", " ").split(" ")){
                    if(!defined.get(Integer.parseInt(s))){
                        continue outer;
                    }
                }
                ArrayList<String> arr = new ArrayList<>();
                if(rule.contains(" | ")){
                    int splitInd = rule.indexOf(" | ");
                    arr.add(rule.substring(0, splitInd));
                    arr.add(rule.substring(splitInd + 3));
                    //System.out.println(arr);
                }
                else{
                    arr.add(rule);
                }
                for(String arrstr : arr){
                    String[] components = arrstr.split(" ");
                    int[] componentsNum = new int[components.length];
                    for(int i = 0; i < components.length; i++){
                        componentsNum[i] = Integer.parseInt(components[i]);
                    }
                    ArrayList<String> possible = new ArrayList<>();
                    possible.add("");
                    for(int i = 0; i < componentsNum.length; i++){
                        ArrayList<String> newPossible = new ArrayList<>();
                        for(String s : possible){
                            for(String l : rules.get(componentsNum[i])){
                                newPossible.add(s + l);
                            }
                        }
                        possible = newPossible;
                    }
                    rules.get(key).addAll(possible);
                    defined.put(key, true);
                    numDefined++;
                }
                    
                    
            }
        }
        for(int key : defined.keySet()){
            if(defined.get(key)){
                //System.out.println(key + " " + rules.get(key).size());

            }
            //System.out.println(defined.keySet().size() + " " + txtRules.keySet().size());
        }
        ArrayList<String> all = new ArrayList<>();
        for(int key : rules.keySet()){
            all.addAll(rules.get(key));
        }
        Collections.sort(all);
        int numValid = 0;
        while((line = in.readLine()) != null){
            if(Collections.binarySearch(all, line) >= 0){
                numValid++;
            }
        }
        System.out.println(numValid);

        in.close();
    }

}
