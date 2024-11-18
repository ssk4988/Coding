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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k; k--;
    vl a(n);
    map<ll, int> frq;
    rep(i, 0, n) cin >> a[i], frq[a[i]]++;
    if(frq[a[k]] == 1) {
        cout << "0\n"; return 0;
    }
    vector<pair<char, ll>> ops(m);
    rep(i, 0, m) cin >> ops[i].f >> ops[i].s;
    map<ll, pair<int, ll>> prv;
    queue<ll> q;
    q.push(a[k]);
    prv[a[k]] = {-1, -1};
    ll res = -1;
    while(sz(q)){
        ll x = q.front(); q.pop();
        rep(i, 0, m){
            ll v = x;
            if(ops[i].f == '+') v += ops[i].s;
            if(ops[i].f == '-') v -= ops[i].s;
            if(ops[i].f == '*') v *= ops[i].s;
            if(ops[i].f == '/') v /= ops[i].s;
            if(prv.count(v) || v < 0) continue;
            prv[v] = {i, x};
            if(!frq.count(v)){
                res = v;
                goto fnd;
            }
            q.push(v);
        }
    }
    fnd:
    if(res == -1){ cout << res << "\n"; return 0; }
    vi act;
    while(res != -1 && prv[res].f != -1){
        act.pb(prv[res].f);
        res = prv[res].s;
    }
    reverse(all(act));
    cout << sz(act) << "\n";
    for(int v : act) cout << v+1 << "\n";

    
    return 0;
}
