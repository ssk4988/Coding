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

template<int B>
struct XORBasis {
	bitset<B> basis[B];
	int npivot = 0, nfree = 0;
	bool check(bitset<B> v) {
		for(int i = B - 1; i >= 0; i--)
			if (v.test(i)) v ^= basis[i];
		return v.none();
	}
	bool add(bitset<B> v) {
		for(int i = B - 1; i >= 0; i--)
			if (v.test(i)) {
				if (basis[i].none()) return basis[i] = v, ++npivot;
				v ^= basis[i];
			}
        return !++nfree;
	}
    void operator+=(XORBasis &r){
        for(int i = B - 1; i >= 0; i--){
            if(r.basis[i].any()) add(r.basis[i]);
        }
        // return this;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<bitset<20>> c(n);
    rep(i, 0, n){
        int v; cin >> v;
        c[i] ^= v;
    }
    int q; cin >> q;
    vector<array<int, 3>> qs(q);
    rep(i, 0, q){
        cin >> qs[i][0] >> qs[i][1];
        qs[i][0]--, qs[i][1]--;
        qs[i][2] = i;
    }
    vector<XORBasis<20>> ans(q);
    vvi buckets(n);
    auto solve = [&](int l, int r, vector<array<int, 3>> &queries, auto &&solve) -> void{
        // base case for l + 1 == r
        int mid = l + (r - l) / 2;
        // cout << l << "," << r << " " << mid << " " << sz(queries) << "\n";
        // [l, r)
        vector<array<int, 3>> qls, qrs;
        for(auto &qq : queries){
            auto [ql, qr, idx] = qq;
            if(qr < mid && l + 1 < r){
                qls.pb(qq);
                // cout << "putting query " << idx << " in left\n";
            }
            else if(ql >= mid && l + 1 < r){
                qrs.pb(qq);
                // cout << "putting query " << idx << " in right\n";
            }
            else{
                buckets[ql].pb(idx);
                if(qr != ql) buckets[qr].pb(idx);
            }
        }
        XORBasis<20> suff, pref;
        rep(i, mid, r){
            pref.add(c[i]);
            for(int idx : buckets[i]){
                ans[idx] += pref;
                // cout << "adding right of " << mid << " to " << i << " to query " << idx << " with basis size " << pref.npivot << "\n";
            }
        }
        for(int i = mid - 1; i >= l; i--){
            suff.add(c[i]);
            for(int idx : buckets[i]){
                ans[idx] += suff;
                // cout << "adding left of " << i << " to " << mid-1 << " to query " << idx << "\n";
            }
        }
        rep(i, l, r){
            buckets[i].clear();
        }
        if(l + 1 == r) return;
        solve(l, mid, qls, solve);
        solve(mid, r, qrs, solve);
    };
    solve(0, n, qs, solve);
    rep(i, 0, q){
        bitset<20> v;
        for(int j = 19; j >= 0; j--){
            if(!v[j]) v ^= ans[i].basis[j];
        }
        cout << v.to_ullong() << "\n";
    }

    
    return 0;
}
