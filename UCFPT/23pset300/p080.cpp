#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;
using vvpi = vector<vpi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int n, m;
struct edge{
    int a, b, w;
    int c;
    edge(int a, int b, int w, int c) : a(a), b(b), w(w), c(c) {}
    int other(int d){
        return d == a ? b : a;
    }
};
struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};
vector<edge> es;

bool connected(vi &used, int t){
    UF uf(n);
    rep(i, 0, sz(used)){
        if(!used[i] || !(es[i].c == 0 || es[i].c == t)) continue;
        uf.join(es[i].a, es[i].b);
    }
    return uf.size(0) == n;
}

int source, sink;
vvpi matroidgraph(vi &used){
    vvpi gr(m + 2);
    vi isused, isunused;
    rep(i, 0, m){
        if(!used[i]) {
            isunused.pb(i);
            continue;
        }
        used[i] = false;
        if(connected(used, 1)){
            gr[source].pb({i, -es[i].w});
        }
        if(connected(used, 2)){
            gr[i].pb({sink, 0});
        }
        used[i] = true;
        isused.pb(i);
    }
    for(int j : isunused){
        used[j] = true;
        for(int i : isused){
            used[i] =false;
            if(connected(used, 2)){
                gr[i].pb({j, es[j].w});
            }
            if(connected(used, 1)){
                gr[j].pb({i, -(es[i].w)});
            }
            used[i] = true;
        }
        used[j] = false;
    }
    return gr;
}

// self-loops and multi-edges allowed
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cin >> n >> m;
    int sum = 0;
    source = m, sink = m + 1;
    rep(i, 0, m){
        int a, b, w; char c; cin >> a >> b >> w >> c;
        a--,b--;
        int c1 = (c == 'G' ? 0 : (c == 'B' ? 1 : 2));
        es.pb(edge(a, b, w, c1));
        sum += w;
    }
    vi ans(m + 1, -1);
    int cur = sum;
    ans[m] = cur;
    vi used(m, 1);
    for(int cnt = m - 1; connected(used, 1) && connected(used, 2) && cnt >= 0; cnt--){
        vvpi gr = matroidgraph(used);
        vi dist(m + 2, INT_MAX), pre(m + 2, -1);
        dist[source] = 0;
        bool didsomething = true;
        while(didsomething){
            didsomething = false;
            rep(i, 0, m + 2){
                for(auto [j, w] : gr[i]){
                    if(dist[i] != INT_MAX && dist[i] + w < dist[j]){
                        didsomething = true;
                        dist[j] = dist[i] + w;
                        pre[j] = i;
                    }
                }
            }
        }
        vi q;
        q.pb(sink);
        while(q.back() != source && q.back() != -1){
            q.pb(pre[q.back()]);
        }
        if(q.back() == -1) break;
        for(int i : q){
            if(i < m){
                used[i] ^= true;
            }
        }
        assert(connected(used, 1) && connected(used, 2));
        cur = 0;
        rep(i, 0, m){
            if(used[i]) cur += es[i].w;
        }
        // cur += dist[sink]; 
        ans[cnt] = cur;
    }
    rep(i, 1, m + 1){
        cout << ans[i] << "\n";
    }

    
    return 0;
}