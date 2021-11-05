/*
ID: ssk49881
LANG: JAVA
TASK: prob2
*/

import java.io.*;
import java.util.*;

public class prob2 {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numTournaments = Integer.parseInt(in.readLine());
        for (int count = 0; count < numTournaments; count++) {
            boolean possible = true;
            int numTeams = Integer.parseInt(in.readLine());
            int depth = (int) (Math.log(numTeams) / Math.log(2)) + 1;
            int[] places = new int[numTeams * 2 - 1];
            Team[] teams = new Team[numTeams];
            Arrays.fill(places, -1);
            for (int i = 0; i < numTeams; i++) {
                StringTokenizer tokenizer = new StringTokenizer(in.readLine());
                int wins = Integer.parseInt(tokenizer.nextToken());
                int losses = Integer.parseInt(tokenizer.nextToken());
                teams[i] = new Team(i, wins, losses, depth);
                int index = i;
                int inc1 = numTeams;
                int inc2 = i;
                for (int d = 0; d < Math.min(depth, teams[i].matchwins + 1) && possible; d++) {
                    if (places[index] == -1) {
                        // System.out.printf("Team %d index %d%n", i, index);
                        places[index] = i;
                        index += inc1;
                        inc1 /= 2;
                        index -= inc2;
                        inc2 /= 2;
                        index += inc2;
                    } else {
                        // System.out.printf("Team %d index %d impossible %n", i, index);
                        possible = false;
                    }
                }
            }
            // System.out.println(Arrays.toString(places));
            for (int i = 0; i < numTeams; i++) {
                if (places[i] == -1)
                    possible = false;
            }
            for (int i = 0; i < places.length - 1 && possible; i += 2) {
                Team team1 = teams[places[i]];
                Team team2 = teams[places[i + 1]];
                Team winner = team1.matchwins == 0 ? team2 : team1;
                Team loser = team1.matchwins == 0 ? team1 : team2;
                winner.matchwins--;
                loser.matchlosses--;
                winner.wins -= 4;
                loser.losses -= 4;
                winner.losses -= loser.wins;
                loser.wins -= loser.wins;
            }
            for (int i = 0; i < teams.length && possible; i++) {
                if (teams[i].wins != 0 || teams[i].losses != 0) {
                    possible = false;
                }
            }
            System.out.println("Tournament #" + (count + 1) + ": " + (possible ? "Possible" : "Impossible"));
            // System.out.println(numTeams + " depth " + depth);
        }
        in.close();
        out.close();
    }

    public static class Team {
        int index;
        int wins;
        int losses;
        int matchwins;
        int matchlosses;

        public Team(int index, int wins, int losses, int depth) {
            this.index = index;
            this.wins = wins;
            this.losses = losses;
            this.matchwins = wins / 4;
            this.matchlosses = this.matchwins == depth ? 0 : 1;
        }
    }
}