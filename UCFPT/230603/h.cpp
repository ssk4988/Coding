#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do {
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vvi A(n);
    vi b(n);
    vi x;
    int eqs = 0;
    rep(i, 0, m)
    {
        int n1, n2, c;
        cin >> n1 >> n2 >> c;
        n1--, n2--;
        if (c == 1)
        {
            b[n2]++;
            b[n1]--;
        }
        else
        {
            if(n1 > n2) swap(n1, n2);
            b[n1]--;
            b[n2]++;
            rep(j, 0, n)
            {
                A[j].pb(0);
            }
            x.pb(0);
            A[n1][eqs] = 2;
            A[n2][eqs] = -2;
            eqs++;
        }
    }
    ll sum = 0;
    rep(i, 0, n)
    {
        sum += b[i];
        if ((b[i] / 2) * 2 != b[i])
        {
            cout << "NO\n";
            return 0;
        }
        rep(j, 0, eqs)
        {
            if ((A[i][j] / 2) * 2 != A[i][j])
            {
                cout << "NO\n";
                return 0;
            }
        }
    }
    if (sum != 0)
    {
        cout << "NO\n";
        return 0;
    }

    if (eqs == 0)
    {
        bool works = true;
        rep(i, 0, n){
            if(b[i] != 0) works = false;
        }
        cout << (works ? "YES" : "NO") << "\n";
        return 0;
    }
    int source = n, sink = n + 1;
    Dinic d(n + 2);
    ll val = 0;
    rep(i, 0, n){
        if(b[i] < 0){
            d.addEdge(i, sink, abs(b[i]) / 2);
            val += abs(b[i]);
        }
        if(b[i] > 0){
            d.addEdge(source, i, abs(b[i]) / 2);
        }
    }
    rep(i, 0, eqs){
        int send = -1, receive = -1;
        rep(j, 0, n){
            if(A[j][i] == -2){
                send = j;
            }
            if(A[j][i] == 2){
                receive = j;
            }
        }
        assert(send != -1);
        assert(receive != -1);
        d.addEdge(send, receive, 1);
    }
    val /= 2;
    ll mf = d.calc(source, sink);
    cout << (mf == val ? "Yes" : "No") << "\n";

    return 0;
}
