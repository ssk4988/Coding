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
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    const int B = 400;
    int blocks = (n-1)/B+10;
    vi off(blocks, B);
    vi cnt(n+1);
    rep(i, 0, n) {
        if(a[i] <= n) {
            cnt[a[i]]++;
            if(cnt[a[i]] == 1) off[a[i]/B]--;
        }
        if(i >= k) {
            if(a[i-k] <= n) {
                cnt[a[i-k]]--;
                if(cnt[a[i-k]] == 0) off[a[i-k]/B]++;
            }
        }
        if(i >= k-1) {
            int ans = 0;
            while(off[ans] == 0) ans++;
            ans *= B;
            rep(i, 0, B) {
                if(cnt[ans + i] == 0) {
                    ans += i;
                    break;
                }
            }
            cout << ans << " ";
        }
    }    
    cout << "\n";

    
    return 0;
}
