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

void solve(int cn) {
    int n, m; cin >> n >> m;
    vi a(n), b(n), s(n);
    map<int, vi> pd;
    rep(i, 0, n){
        cin >> a[i] >> b[i] >> s[i];
        // if(cn == 50) cout << a[i] << " " << b[i] << " " << s[i] << endl;
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
            // if(cn == 50) cout << v << " ";
            teams.back().pb(v);
            lo = min(lo, a[v]);
            hi = max(hi, a[v]);
            tp[v] = t;
        }
        // if(cn == 50) cout << "\n";
        los.pb(lo);
        his.pb(hi);
    }
    int topic = inf;
    vii probs;
    probs.pb({his[1]+1, topic--});
    probs.pb({los[0], topic--});
    map<int, int> topicdiff;
    for(auto &[key, val] : pd) {
        int lo = inf;
        for(int i : val){
            if(tp[i] == 0 && a[i] <= his[1]) lo = min(lo, b[i]);
        }
        if(lo != inf){
            probs.pb({lo, key});
            topicdiff[key] = lo;
        }
    }
    vi score(n);
    vi pidx(n);
    iota(all(pidx), 0);
    sort(all(pidx), [&](int i, int j) { return a[i] < a[j]; });
    sort(all(probs));
    int p = 0;
    for(int i : pidx) {
        while(p < sz(probs) && probs[p].f <= a[i]) {
            p++;
        }
        score[i] = p;
        if(topicdiff.count(s[i])) {
            int d = topicdiff[s[i]];
            if(a[i] < d && d <= b[i]) score[i]++;
        }
    }
    vi mx(2, -inf), mn(2, inf);
    rep(i, 0, n){
        mx[tp[i]] = max(mx[tp[i]], score[i]);
        mn[tp[i]] = min(mn[tp[i]], score[i]);
    }
    if(mx[1] >= mn[0]){
        cout << "-1\n";
        return;
    }
    // if(cn < 5) {
        cout << sz(probs) << "\n";
        for(auto [d, t] : probs) cout << d << " " << t << "\n";
    // }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve(cn);
    
    return 0;
}
