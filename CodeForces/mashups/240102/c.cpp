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

bitset<2500> rows[2500];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi a(n, vi(n));
    vector<array<int, 3>> m;
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> a[i][j];
            m.pb({a[i][j], i, j});
        }
    }
    sort(all(m));
    reverse(all(m));
    bool valid = true;
    rep(i, 0, n){
        if(a[i][i] != 0) valid = false;
        rep(j, 0, n){
            if(a[i][j] != a[j][i]) valid = false;
        }
    }
    int idx = 0;
    while(valid && idx < sz(m)){
        int nextidx = idx;
        while(nextidx < sz(m) && m[nextidx][0] == m[idx][0]) nextidx++;
        rep(x, idx, nextidx){
            auto [w, i, j] = m[x];
            rows[i][j] = 1;
            rows[j][i] = 1;
        }
        rep(x, idx, nextidx){
            auto [w, i, j] = m[x];
            if(i < j && (rows[i] | rows[j]).count() != n) {valid = false; break;}
        }
        idx = nextidx;
    }
    // for(auto const& [key, v] : m){
    //     if(!valid) break;
    //     for(auto [i, j] : v){
    //         rows[i][j] = 1;
    //     }
    //     for(auto [i, j] : v){
            
    //     }
    // }
    cout << (valid ? "MAGIC" : "NOT MAGIC") << nL;

    
    return 0;
}
