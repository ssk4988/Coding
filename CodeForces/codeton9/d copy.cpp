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
    int n; cin >> n;
    vi a(n+1);
    rep(i, 1, n+1){
        set<int> seen;
        rep(j, 1, i) if(i % j == 0) seen.insert(a[j]);
        int mex = 0;
        for(int v : seen) if(v == mex) mex++;
        a[i] = mex;
        cout << i << " " << a[i] << "\n";
    }
    // int nc; cin >> nc;
    // rep(cn, 0, nc){
        // int n; cin >> n;
    // }
    
    return 0;
}
