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
	vi e; int ncomps;
	UF(int n) : e(n, -1), ncomps(n) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        ncomps--;
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    UF uf(n);
    set<pi> edges;
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        if(a > b) swap(a, b);
        edges.insert({a, b});
    }
    vpi qs(k);
    rep(i, 0, k){
        cin >> qs[i].f >> qs[i].s; qs[i].f--, qs[i].s--;
        if(qs[i].f > qs[i].s) swap(qs[i].f, qs[i].s);
        edges.erase(qs[i]);
    }
    for(auto [a, b] : edges) uf.join(a, b);
    vi ans;
    for(int i = k - 1; i >= 0; i--){
        ans.pb(uf.ncomps);
        uf.join(qs[i].f, qs[i].s);
    }
    reverse(all(ans));
    for(int i : ans) cout << i << " ";
    cout << nL;

    
    return 0;
}