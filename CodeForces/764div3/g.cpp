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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vector<pair<ll, pi>> edges(m);
        rep(i, 0, m){
            cin >> edges[i].s.f >> edges[i].s.s >> edges[i].f;
            edges[i].s.f--, edges[i].s.s--;
        }
        sort(all(edges));
        int exc = 0, ority = 0;
        for(int b = 30; b >= 0; b--){
            exc ^= 1 << b;
            UF uf(n);
            ority = 0;
            for(auto [c, p] : edges){
                if((c & exc)) continue;
                uf.join(p.f, p.s);
                ority |= c;
            }
            bool complete = false;
            rep(i, 0, n) if(uf.size(i) == n) complete = true;
            if(!complete) exc ^= 1 << b;
        }
        ority = (1 << 31) - 1;
        ority ^= exc;
        cout << ority << nL;
    
    }
    return 0;
}
