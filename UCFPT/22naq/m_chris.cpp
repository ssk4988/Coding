#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vii;

#define nl '\n'
#define rep(i,a,b) for(int i = a; i < b; i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

const int DEBUG = false;

struct UF {
    vi e;
    UF(int n) : e(n, -1) { }
    bool sameSet(int a, int b) {return find(a) == find(b);}
    int size(int x){return -e[find(x)];}
    int find(int x){return e[x] < 0 ? x : e[x] = find(e[x]);}
    bool join(int a, int b){
        a = find(a), b = find(b);
        if(a == b) return false;
        if(e[a] > e[b]) swap(a, b);
        e[a] += e[b]; e[b] = a;
        return true;
    }
    int getNewGroup(int a, int b)
    {
        a = find(a), b = find(b);
        if(a == b) return a;
        if(e[a] > e[b]) return b;
        return a;
    }
};

int n, m, q;
vector<vii> query;
vector<pii> ans;
vector<pii> queries;
queue<int> qu;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;

    query = vector<vii> (n);
    vector<pair<int, pii>> edges(m);

    for(int i = 0; i < m; i++){
        int u, v, t;
        cin >> u >> v >> t;
        u--; v--;
        
        edges[i] = {t, {u, v}};
    }
    sort(all(edges));

    vector<vii> query (n);
    ans = vii (q, {-1, -1});
    for(int i = 0; i < q; i++){
        int u, v;
        cin >> u >> v;
        u--;v--;
        query[u].push_back({v, i});
        query[v].push_back({u, i});
    }

    UF uf(n);
    int prev = -1;
    vii waiting;

    auto clearWaiting = [&] (int w)
    {
        for(pii info : waiting)
        {
            int group = info.first;
            int idx = info.second;
            if(ans[idx].first != -1 && ans[idx].first < w) continue;
            if(DEBUG) cout << "clearWaiting with w=" << w <<" group=" << group << " idx=" << idx << nl;
            ans[idx].first = w;
            ans[idx].second = uf.size(group);
        }
        waiting.clear();
    };

    for(int i = 0; i < m; i++){
        int weight = edges[i].first;

        if(prev != weight) 
            clearWaiting(prev);

        prev = weight;

        int u = edges[i].second.first;
        int v = edges[i].second.second;
        if(DEBUG) cout << "adding edge " << u << "=>" << v << " with weight=" << weight << nl;

        if(uf.find(u) == uf.find(v)) continue; // already connected

        // int update = uf.size(u) < uf.size(v) ? u : v;
        // int other = update == u ? v : u;
        int newGroup = uf.getNewGroup(u, v);
        int prevGroup = newGroup == uf.find(u) ? uf.find(v) : uf.find(u);

        while(!query[prevGroup].empty())
        {
            int node = uf.find(query[prevGroup].back().first);
            int idx = query[prevGroup].back().second;
            query[prevGroup].pop_back();

            if(uf.find(prevGroup) == uf.find(node) || uf.find(newGroup) == uf.find(node))    // in same set now
            {
                waiting.push_back({node, idx});
            }

            else
            {
                query[newGroup].push_back({uf.find(node), idx});
            }
        }

        uf.join(u, v);
    }

    clearWaiting(prev);
    for(int i = 0; i < q; i++){
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
    


    return 0;
}