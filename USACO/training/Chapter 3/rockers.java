/*
ID: ssk49881
LANG: JAVA
TASK: rockers
*/

import java.io.*;
import java.util.*;

public class rockers {
    public static int numSongs;
    public static int maxTime;
    public static int numDisks;
    public static int[] songs;
    public static LinkedList<songCollection> list = new LinkedList<>();

    public static void main(String[] args) throws Exception {
        long start_time = System.currentTimeMillis();
        BufferedReader in = new BufferedReader(new FileReader("rockers.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rockers.out")));

        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        numSongs = Integer.parseInt(tokenizer.nextToken());
        maxTime = Integer.parseInt(tokenizer.nextToken());
        numDisks = Integer.parseInt(tokenizer.nextToken());
        songs = new int[numSongs];
        tokenizer = new StringTokenizer(in.readLine());
        for (int i = 0; i < numSongs; i++) {
            songs[i] = Integer.parseInt(tokenizer.nextToken());
        }
        int maxSongs = 0;
        int t = 0;
        for (int i = 0; i < numSongs; i++) {
            if (songs[i] > maxTime) {
                continue;
            }
            songCollection tmp = new songCollection(i, 1, 1);
            tmp.diskLeft = maxTime - songs[i];
            list.add(tmp);
        }
        while (!list.isEmpty()) {
            songCollection tmp = list.pollFirst();
            t++;
            // System.out.println(tmp.songIndices.toString());
            // System.out.println(tmp.disksUsed + " " + tmp.diskLeft);
            if (tmp.songsUsed > maxSongs) {
                maxSongs = tmp.songsUsed;
                System.out.println(maxSongs + " " + (System.currentTimeMillis() - start_time) + " " + t);
                t = 0;
            }
            if (tmp.lastSong >= numSongs - 1) {
                continue;
            }
            for (int i = tmp.lastSong + 1; i < numSongs; i++) {
                if (songs[i] > tmp.diskLeft && tmp.disksUsed >= numDisks) {
                    continue;
                }
                int diskLeft = tmp.diskLeft - songs[i];
                int disksUsed = tmp.disksUsed;
                if (diskLeft < 0) {
                    diskLeft = maxTime - songs[i];
                    disksUsed++;
                }
                songCollection newC = new songCollection(i, disksUsed, tmp.songsUsed + 1);
                newC.diskLeft = diskLeft;
                list.addFirst(newC);
            }
        }

        out.println(maxSongs);
        in.close();
        out.close();
    }

    public static class songCollection {
        public int songsUsed = 0;
        public int lastSong;
        public int disksUsed = 0;
        public int diskLeft = maxTime;

        public songCollection(int lastSong, int disksUsed, int songsUsed) {
            this.disksUsed = disksUsed;
            this.lastSong = lastSong;
            this.songsUsed = songsUsed;
        }
    }
}