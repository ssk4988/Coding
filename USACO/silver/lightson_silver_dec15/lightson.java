/*
ID: ssk49881
LANG: JAVA
TASK: lightson
*/

import java.io.*;
import java.util.*;

public class lightson {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("lightson.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lightson.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int dim = Integer.parseInt(tokenizer.nextToken());
        int numConnect = Integer.parseInt(tokenizer.nextToken());
        Room[][] rooms = new Room[dim][dim];
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                rooms[i][j] = new Room(i, j);
            }
        }
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (i > 0) {
                    rooms[i][j].neighbors.add(rooms[i - 1][j]);
                }
                if (j > 0) {
                    rooms[i][j].neighbors.add(rooms[i][j - 1]);
                }
                if (i < dim - 1) {
                    rooms[i][j].neighbors.add(rooms[i + 1][j]);
                }
                if (j < dim - 1) {
                    rooms[i][j].neighbors.add(rooms[i][j + 1]);
                }
            }
        }
        for (int i = 0; i < numConnect; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int x1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int y1 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int x2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            int y2 = Integer.parseInt(tokenizer.nextToken()) - 1;
            rooms[x1][y1].switches.add(rooms[x2][y2]);
        }
        int maxOn = 0;
        int maxConnected = 0;
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                for (int i2 = 0; i2 < dim; i2++) {
                    for (int j2 = 0; j2 < dim; j2++) {
                        rooms[i2][j2].on = false;
                        rooms[i2][j2].connected = false;
                        rooms[i2][j2].prevConnected = 0;
                    }
                }
                // System.out.println("Start: " + i + " " + j);
                rooms[i][j].on = true;
                int numConnected = 0;
                int numOn = 1;
                ArrayList<Room> queue = new ArrayList<>();
                queue.add(rooms[i][j]);
                while (!queue.isEmpty()) {
                    Room room = queue.remove(0);
                    // System.out.println(room.x + " " + room.y);
                    boolean canConnect = false;
                    for (Room r : room.neighbors) {
                        if (r.connected) {
                            canConnect = true;
                            break;
                        }
                    }
                    if (canConnect || room == rooms[i][j]) {
                        room.connected = true;
                        numConnected++;
                        for (Room r : room.switches) {
                            if (!r.on) {
                                r.on = true;
                                numOn++;
                                queue.add(r);
                            }
                        }
                    } else {
                        if (numConnected == room.prevConnected) {
                            break;
                        } else {
                            room.prevConnected = numConnected;
                            queue.add(room);
                        }
                    }
                }
                // System.out.println((i + 1) + " " + (j + 1) + " " + numConnected);
                if (numConnected > maxConnected) {
                    maxConnected = numConnected;
                }
                if (numOn > maxOn) {
                    maxOn = numOn;
                }
            }
        }
        out.println(maxOn);

        in.close();
        out.close();
    }

    public static class Room {
        int x;
        int y;
        boolean on = false;
        boolean connected = false;
        int prevConnected = 0;
        ArrayList<Room> switches = new ArrayList<>();
        ArrayList<Room> neighbors = new ArrayList<>();

        public Room(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}