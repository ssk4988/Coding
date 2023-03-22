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

public class princess
{
  static class Edge
  {
    int to, w;

    public Edge(int to, int w)
    {
      this.to = to;
      this.w = w;
    }
  }

  static class Node implements Comparable<Node>
  {
    int v;
    long d;

    public Node(int v, long d)
    {
      this.v = v;
      this.d = d;
    }

    // PriorityQueue is sorted by lower distance first
    public int compareTo(Node node)
    {
      return Long.compare(d, node.d);
    }
  }

  // Longest path could be approx. num_roads * max_weight = 1e5 * 1e9 = 1e14.
  // So we use a value larger than that as infinity.
  static final long inf = 1_000_000_000_000_000_000L;

  @SuppressWarnings("unchecked")
  public static void main(String[] args)
  {
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    int m = sc.nextInt();

    // Store the graph as an adjacency list
    ArrayList<Edge>[] adj = new ArrayList[n];

    // Initialize empty ArrayLists
    for (int i = 0; i < n; i++)
      adj[i] = new ArrayList<>();

    for (int i = 0; i < m; i++)
    {
      // Convert to 0-based indexing
      int u = sc.nextInt() - 1;
      int v = sc.nextInt() - 1;
      int w = sc.nextInt();

      // Bidirectional, weighted edges
      adj[u].add(new Edge(v, w));
      adj[v].add(new Edge(u, w));
    }

    long[] dist = new long[2 * n];
    Arrays.fill(dist, inf);

    PriorityQueue<Node> pq = new PriorityQueue<Node>();
    pq.add(new Node(0, 0));
    dist[0] = 0;

    // Dijkstra's Shortest Path Algorithm
    while (pq.size() > 0)
    {
      Node cur = pq.poll();
      int kingdom = cur.v / 2;
      int star = cur.v % 2;

      if (cur.d > dist[cur.v])
        continue;

      // Add/update adjacent nodes if we can get a better distance.
      for (Edge e : adj[kingdom])
      {
        int to = e.to * 2 + star;

        if (cur.d + e.w < dist[to])
        {
          dist[to] = cur.d + e.w;
          pq.add(new Node(to, cur.d + e.w));
        }
      }

      // Can use lucky star
      if (star == 0)
      {
        int to = n - kingdom - 1;

        // Convert to the (2 * n) nodes representation and add 1 to indicate
        // that Earl has used the lucky star.
        to = 2 * to + 1;

        if (cur.d < dist[to])
        {
          dist[to] = cur.d;
          pq.add(new Node(to, cur.d));
        }
      }
    }

    for (int i = 1; i < n; i++)
    {
      // The final answer will be the minimum of the two possibilities:
      // - Earl used the star
      // - Earl did not use the star
      long d = Math.min(dist[2 * i], dist[2 * i + 1]);

      // Earl is unable to reach this kingdom
      if (d == inf)
        d = -1L;

      System.out.print(d + " ");
    }
  }
}
