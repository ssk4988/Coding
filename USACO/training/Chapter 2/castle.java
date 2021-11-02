/*
ID: ssk49881
LANG: JAVA
TASK: castle
*/

import java.io.*;
import java.util.*;

public class castle {
    public static ArrayList<Integer>[][] neighbors;
    public static int[][] rooms;
    public static int width;
    public static int height;
    public static Stack<Integer> stack = new Stack<>();
    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new File("castle.in"));
        PrintWriter out = new PrintWriter(new File("castle.out"));
        String phrase = in.nextLine();
        width = Integer.parseInt(phrase.split(" ")[0]);
        height = Integer.parseInt(phrase.split(" ")[1]);
        neighbors = new ArrayList[height][width];
        rooms = new int[height][width];
        HashMap<Integer, Integer> roomsizes = new HashMap<>();
        

        for (int i = 0; i < height; i++) {
            phrase = in.nextLine();
            for (int j = 0; j < phrase.split(" ").length; j++) {
                neighbors[i][j] = getNeighbors(i * width + j, Integer.parseInt(phrase.split(" ")[j]));
                // System.out.print(neighbors[i][j].size() + " ");
            }
            // System.out.println();
        }
        int numrooms = 0;
        for (int i = 0; i < rooms.length; i++) {
            for (int j = 0; j < rooms[0].length; j++) {
                if (rooms[i][j] == 0) {
                    numrooms++;
                    //rooms[i][j] = -2;
                    //flood_fill(numrooms);
                    dffill(numrooms, i, j);
                }
            }
        }
        out.println(numrooms);

        for (int i = 0; i < rooms.length; i++) {
            for (int j = 0; j < rooms[0].length; j++) {
                if(roomsizes.get(rooms[i][j]) != null){
                    roomsizes.put(rooms[i][j], roomsizes.get(rooms[i][j]) + 1);
                }
                else{
                    roomsizes.put(rooms[i][j], 1);
                }
            }
        }

        int maxSize = 0;
        for (int roomsize : roomsizes.values()) {
            if (maxSize < roomsize) {
                maxSize = roomsize;
            }
            System.out.println(roomsize);
        }
        out.println(maxSize);

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                System.out.print(rooms[i][j] + " ");
            }
            System.out.println();
        }

        maxSize = 0;
        int size;
        String maxConditions = "";
        for (int j = 0; j < width; j++) {
            for (int i = height - 1; i >= 0; i--) {
                // north
                if (i != 0 && !neighbors[i][j].contains((i - 1) * width + j)) {
                    if (rooms[i][j] != rooms[i - 1][j]) {
                        size = roomsizes.get(rooms[i][j]) + roomsizes.get(rooms[i - 1][j]);
                        if (size > maxSize) {
                            maxSize = size;
                            maxConditions = Integer.toString(i + 1) + " " + Integer.toString(j + 1) + " N";
                        }
                    }
                }

                // east
                if (j != width - 1 && !neighbors[i][j].contains(i * width + j + 1)) {
                    if (rooms[i][j] != rooms[i][j + 1]) {
                        size = roomsizes.get(rooms[i][j]) + roomsizes.get(rooms[i][j + 1]);
                        if (size > maxSize) {
                            maxSize = size;
                            maxConditions = Integer.toString(i + 1) + " " + Integer.toString(j + 1) + " E";
                        }
                    }
                }
            }
        }
        out.println(maxSize);
        out.println(maxConditions);

        in.close();
        out.close();
    }

    public static void dffill(int roomnumber, int i, int j){
        rooms[i][j] = roomnumber;
        for (int index : neighbors[i][j]) {
            if (rooms[index / width][index % width] == 0) {
                dffill(roomnumber, index / width, index % width);
            }
        }
    }

    public static void flood_fill(int roomnumber) {
        int numvisited = 0;
        do {
            numvisited = 0;
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (rooms[i][j] == -2) {
                        numvisited++;
                        rooms[i][j] = roomnumber;
                        for (int index : neighbors[i][j]) {
                            if (rooms[index / width][index % width] == 0) {
                                rooms[index / width][index % width] = -2;
                            }
                        }
                    }
                }
            }
        } while (numvisited == 0);
    }

    public static ArrayList<Integer> getNeighbors(int index, int neighborvalue) {
        ArrayList<Integer> n = new ArrayList<>();
        int i = index / width;
        int j = index % width;
        int copyneighborvalue = neighborvalue;
        if (copyneighborvalue >= 8) {
            copyneighborvalue -= 8;
        } else {
            n.add((i + 1) * width + j);
        }
        if (copyneighborvalue >= 4) {
            copyneighborvalue -= 4;
        } else {
            n.add(i * width + j + 1);
        }
        if (copyneighborvalue >= 2) {
            copyneighborvalue -= 2;
        } else {
            n.add((i - 1) * width + j);
        }
        if (copyneighborvalue >= 1) {
            copyneighborvalue -= 1;
        } else {
            n.add(i * width + j - 1);
        }

        return n;
    }
}