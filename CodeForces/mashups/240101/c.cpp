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
    // CHECK n=2
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    UF uf(n);
    vector<vl> cost(n, vl(n));
    vector<array<ll, 3>> e, edges;
    rep(i, 0, n)
    {
        rep(j, 0, i + 1)
        {
            cin >> cost[i][j];
            cost[j][i] = cost[i][j];
            e.pb({cost[i][j], i, j});
        }
    }
    sort(all(e));
    reverse(all(e));
    for(auto [w, i, j] : e){
        if(uf.join(i, j)){
            ll w1 = (cost[i][i] - cost[i][j] + cost[j][j] - cost[i][j]) / n;
            edges.pb({i, j, w1});
        }
    }
    for(auto [i, j, w] : edges){
        cout << (i + 1) << " " << (j + 1) << " " << w << nL;
    }

    return 0;
}
