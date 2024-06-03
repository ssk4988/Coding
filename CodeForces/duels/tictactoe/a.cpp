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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vi mx(n), mn(n), cur(n), inv(n);
    iota(all(mx), 0);
    iota(all(mn), 0);
    iota(all(cur), 0);
    iota(all(inv), 0);
    rep(i, 0, m){
        int p; cin >> p; p--;
        int idx = inv[p];
        if(idx == 0) continue;
        swap(cur[idx], cur[idx-1]);
        inv[p]--;
        inv[cur[idx]]++;
        mx[cur[idx]] = max(mx[cur[idx]], idx);
        mn[cur[idx]] = min(mn[cur[idx]], idx);
        mx[cur[idx-1]] = max(mx[cur[idx-1]], idx-1);
        mn[cur[idx-1]] = min(mn[cur[idx-1]], idx-1);
    }
    rep(i, 0, n){
        cout << mn[i]+1 << " " << mx[i]+1 << "\n";
    }
    
    return 0;
}
