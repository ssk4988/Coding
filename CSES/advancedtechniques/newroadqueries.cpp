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

vpi queries;
vi answers;
vvi appearances;

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b, int t) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
        for(int i : appearances[b]){
            appearances[a].pb(i);
        }
		e[a] += e[b]; e[b] = a;
        for(int i : appearances[b]){
            if(sameSet(queries[i].f, queries[i].s) && answers[i] == -1) answers[i] = t;
        }
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
    queries.resize(q);
    answers.assign(q, -1);
    appearances.resize(n);
    rep(i, 0, q){
        int a, b; cin >> a >> b; a--,b--;
        queries[i] = {a, b};
        appearances[a].pb(i);
        appearances[b].pb(i);
        if(a == b) answers[i] = 0;
    }
    rep(i, 0, m){
        uf.join(roads[i].f, roads[i].s, i + 1);
    }
    rep(i, 0, q) cout << answers[i] << nL;

    return 0;
}