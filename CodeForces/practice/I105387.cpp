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

bool solve(int n) {
    vi p(n, 1);
    vvi bucket(n+1);
    rep(i, 1, n+1) bucket[0].pb(i);
    rep(i, 0, n) {
        if(sz(bucket[i]) == 0) continue;
        int mn = *min_element(all(bucket[i])), mx = *max_element(all(bucket[i]));
        while(p[i] < mx || i + p[i] / mn < n){
            p[i]++;
        }
        while(i + (p[i]+1) / mn == n) p[i]++;
        if(i + p[i] / mn > n) {
            cerr << "issue: n=" << n << " bucket=" << i << endl;
            return false;
            break;
        }
        for(int u : bucket[i]) {
            bucket[i + p[i] / u].pb(u);
        }
    }
    // rep(i, 0, n) {
    //     cout << p[i] << " ";
    // }
    // cout << "\n";
    return true;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int n; cin >> n;
    int v = 1;
    while(solve(v)) v++;

    cout << "bad n: " << v << endl;
    return 0;
}
