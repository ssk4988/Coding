import java.io.*;
import java.util.*;

public class e {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int nhouses = Integer.parseInt(tokenizer.nextToken());
            int nroads = Integer.parseInt(tokenizer.nextToken());
            int nfriends = Integer.parseInt(tokenizer.nextToken())+1;
            friend[] friends = new friend[nfriends];
            house[] houses = new house[nhouses];
            for (int i = 0; i < nhouses; i++) {
                houses[i] = new house(i);
            }
            tokenizer = new StringTokenizer(in.readLine());
            friends[0] = new friend(0, houses[0], nfriends);
            for (int i = 0; i < nfriends-1; i++) {
                int k = Integer.parseInt(tokenizer.nextToken()) - 1;
                friends[i+1] = new friend(i+1, houses[k], nfriends);
            }
            
            for (int i = 0; i < nroads; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                house h1 = houses[Integer.parseInt(tokenizer.nextToken()) - 1];
                house h2 = houses[Integer.parseInt(tokenizer.nextToken()) - 1];
                long weight = Long.parseLong(tokenizer.nextToken());
                road e = new road(h1, h2, weight);
                h1.edges.add(e);
                h2.edges.add(e);
            }
            for (int i = 0; i < nfriends; i++) {
                for (int j = 0; j < nhouses; j++) {
                    houses[j].dist = Long.MAX_VALUE;
                    houses[j].visited = false;
                }
                friends[i].h.dist = 0;
                PriorityQueue<house> q = new PriorityQueue<>();
                q.add(friends[i].h);
                int numVisited = 0;
                while (numVisited < nhouses) {
                    house h = q.poll();
                    if (h.visited)
                        continue;
                    h.visited = true;
                    numVisited++;
                    for (int k = 0; k < h.edges.size(); k++) {
                        house other = h.edges.get(k).other(h);
                        if (!other.visited) {
                            if (other.dist > h.dist + h.edges.get(k).weight) {
                                other.dist = h.dist + h.edges.get(k).weight;
                            }
                            q.add(other);
                        }
                    }
                }
                for (int j = 0; j < nfriends; j++) {
                    friends[i].dist[j] = friends[j].h.dist;
                }
                //System.out.println(Arrays.toString(friends[i].dist));
            }
            long[][] cost = new long[1 << nfriends][nfriends];
            for (int i = 0; i < cost.length; i++) {
                Arrays.fill(cost[i], Long.MAX_VALUE);
            }

            long min = Long.MAX_VALUE;
            for (int i = 1; i < nfriends; i++) {
                calc((1 << nfriends) - 1, i, nfriends, cost, friends);
                min = Math.min(min, friends[0].dist[i] + cost[(1<<nfriends)-1][i]);
            }
            System.out.println(min);
        }

        in.close();
        out.close();
    }

    public static void calc(int set, int second, int size, long[][] cost, friend[] friends) {
        if (cost[set][second] != Long.MAX_VALUE)
            return;
        if (size == 2) {
            cost[set][second] = friends[0].dist[second];
            return;
        }
        int sbit = 1 << second;
        int nset = set ^ sbit;
        int bit = 1;
        long min = Long.MAX_VALUE;
        for (int i = 0; i < friends.length; i++) {
            if (i !=0 && i!= second && (set | bit) == set) {
                calc(nset, i, size - 1, cost, friends);
                min = Math.min(min, cost[nset][i] + friends[second].dist[i]);
            }
            bit <<= 1;
        }
        cost[set][second] = min;
    }

    public static class friend {
        int id;
        house h = null;
        long[] dist;

        public friend(int id, house h, int nfriends) {
            dist = new long[nfriends];
            this.h = h;
            this.id = id;
            h.isFriend = true;
        }
    }
    public static class comp implements Comparator<house>{
        @Override
        public int compare(e.house o1, e.house o2) {
            if(o1.dist == o2.dist) return 0;
            if(o1.dist < o2.dist) return -1;
            return 1;
        }
    }
    public static class house implements Comparable<house> {
        int id;
        ArrayList<road> edges = new ArrayList<>();
        boolean isFriend = false;
        friend f = null;
        boolean visited = false;
        long dist = 0;

        public house(int id) {
            this.id = id;
        }

        @Override
        public int compareTo(e.house o) {
            if (this.dist == o.dist)
                return 0;
            if (this.dist < o.dist)
                return -1;
            return 1;
        }
    }

    public static class road {
        house h1;
        house h2;
        long weight;

        public road(house h1, house h2, long weight) {
            this.h1 = h1;
            this.h2 = h2;
            this.weight = weight;
        }

        public house other(house h) {
            if (h == h1)
                return h2;
            return h1;
        }
    }
}