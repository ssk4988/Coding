import java.io.*;
import java.util.*;

public class c {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer tokenizer = new StringTokenizer(in.readLine());
        int nStates = Integer.parseInt(tokenizer.nextToken());
        int nTrans = Integer.parseInt(tokenizer.nextToken());
        int nProp = Integer.parseInt(tokenizer.nextToken());
        state[] s = new state[nStates];
        for (int i = 0; i < nStates; i++) {
            s[i] = new state();
            s[i].id = i;
            s[i].p = new boolean[nProp];
            s[i].next = new boolean[nProp];
            Arrays.fill(s[i].next, true);
            tokenizer = new StringTokenizer(in.readLine());
            int k = Integer.parseInt(tokenizer.nextToken());
            for (int j = 0; j < k; j++) {
                s[i].p[tokenizer.nextToken().charAt(0) - 'a'] = true;
            }
        }
        for (int i = 0; i < nTrans; i++) {
            tokenizer = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(tokenizer.nextToken()) - 1;
            int b = Integer.parseInt(tokenizer.nextToken()) - 1;
            s[a].children.add(s[b]);
            s[b].parents.add(s[a]);
        }
        for (int i = 0; i < nProp; i++) {
            for (int j = 0; j < nStates; j++) {
                if (!s[j].p[i])
                    rdfs(s[j], i);
            }
        }
        String q = in.readLine();
        int x = q.charAt(2) - 'a';
        int y = q.charAt(7) - 'a';
        Set<state> set = new TreeSet<>((o1, o2) -> o1.id - o2.id);
        for (int i = 0; i < nStates; i++) {
            if (s[i].next[y]) {
                rdfs2(set, s[i], x);
            }
        }
        System.out.println(set.size());
        for(state s1 : set){
            System.out.println(s1.id + 1);
        }
        in.close();
    }

    public static void rdfs2(Set<state> set, state s1, int x) {
        set.add(s1);
        for (state s2 : s1.parents) {
            if(set.contains(s2)) continue;
            if(s2.p[x]){
                rdfs2(set, s2, x);
            }
        }
    }

    public static void rdfs(state s1, int p) {
        s1.next[p] = false;
        for (state s2 : s1.parents) {
            if (s2.next[p])
                rdfs(s2, p);
        }
    }

    public static class state {
        int id;
        boolean[] p;
        boolean[] next;
        Set<state> parents = new HashSet<>();
        Set<state> children = new HashSet<>();
    }
}