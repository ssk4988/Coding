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
    int n, m, q; cin >> n >> m >> q;
    UF uf(n);
    vpi roads(m);
    rep(i, 0, m){
        int a, b; cin >> a >> b; a--,b--;
        roads[i] = {a, b};
    }
    vpi queries(q);
    vi l(q), r(q, m);
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--,b--;
        queries[i] = {a, b};
        if(a == b) l[i] = r[i] = -1;
    }
    while(true){
        bool didsomething = false;
        vvi buckets(m + 1);
        rep(i, 0, q){
            if(l[i] == r[i]) continue;
            int mid = l[i] + (r[i] - l[i]) / 2;
            buckets[mid].pb(i);
            didsomething = true;
        }
        UF uf(n);
        rep(i, 0, m){
            uf.join(roads[i].f, roads[i].s);
            for(int j : buckets[i]){
                if(uf.sameSet(queries[j].f, queries[j].s)){
                    r[j] = i;
                }
                else{
                    l[j] = i + 1;
                }
            }
        }
        if(!didsomething) break;
    }
    rep(i, 0, q) if(l[i] == m) l[i] = -2;
    rep(i, 0, q) cout << (l[i] + 1) << nL;

    return 0;
}
