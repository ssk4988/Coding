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
	vi e, rig;
	UF(int n) : e(n, -1), rig(n) {
        iota(all(rig), 0);
    }
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
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
        int n, m, q; cin >> n >> m >> q;
        vi ans(n, -1);
        vector<array<int, 2>> edges(m), qs(q);
        rep(i, 0, m){
            cin >> edges[i][0] >> edges[i][1];
            edges[i][0]--, edges[i][1]--;
        }
        rep(i, 0, q){
            cin >> qs[i][0] >> qs[i][1];
            qs[i][0]--, qs[i][1]--;
        }
        vi x(q, -1);
        for(int dif = 1 << __lg(m); dif > 0; dif /= 2){
            vvi bucket(m+1);
            rep(i, 0, q){
                if(x[i] + dif <= m){
                    bucket[x[i] + dif].pb(i);
                }
            }
            UF reg(n), rig(n);
            rep(i, 0, m + 1){
                for(int idx : bucket[i]){
                    auto [l, r] = qs[idx];
                    while(true){
                        int cur = rig.rig[rig.find(l)];
                        if(cur + 1 >= n) break;
                        if(reg.sameSet(cur, cur+1)){
                            rig.join(cur, cur+1);
                        }
                        else break;
                    }
                    if(rig.rig[rig.find(l)] < r) x[idx] += dif;
                }
                if(i < m){
                    reg.join(edges[i][0], edges[i][1]);
                }
            }
        }
        rep(i, 0, q){
            x[i]++;
            cout << x[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
