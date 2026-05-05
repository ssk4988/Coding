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
    int n, m; cin >> n >> m;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vector<array<int, 2>> rng(m);
    vector<set<int>> deg(n+1);
    vi res(m);
    rep(i, 0, m) {
        cin >> rng[i][0] >> rng[i][1];
        rng[i][0]--;
        deg[rng[i][0]].insert(i);
        if(rng[i][1] < n) deg[rng[i][1]].insert(i);
    }
    for(int i = n-1; i > 0; i--) {
        a[i] ^= a[i-1];
    }
    queue<int> q;
    rep(i, 0, n) if(sz(deg[i]) == 1) q.push(i);
    rep(l, -1, n) {
        if(l >= 0 && sz(deg[l])) {
            q.push(l);
        }
        while(sz(q)) {
            int i = q.front(); q.pop();
            int j = *deg[i].begin();
            res[j] = a[i];
            for(int k : rng[j]) {
                if(k == n) continue;
                // cerr << i << " " << j << " " << k << endl;
                a[k] ^= res[j];
                deg[k].erase(j);
                if(sz(deg[k]) == 1) q.push(k);
            }
        }
    }
    bool works = true;
    rep(i, 0, n) if(a[i]) {
        works = false;
    }
    if(works) {
        cout << m << "\n";
        rep(i, 0, m) cout << i+1 << " " << res[i] << "\n";
    } else cout << "-1\n";
    
    return 0;
}
