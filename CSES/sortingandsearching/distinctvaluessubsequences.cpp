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
const ll mod = 1e9+7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    map<int, int> freq;
    rep(i, 0, n) {
        int v; cin >> v; freq[v]++;
    }
    ll ans = 1;
    for(auto [key, val] : freq) {
        ans = ans * (val+1) % mod;
    }
    cout << ans-1 << "\n";
    
    return 0;
}
