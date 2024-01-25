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
	vi e, lef, rig;
    int ncomps;
	UF(int n) : e(n, -1), ncomps(n), lef(n), rig(n) {
        iota(all(lef), 0);
        iota(all(rig), 0);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(vi &x, int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
        ncomps--;
		if (x[a] > x[b]) swap(a, b);
        lef[a] = min(lef[a], lef[b]);
        rig[a] = max(rig[a], rig[b]);
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
        int n; cin >> n;
        vi a(n);
        UF uf(n);
        vvi bucket(n);
        rep(i, 0, n){
            cin >> a[i];
            bucket[a[i]].pb(i);
        }
        for(int i = n - 1; i >= 1; i--){
            for(int j : bucket[i]){
                int lefb = uf.lef[uf.find(j)];
                int rigb = uf.rig[uf.find(j)];
                if(lefb > 0 && a[uf.find(j)] == a[j] && (a[uf.find(lefb-1)] == a[j] || a[uf.find(lefb-1)] == a[j] - 1)){
                    uf.join(a, lefb-1, j);
                }
                lefb = uf.lef[uf.find(j)];
                rigb = uf.rig[uf.find(j)];
                if(rigb + 1 < n && a[uf.find(j)] == a[j] && (a[uf.find(rigb + 1)] == a[j] || a[uf.find(rigb + 1)] == a[j] - 1)){
                    uf.join(a, rigb + 1, j);
                }
            }
        }
        bool valid = uf.size(0) == n && a[uf.find(0)] == 0;
        cout << (valid ? "YES" : "NO") << nL;
    }
    
    return 0;
}
