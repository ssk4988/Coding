import java.io.*;
import java.util.*;

public class barns {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int numcases = Integer.parseInt(in.readLine());
        for (int casenum = 0; casenum < numcases; casenum++) {
            StringTokenizer tokenizer = new StringTokenizer(in.readLine());
            int numNodes = Integer.parseInt(tokenizer.nextToken());
            int numPaths = Integer.parseInt(tokenizer.nextToken());
            node[] nodes = new node[numNodes];
            for (int i = 0; i < numNodes; i++) {
                nodes[i] = new node(i);
            }
            for (int i = 0; i < numPaths; i++) {
                tokenizer = new StringTokenizer(in.readLine());
                int i1 = Integer.parseInt(tokenizer.nextToken()) - 1;
                int i2 = Integer.parseInt(tokenizer.nextToken()) - 1;
                nodes[i1].neighbors.add(nodes[i2]);
                nodes[i2].neighbors.add(nodes[i1]);
            }
            ArrayList<component> components = new ArrayList<>();
            for (int i = 0; i < numNodes; i++) {
                if (nodes[i].component != null)
                    continue;
                components.add(new component(components.size()));
                component c = components.get(components.size() - 1);
                LinkedList<node> q = new LinkedList<>();
                q.add(nodes[i]);
                while (!q.isEmpty()) {
                    node k = q.poll();
                    k.component = c;
                    c.content.add(k);
                    for (node n : k.neighbors) {
                        if (n.component == null) {
                            q.add(n);
                        }
                    }
                }
            }
            for (int i = 0; i < components.size(); i++) {
                Collections.sort(components.get(i).content, new sor());
            }
            component orr = nodes[0].component;
            component end = nodes[nodes.length - 1].component;
            int cur = 0;
            for (int i = 0; i < nodes.length; i++) {
                while (cur < orr.content.size()) {
                    nodes[i].component.dist1 = Math.min(nodes[i].component.dist1,
                            Math.abs(orr.content.get(cur).id - nodes[i].id));
                    if (orr.content.get(cur).id < i)
                        cur++;
                    else
                        break;
                }
                if (cur > 0)
                    cur--;
            }
            cur = 0;
            for (int i = 0; i < nodes.length; i++) {
                while (cur < end.content.size()) {
                    nodes[i].component.dist2 = Math.min(nodes[i].component.dist2,
                            Math.abs(end.content.get(cur).id - nodes[i].id));
                    if (end.content.get(cur).id < i)
                        cur++;
                    else
                        break;
                }
                // orr.content.get(cur).neighbors.add(nodes[i]);

                if (cur > 0)
                    cur--;
            }
            long answer = Long.MAX_VALUE;
            for (component c : components) {
                answer = Math.min(answer, c.dist1 * c.dist1 + c.dist2 * c.dist2);
            }
            System.out.println(answer);
        }

        in.close();
    }

    public static long dist(node n1, node n2) {
        if (n1.component == n2.component)
            return 0;
        long answer = Math.abs(n1.id - n2.id);
        answer *= answer;
        return answer;
    }

    public static class component {
        int id;
        ArrayList<node> content = new ArrayList<>();
        long dist1 = Long.MAX_VALUE;
        long dist2 = Long.MAX_VALUE;

        public component(int id) {
            this.id = id;
        }
    }

    public static class sor implements Comparator<node> {
        @Override
        public int compare(barns.node o1, barns.node o2) {
            return o1.id - o2.id;
        }
    }

    public static class node {
        int id;
        component component = null;

        ArrayList<node> neighbors = new ArrayList<>();

        public node(int id) {
            this.id = id;
        }
    }
}