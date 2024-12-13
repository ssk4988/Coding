#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve() {
    int n, m; cin >> n >> m;
    vi a(n), b(n), s(n);
    map<int, vi> pd;
    rep(i, 0, n){
        cin >> a[i] >> b[i] >> s[i];
        pd[s[i]].pb(i);
    }
    vvi teams;
    vi los, his;
    const int inf = 1e9;
    vi tp(n);
    rep(t, 0, 2){
        int k; cin >> k;
        teams.pb({});
        int lo = inf, hi = -inf;
        rep(i, 0, k){
            int v; cin >> v; v--;
            teams.back().pb(v);
            lo = min(lo, a[v]);
            hi = max(hi, a[v]);
            tp[v] = t;
        }
        los.pb(lo);
        his.pb(hi);
    }
    if(his[1] > los[0]){
        cout << "-1\n";
        return;
    }
    int topic = inf;
    vii probs;
    probs.pb({los[0], topic--});
    probs.pb({los[0]+1, topic--});
    for(auto &[key, val] : pd) {
        int hi = -inf, lo = inf;
        for(int i : val){
            if(tp[i] && a[i] == los[0]) hi = max(hi, b[i]);
            if(!tp[i] && a[i] == los[0]) lo = min(lo, b[i]);
        }
        if(hi >= lo) goto bad;
        if(lo == inf) continue;
        probs.pb({lo, key});
    }
    cout << sz(probs) << "\n";
    for(auto [d, t] : probs) cout << d << " " << t << "\n";


    return;
    bad:
    cout << "-1\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
