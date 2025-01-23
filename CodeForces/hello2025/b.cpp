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
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, k; cin >> n >> k;
        vi a(n);
        map<int, int> freq;
        rep(i, 0, n){
            cin >> a[i];
            freq[a[i]]++;
        }
        vii fs;
        for(auto [key, val] : freq){
            fs.pb({val, key});
        }
        sort(all(fs));
        int ans = sz(fs);
        rep(i, 0, sz(fs)-1){
            if(k >= fs[i].f) ans--, k -= fs[i].f;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
