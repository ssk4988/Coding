/*
ID: ssk49881
LANG: JAVA
TASK: multimoo
*/

import java.io.*;
import java.util.*;
public class multimoo {
    public static int dim;
    public static int numComponents = 0;
    public static int[][] state;
    public static int[][] component;
    public static ArrayList<Integer> size = new ArrayList<>();
    public static ArrayList<Integer> componentID = new ArrayList<>();
    public static ArrayList<Integer> ids = new ArrayList<>();
    public static ArrayList<Integer>[] neighbor;
    public static int max = 0;
    public static boolean[] visited;
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("2.in"));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("multimoo.out")));
        dim = Integer.parseInt(in.readLine());
        state = new int[dim][dim];
        component = new int[dim][dim];
        for(int[] i : component){
            Arrays.fill(i, -2);
        }
        for(int i = 0; i < dim; i++){
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            for(int j = 0; j < dim; j++){
                int next = Integer.parseInt(tokenizer.nextToken());
                if(!ids.contains(next)){
                    ids.add(next);
                }
                state[i][j] = ids.indexOf(next);
            }
        }
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                if(component[i][j] == -2){
                    flood_fill(i * dim + j);
                    numComponents++;
                }
            }
        }
        neighbor = new ArrayList[numComponents];
        for(int i = 0; i < neighbor.length; i++){
            neighbor[i] = new ArrayList<>();
        }
        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                int comp = component[i][j];
                if(i > 0){
                    int comp2 = component[i - 1][j];
                    if(comp != comp2 && !neighbor[comp].contains(comp2)){
                        neighbor[comp].add(comp2);
                        neighbor[comp2].add(comp);
                    }
                }
                if(j > 0){
                    int comp2 = component[i][j - 1];
                    if(comp != comp2 && !neighbor[comp].contains(comp2)){
                        neighbor[comp].add(comp2);
                        neighbor[comp2].add(comp);
                    }
                }
                if(i < dim - 1){
                    int comp2 = component[i + 1][j];
                    if(comp != comp2 && !neighbor[comp].contains(comp2)){
                        neighbor[comp].add(comp2);
                        neighbor[comp2].add(comp);
                    }
                }
                if(j < dim - 1){
                    int comp2 = component[i][j + 1];
                    if(comp != comp2 && !neighbor[comp].contains(comp2)){
                        neighbor[comp].add(comp2);
                        neighbor[comp2].add(comp);
                    }
                }
            }
        }
        for(int i = 0; i < size.size(); i++){
            if(size.get(i) > max){
                max = size.get(i);
            }
        }
        System.out.println(max);
        max = 0;
        visited = new boolean[numComponents];
        for(int i = 0; i < ids.size(); i++){
            for(int j = 0; j < i; j++){
                visited = new boolean[numComponents];
                for(int k = 0; k < numComponents; k++){
                    if((componentID.get(k) == i || componentID.get(k) == j) && !visited[k]){
                        dfs(k, i, j);
                    }
                }
            }
        }
        System.out.println(max);

        for(int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                System.out.print(state[i][j] + " ");
            }
            System.out.println();
        }
        System.out.println(size);
        System.out.println(componentID);
        


        in.close();
        //out.close();
    }
    public static void dfs(int first, int i1, int i2){
        ArrayList<Integer> seen = new ArrayList<>();
        ArrayList<Integer> frontier = new ArrayList<>();
        frontier.add(first);
        while(frontier.size() != 0){
            int index = frontier.remove(0);
            seen.add(index);
            visited[index] = true;
            for(int i : neighbor[index]){
                if((componentID.get(i) == i1 || componentID.get(i) == i2) && !visited[i]){
                    frontier.add(i);
                }
            }
        }
        int sum = 0;
        for(int i : seen){
            sum += size.get(i);
        }
        if(sum > max){
            max = sum;
            System.out.println(i1 + " " + i2);
        }
    }

    public static void flood_fill(int index) {
        ArrayList<Integer> seen = new ArrayList<>();
        ArrayList<Integer> frontier = new ArrayList<>();
        frontier.add(index);
        while (frontier.size() != 0) {
            int next = frontier.remove(0);
            seen.add(next);
            int i = next / dim;
            int j = next % dim;
            if (i > 0) {
                int index2 = (i - 1) * dim + j;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i - 1][j] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (j > 0) {
                int index2 = i * dim + j - 1;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i][j - 1] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (i < dim - 1) {
                int index2 = (i + 1) * dim + j;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i + 1][j] == state[i][j]) {
                    frontier.add(index2);
                }
            }
            if (j < dim - 1) {
                int index2 = i * dim + j + 1;
                if (!seen.contains(index2) && !frontier.contains(index2) && state[i][j + 1] == state[i][j]) {
                    frontier.add(index2);
                }
            }
        }
        for (int in : seen) {
            int i = in / dim;
            int j = in % dim;
            component[i][j] = numComponents;
            
        }
        size.add(seen.size());
        componentID.add(state[index / dim][index % dim]);
    }
}