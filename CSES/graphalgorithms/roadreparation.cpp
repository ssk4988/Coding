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
using vvl = vector<vl>;

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
    int n, m; cin >> n >> m;
    vvl edges(m);
    rep(i, 0, m){
        int a, b; ll c; cin >> a >> b >> c; a--,b--;
        edges[i] = {c, a, b};
    }
    sort(all(edges));
    UF uf(n);
    ll costs = 0; 
    int joins = 0;
    rep(i, 0, m){
        if(!uf.sameSet(edges[i][1], edges[i][2])){
            uf.join(edges[i][1], edges[i][2]);
            joins++;
            costs += edges[i][0];
        }
    }
    if(joins == n - 1) cout << costs << nL;
    else cout << "IMPOSSIBLE\n";
    // cout << (joins == n - 1 ? costs : ) << nL;
    
    return 0;
}
