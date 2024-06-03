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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vi hasprev(n), hasnext(n);
        set<int> ss;
        rep(i, 0, n){
            if(ss.count(a[i])) hasprev[i] = true;
            ss.insert(a[i]);
            // if(i) hasprev[i] += hasprev[i-1];
        }
        ss.clear();
        for(int i = n-1; i >= 0; i--) {
            if(ss.count(a[i])) hasnext[i] = true;
            ss.insert(a[i]);
            if(i + 1 < n) hasnext[i] += hasnext[i+1];
        }
        ll ans = 0;
        rep(i, 0, n){
            if(hasprev[i]) continue;
            ans += n - i - hasnext[i];
        }
        cout << ans << "\n";

    }
    
    return 0;
}
