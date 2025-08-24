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
        int n; cin >> n;
        vi freq(n+1);
        rep(i, 0, n) {
            int a; cin >> a; freq[a]++;
        }
        int mex = 0;
        while(freq[mex]) mex++;
        int cnt = 0;
        rep(i, mex, n+1) cnt += freq[i];
        rep(i, 0, mex) cnt += max(0, freq[i]-1);
        vi ans(n+2);
        for(int i = mex; i >= 0; i--) {
            cnt += freq[i];
            cnt -= max(0, freq[i]-1);
            int low = freq[i];
            int high = cnt;
            ans[low]++;
            ans[high+1]--;
        }
        rep(i, 1, sz(ans)) ans[i] += ans[i-1];
        rep(i, 0, n+1) cout << ans[i] << " ";
        cout << "\n";
    }
    
    return 0;
}
