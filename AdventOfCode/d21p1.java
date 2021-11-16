import java.io.*;
import java.util.*;

public class d21p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d21p1.in"));
        int numIngredients = 0;
        int numAllergens = 0;
        Map<String, Integer> ingredientid = new HashMap<>();
        Map<String, Integer> allergenid = new HashMap<>();
        ArrayList<ArrayList<Integer>> ingredients = new ArrayList<>();
        ArrayList<ArrayList<Integer>> allergens = new ArrayList<>();
        ArrayList<Integer> seen = new ArrayList<>();

        String line;
        int numFoods = 0;
        while ((line = in.readLine()) != null) {
            ingredients.add(new ArrayList<>());
            allergens.add(new ArrayList<>());
            String[] inglist = line.substring(0, line.indexOf("(")).split(" ");
            for(String s : inglist){
                if(!ingredientid.containsKey(s)){
                    ingredientid.put(s, numIngredients);
                    seen.add(0);
                    //System.out.println(s + " " + numIngredients);
                    numIngredients++;
                    
                }
                seen.set(ingredientid.get(s), seen.get(ingredientid.get(s)) + 1);
                ingredients.get(numFoods).add(ingredientid.get(s));
            }
            String[] alllist = line.substring(line.indexOf("(contains ") + "(contains ".length(), line.length() - 1).split(", ");
            for(String s : alllist){
                if(!allergenid.containsKey(s)){
                    allergenid.put(s, numAllergens);
                    //System.out.println(s + " " + numAllergens);
                    numAllergens++;
                }
                allergens.get(numFoods).add(allergenid.get(s));
            }
            numFoods++;
        }
        ArrayList<Integer>[] possibleAllergens = new ArrayList[numIngredients];
        for(int i = 0; i < numIngredients; i++){
            possibleAllergens[i] = new ArrayList<>();
        }
        for(int i = 0; i < numAllergens; i++){
            ArrayList<Integer> possible = new ArrayList<>();
            for(int j = 0; j < numFoods; j++){
                if(allergens.get(j).contains(i)){
                    if(possible.size() == 0){
                        possible.addAll(ingredients.get(j));
                    }
                    else{
                        possible.retainAll(ingredients.get(j));
                    }
                }
            }
            for(int j : possible){
                possibleAllergens[j].add(i);
            }
        }
        int sum = 0;
        for(int i = 0; i < possibleAllergens.length; i++){
            if(possibleAllergens[i].size() == 0){
                sum += seen.get(i);
            }
        }
        System.out.println(sum);
        //System.out.println(Arrays.toString(possibleAllergens));
        //System.out.println(ingredientid);

        in.close();
    }

}
