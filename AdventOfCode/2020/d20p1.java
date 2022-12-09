import java.io.*;
import java.util.*;

public class d20p1 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("d20p1.in"));
        String line = " ";
        int dim = 10;
        ArrayList<Tile> tiles = new ArrayList<>();
        while(line != null){
            line = in.readLine();
            int id = Integer.parseInt(line.split(":")[0].split(" ")[1]);
            char[][] arr = new char[dim][dim];
            int i = 0;
            while((line = in.readLine()) != null && line.length() > 0){
                arr[i] = line.toCharArray();
                i++;
            }
            tiles.add(new Tile(arr, id));
        }
        for(int i = 0; i < tiles.size(); i++){
            for(int j = 0; j < i; j++){
                tiles.get(i).hasMatch(tiles.get(j));
            }
        }
        long prod = 1;
        for(int i = 0; i < tiles.size(); i++){
            if(tiles.get(i).numMatches == 2){
                System.out.println(tiles.get(i).id);
                prod *= tiles.get(i).id;
            }
            //System.out.println(tiles.get(i).id);
            //System.out.println(Arrays.toString(tiles.get(i).matchArray));
        }
        System.out.println(prod);

        in.close();
    }
    public static class Tile{
        boolean[][] edges;
        int[] matchArray = new int[4];
        int dim;
        int id;
        int numMatches = 0;
        public Tile(char[][] data, int id){
            this.id = id;
            this.dim = data.length;
            this.edges = new boolean[4][this.dim];
            for(int i = 0; i < data.length; i++){
                edges[0][i] = data[0][i] == '#';
                edges[1][i] = data[i][this.dim - 1] == '#';
                edges[2][i] = data[this.dim - 1][i] == '#';
                edges[3][i] = data[i][0] == '#';
            }
        }
        public boolean hasMatch(Tile t){
            boolean match = false;
            for(int i = 0; i < this.edges.length; i++){
                for(int j = 0; j < t.edges.length; j++){
                    boolean matches = true;
                    for(int k= 0; k < this.dim; k++){
                        if(this.edges[i][k] != t.edges[j][k]){
                            matches = false;
                        }
                    }
                    boolean matches2 = true;
                    for(int k= 0; k < this.dim; k++){
                        if(this.edges[i][k] != t.edges[j][this.dim - 1 - k]){
                            matches2 = false;
                        }
                    }
                    
                    if(matches || matches2){
                        this.numMatches++;
                        t.numMatches++;
                        this.matchArray[i] = t.id;
                        t.matchArray[j] = this.id;
                        match = true;
                    }
                }
            }
            return match;
        }
    }
}
