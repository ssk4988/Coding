#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

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
    rep(cn, 0, nc) {
        int n, m, q; cin >> n >> m >> q;
        vii ed(m);
        vi blocked(m);
        rep(i, 0, m) {
            cin >> ed[i].f >> ed[i].s; ed[i].f--, ed[i].s--;
        }
        UF uf(n);
        vii qs(q);
        rep(i, 0, q) {
            cin >> qs[i].f >> qs[i].s; qs[i].s--;
            if(qs[i].f == 1) blocked[qs[i].s] = 1;
        }
        rep(i, 0, m) if(!blocked[i]) uf.join(ed[i].f, ed[i].s);
        vi ans(q, -1);
        for(int i = q-1; i >= 0; i--) {
            if(qs[i].f == 1) {
                blocked[qs[i].s] = false;
                uf.join(ed[qs[i].s].f, ed[qs[i].s].s);
            } else {
                ans[i] = uf.size(qs[i].s);
            }
        }
        rep(i, 0, q) {
            if(ans[i] != -1) cout << ans[i] << "\n";
        }
    }
    
    return 0;
}
