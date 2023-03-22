// Asir Alam
// Solution to UCF HSPT 2023 Problem: Princess Plum Chiffon

/*
 * Solution Idea
 *
 * Convert the given n-node graph to a 2n-node graph.
 *
 * For some kingdom i (0 <= i < n), 
 * - let node (2 * i) represent Earl being at kingdom i and still possessing 
 * the lucky star. 
 * - let (2 * i + 1) represent Earl being at kingdom i and no longer possessing
 * the lucky star (because it has already been used).
 *
 * We can use Dijkstra's algorithm on this slightly adjusted graph to compute 
 * the shortest travel times to each kingdom.
 */

import java.util.*;

public class princess1 {

  static class Node implements Comparable<Node> {
    int kingdom;
    boolean usedStar;
    boolean visited = false;
    long d = inf;
    ArrayList<Node> neighbors = new ArrayList<>();
    ArrayList<Long> distances = new ArrayList<>();

    public Node(int v) {
      this.kingdom = v / 2;
      this.usedStar = v % 2 == 1;
    }

    // PriorityQueue is sorted by lower distance first
    @Override
    public int compareTo(princess1.Node o) {
        return Long.compare(d, o.d);
    }
  }

  // Longest path could be approx. num_roads * max_weight = 1e5 * 1e9 = 1e14.
  // So we use a value larger than that as infinity.
  static final long inf = 1_000_000_000_000_000_000L;

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();

    // Store the graph as an adjacency list
    Node[] nodes = new Node[2 * n];
    for (int i = 0; i < nodes.length; i++) {
      nodes[i] = new Node(i);
    }
    // Initialize empty ArrayLists
    for (int i = 0; i < n; i++){
      int to = n - 1 - i;
      nodes[2 * i].neighbors.add(nodes[2 * to + 1]);
      nodes[2 * i].distances.add(0L);
    }

    for (int i = 0; i < m; i++) {
      // Convert to 0-based indexing
      int u = sc.nextInt() - 1;
      int v = sc.nextInt() - 1;
      long w = sc.nextInt();

      nodes[2 * u].neighbors.add(nodes[2 * v]);
      nodes[2 * u].distances.add(w);
      nodes[2 * v].neighbors.add(nodes[2 * u]);
      nodes[2 * v].distances.add(w);
      nodes[2 * u + 1].neighbors.add(nodes[2 * v + 1]);
      nodes[2 * u + 1].distances.add(w);
      nodes[2 * v + 1].neighbors.add(nodes[2 * u + 1]);
      nodes[2 * v + 1].distances.add(w);
      // Bidirectional, weighted edges
    }
    // Arrays.fill(dist, inf);
    PriorityQueue<Node> pq = new PriorityQueue<Node>();
    nodes[0].d = 0;
    pq.add(nodes[0]);

    // Dijkstra's Shortest Path Algorithm
    while (pq.size() > 0) {
      Node cur = pq.poll();
      // int kingdom = cur.v / 2;
      // int star = cur.v % 2;
      if(cur.visited) continue;
      cur.visited = true;

      // Add/update adjacent nodes if we can get a better distance.
      for (int i = 0; i < cur.neighbors.size(); i++){
        Node nex = cur.neighbors.get(i);
        long dist = cur.distances.get(i);
        if(nex.d > cur.d + dist){
          nex.d = cur.d + dist;
          pq.add(nex);
        }
      }
    }

    for (int i = 1; i < n; i++) {
      // The final answer will be the minimum of the two possibilities:
      // - Earl used the star
      // - Earl did not use the star
      long d = Math.min(nodes[2 * i].d, nodes[2 * i + 1].d);

      // Earl is unable to reach this kingdom
      if (d == inf)
        d = -1L;

      System.out.print(d + " ");
    }
  }
}
