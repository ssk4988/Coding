/*
ID: ssk49881
LANG: JAVA
TASK: wormsort
*/

import java.io.*;
import java.util.*;

public class wormsort {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("wormsort.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int numCows = Integer.parseInt(tokenizer.nextToken());
        int numRoutes = Integer.parseInt(tokenizer.nextToken());
        ArrayList<Route> routes = new ArrayList<>();
        tokenizer = new StringTokenizer(in.readLine());
        int[] location = new int[numCows];
        int[] destination = new int[numCows];
        Cow[] cows = new Cow[numCows];
        for (int i = 0; i < numCows; i++) {
            int j = Integer.parseInt(tokenizer.nextToken()) - 1;
            destination[j] = i;
            location[i] = j;
            cows[i] = new Cow(i, j);
        }
        for (int i = 0; i < numRoutes; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int first = Integer.parseInt(tokenizer.nextToken()) - 1;
            int second = Integer.parseInt(tokenizer.nextToken()) - 1;
            int weight = Integer.parseInt(tokenizer.nextToken());
            routes.add(new Route(first, second, weight));
        }
        Collections.sort(routes, new comp());
        int low = 0;
        int high = routes.get(0).weight + 1;
        int mid;
        int numComponents = 0;
        while (low < high) {
            mid = (low + high + 1) / 2;
            for (Cow cow : cows) {
                cow.component = -1;
                cow.neighbors = new ArrayList<>();
            }
            for (int i = 0; i < numRoutes; i++) {
                if (routes.get(i).weight < mid) {
                    break;
                }
                Route route = routes.get(i);
                cows[route.first].neighbors.add(route.second);
                cows[route.second].neighbors.add(route.first);
            }
            boolean condition = true;
            ArrayList<Integer> queue = new ArrayList<>();
            for (int i = 0; i < numCows; i++) {
                if (cows[i].component == -1) {
                    queue.add(i);
                    while (!queue.isEmpty()) {
                        int index = queue.remove(queue.size() - 1);
                        cows[index].component = numComponents;
                        for (int neighbor : cows[index].neighbors) {
                            if (cows[neighbor].component == -1) {
                                queue.add(neighbor);
                            }
                        }
                    }
                    numComponents++;
                }
            }
            for (int i = 0; i < numCows; i++) {
                if (cows[i].component != cows[cows[i].destination].component) {
                    condition = false;
                    break;
                }
            }
            if (condition) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        int answer = low;
        if (answer == routes.get(0).weight + 1) {
            answer = -1;
        }
        out.println(answer);

        in.close();
        out.close();
    }

    public static class Cow {
        int location;
        int destination;
        int component;
        ArrayList<Integer> neighbors = new ArrayList<>();

        public Cow(int location, int destination) {
            this.location = location;
            this.destination = destination;
            component = -1;
        }
    }

    public static class comp implements Comparator<Route> {
        @Override
        public int compare(wormsort.Route o1, wormsort.Route o2) {
            return o2.weight - o1.weight;
        }
    }

    public static class Route {
        int first;
        int second;
        int weight;

        public Route(int first, int second, int weight) {
            this.first = first;
            this.second = second;
            this.weight = weight;
        }

    }
}