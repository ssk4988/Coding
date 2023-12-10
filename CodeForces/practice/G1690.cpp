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
	vi e, rig, sp;
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
		e[a] += e[b]; e[b] = a;
        rig[a] = max(rig[a], rig[b]);
        sp[a] = min(sp[a], sp[b]);
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, q; cin >> n >> q;
        vi v(n);
        // UF uf(n);
        set<int> ss;
        rep(i, 0, n){
            cin >> v[i];
            if(sz(ss) == 0 || v[*ss.rbegin()] > v[i]){
                ss.insert(i);
            }
        }
        // uf.sp = v;
        // rep(i, 0, n - 1){
        //     if(v[i] <= v[i + 1]) uf.join(i, i + 1);
        // }
        rep(i, 0, q){
            int idx, d; cin >> idx >> d; idx--;
            v[idx] -= d;
            if(!ss.count(idx)){
                auto it = ss.upper_bound(idx);
                if(it != ss.begin()){
                    it = prev(it);
                    if(v[*it] > v[idx]) ss.insert(idx);
                }
            }
            while(true){
                auto it = ss.upper_bound(idx);
                if(it == ss.end()) break;
                if(v[*it] >= v[idx]) ss.erase(it);
                else break;
            }
            cout << sz(ss) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
