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
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges(m);
    rep(i, 0, m){
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
        edges[i][1]--, edges[i][2]--;
    }
    int lo = 0, hi = m;
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        vector<array<int, 3>> e1(edges.begin(), edges.begin() + mid + 1);
        sort(all(e1));
        UF uf(n);
        int mnw = 0, mxw = 0;
        bool useless = false;
        vector<vpi> adj(n);
        for(auto [w, a, b] : e1){
            if(uf.join(a, b)) {
                mnw += w;
            }
        }
        uf = UF(n);
        reverse(all(e1));
        for(auto [w, a, b] : e1){
            if(uf.join(a, b)) {
                mxw += w;
            }
        }
        
        if(mnw != mxw){
            hi = mid;
        }
        else lo = mid + 1;
    }
    // cout << lo << nL;
    rep(i, 0, lo){
        cout << 0;
    }
    rep(i, lo, m) cout << 1;
    cout << nL;

    
    return 0;
}
