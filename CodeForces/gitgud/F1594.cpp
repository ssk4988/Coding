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
// 90154 11754 78586 should be no, but returns yes
void solve() {
    ll s, n, k; cin >> s >> n >> k;
    if(s < k){
        cout << "NO\n";
    }
    else if(s == k){
        cout << "YES\n";
    }
    else if(k <= n){
        if(s >= n + (n / k) * k) cout << "NO\n";
        else cout << "YES\n";
    }
    else{
        // s > k > n
        cout << "NO\n";
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }
    
    return 0;
}
