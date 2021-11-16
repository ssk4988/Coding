import java.io.*;
import java.util.*;

public class d19p2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d19p2.in"));
        Map<Integer, String> txtRules = new HashMap<>();
        String line;
        int aind = -1;
        int bind = -1;
        while ((line = in.readLine()) != null && line.length() > 0) {
            int ruleNum = Integer.parseInt(line.split(": ")[0]);
            txtRules.put(ruleNum, line.split(": ")[1].replace("\"", ""));
            if (txtRules.get(ruleNum).equals("a")) {
                aind = ruleNum;
            }
            if (txtRules.get(ruleNum).equals("b")) {
                bind = ruleNum;
            }
        }
        Map<Integer, Boolean> defined = new HashMap<>();
        Map<Integer, ArrayList<String>> rules = new HashMap<>();
        for (int key : txtRules.keySet()) {
            rules.put(key, new ArrayList<>());
            defined.put(key, false);
        }
        defined.put(aind, true);
        defined.put(bind, true);
        rules.get(aind).add("a");
        rules.get(bind).add("b");
        for (int key : txtRules.keySet()) {
            solve(txtRules, defined, rules, key);
        }
        for (int key : defined.keySet()) {
            if (defined.get(key) && (key == 8 || key == 11 || key == 31 || key == 42)) {
                System.out.println(key + " " + rules.get(key).size());
            }
            Collections.sort(rules.get(key));
        }
        System.out.println(defined.keySet().size() + " " + txtRules.keySet().size());
        int numValid = 0;
        while ((line = in.readLine()) != null) {
            int c42 = 0;
            int c31 = 0;
            boolean in42 = true;
            while (8 * (c42 + c31) < line.length()) {
                String substr = line.substring(8 * (c42 + c31), 8 * (c42 + c31 + 1));
                if (in42) {
                    if (Collections.binarySearch(rules.get(42), substr) >= 0) {
                        c42++;
                    } else {
                        in42 = false;
                    }
                }
                if (!in42) {
                    if (Collections.binarySearch(rules.get(31), substr) >= 0) {
                        c31++;
                    } else {
                        break;
                    }
                }
            }
            int use8 = c42 - c31;
            if (c31 > 0 && use8 > 0 && c42 > 0) {
                numValid++;
                // System.out.println(c42 + " " + c31 + " " + use8);
            }
        }
        System.out.println(numValid);

        in.close();
    }

    public static void solve(Map<Integer, String> txtRules, Map<Integer, Boolean> defined,
            Map<Integer, ArrayList<String>> rules, int key) {
        if (defined.get(key)) {
            return;
        }
        String pipe = " | ";
        String rule = txtRules.get(key);
        for (String s : rule.replace(pipe, " ").split(" ")) {
            if (!defined.get(Integer.parseInt(s))) {
                solve(txtRules, defined, rules, Integer.parseInt(s));
            }
        }
        ArrayList<String> subrules = new ArrayList<>();
        if (rule.contains(pipe)) {
            int splitInd = rule.indexOf(pipe);
            subrules.add(rule.substring(0, splitInd));
            subrules.add(rule.substring(splitInd + pipe.length()));
            // System.out.println(arr);
        } else {
            subrules.add(rule);
        }
        for (String subrule : subrules) {
            String[] components = subrule.split(" ");
            int[] componentRules = new int[components.length];
            for (int i = 0; i < components.length; i++) {
                componentRules[i] = Integer.parseInt(components[i]);
            }
            ArrayList<String> candidates = new ArrayList<>();
            candidates.add("");
            for (int i = 0; i < componentRules.length; i++) {
                ArrayList<String> newCandidates = new ArrayList<>();
                for (String s : candidates) {
                    for (String l : rules.get(componentRules[i])) {
                        newCandidates.add(s + l);
                    }
                }
                candidates = newCandidates;
            }
            rules.get(key).addAll(candidates);
            defined.put(key, true);
        }
    }
}