vi tin, comp, z, cont;
int Time, ncomps;
template<class G, class F> int dfs(int cur, G& g, F& f) {
    int low = tin[cur] = ++Time, x; z.push_back(cur);
    for(auto nxt : g[cur]) if (comp[nxt] < 0)
        low = min(low, tin[nxt] ?: dfs(nxt, g, f));
    if (low == tin[cur]) {
        do {
            x = z.back(); z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != cur);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return tin[cur] = low;
}
template<class G, class F> void scc(G& g, F f) {
    int n = sz(g);
    tin.assign(n, 0); comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if(comp[i] < 0) dfs(i, g, f);
}
