import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
        Map<Integer, String> rulegex = new HashMap<>();
        for (int key : txtRules.keySet()) {
            rulegex.put(key, "");
            defined.put(key, false);
        }
        defined.put(aind, true);
        defined.put(bind, true);
        rulegex.put(aind, "a");
        rulegex.put(bind, "b");
        for (int key : txtRules.keySet()) {
            solve(txtRules, defined, key, rulegex);
        }
        for (int key : defined.keySet()) {
            if (defined.get(key) && (key == 8 || key == 11 || key == 31 || key == 42)) {
                //System.out.println(key + " " + rulegex.get(key));
            }
        }
        String regStr31 = rulegex.get(31);
        String regStr42 = rulegex.get(42);

        String regStr = "^" + regStr42 + "+" + regStr31 + "+$";
        System.out.println(regStr);
        System.out.println(defined.keySet().size() + " " + txtRules.keySet().size());
        int numValid = 0;
        Pattern p42 = Pattern.compile(regStr42);
        Pattern p31 = Pattern.compile(regStr31);
        while ((line = in.readLine()) != null) {
            long c42 = p42.matcher(line).results().count();
            long c31 = p31.matcher(line).results().count();
            if (Pattern.matches(regStr, line)) {
                numValid++;
            }

        }
        System.out.println(numValid);

        in.close();
    }

    public static void solve(Map<Integer, String> txtRules, Map<Integer, Boolean> defined, int key,
            Map<Integer, String> rulegex) {
        if (defined.get(key)) {
            return;
        }
        String pipe = " | ";
        String rule = txtRules.get(key);
        for (String s : rule.replace(pipe, " ").split(" ")) {
            if (!defined.get(Integer.parseInt(s))) {
                solve(txtRules, defined, Integer.parseInt(s), rulegex);
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
        String newRegex = "(";
        for (int j = 0; j < subrules.size(); j++) {
            String subrule = subrules.get(j);
            String[] components = subrule.split(" ");
            if (subrules.size() > 1 && components.length > 1)
                newRegex += "(";
            int[] componentRules = new int[components.length];
            for (int i = 0; i < components.length; i++) {
                componentRules[i] = Integer.parseInt(components[i]);
            }
            for (int i = 0; i < componentRules.length; i++) {
                newRegex += rulegex.get(componentRules[i]);
            }
            if (subrules.size() > 1 && components.length > 1)
                newRegex += ")";
            if (subrules.size() > 1 && j < subrules.size() - 1)
                newRegex += "|";
            defined.put(key, true);
        }
        newRegex += ")";
        rulegex.put(key, newRegex);
    }
}