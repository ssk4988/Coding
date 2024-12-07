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
    const int N = 10010;
    vi mobius(N);
    vvi divs(N);
    mobius[1] = 1;
    rep(i, 1, N) {
        for(int j = 2 * i; j < N; j += i) {
            mobius[j] -= mobius[i];
        }
        for(int j = i; j < N; j += i) {
            divs[j].pb(i);
        }
    }
    vi freq(N);
    int n;
    while(cin >> n) {
        vi a(n);
        rep(i, 0, n) cin >> a[i];
        vi check;
        for(int i : a) {
            for(int j : divs[i]) {
                freq[j]++;
                check.pb(j);
            }
        }
        ll ans = 0;
        sort(all(check));
        check.erase(unique(all(check)), end(check));
        for(int i : check) {
            if(freq[i] >= 4) ans += ll(freq[i]) * (freq[i]-1) * (freq[i]-2) * (freq[i]-3) / 24 * mobius[i];
            freq[i] = 0;
        }
        cout << ans << "\n";
    }
    
    
    return 0;
}
