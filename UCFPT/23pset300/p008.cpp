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

const int inf = 1e9+100;
struct sub {
    ll best = 0, suff = 0, pref = 0, sum = 0;
};
sub operator+(sub l, sub r){
    sub res;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.sum = l.sum + r.sum;
    res.best = max(l.best, r.best);
    res.best = max(res.best, l.suff + r.pref);
    return res;
}
struct PST {
	PST *l = 0, *r = 0;
	ll lo, hi;
    sub val;
	PST(ll lo,ll hi):lo(lo),hi(hi){} // Large interval of -inf
	void insert(ll coord, ll v) {
		if (coord + 1 <= lo || hi <= coord) return;
		if (coord <= lo && hi <= coord + 1){
            val.sum += v;
            val.pref = val.suff = val.best = max(0LL, val.sum);
        }
		else {
			push(), l->insert(coord,v), r->insert(coord,v);
			val = l->val + r->val;
		}
	}
	void push() {
		if (!l) {
			ll mid = lo + (hi - lo)/2;
			l = new PST(lo, mid); r = new PST(mid, hi);
		}
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    map<ll, vpl> mm;
    int n; cin >> n;
    set<ll> ys;
    rep(i, 0, n){
        ll x, y; cin >> x >> y;
        ys.insert(y);
        mm[x].pb({y, 1});
    }
    cin >> n;
    rep(i, 0, n){
        ll x, y; cin >> x >> y;
        ys.insert(y);
        mm[x].pb({y, -1});
    }
    unordered_map<ll, int> cc;
    for(ll i : ys){
        cc[i] = sz(cc);
    }
    ll c1, c2; cin >> c1 >> c2;
    vector<vpl> stuff;
    for(auto &p : mm){
        for(pl &p1 : p.str){
            if(p1.str == 1) p1.str = c1;
            else p1.str = -c2;
            p1.f = cc[p1.f];
        }
        stuff.pb(p.str);
    }
    ll ans = 0;
    rep(i, 0, sz(stuff)){
        PST tree(-5, sz(cc) + 5);
        rep(j, i, sz(stuff)){
            for(auto &p : stuff[j]){
                tree.insert(p.f, p.str);
            }
            ans = max(ans, tree.val.best);
        }
    }
    cout << ans << "\n";
    
    return 0;
}
