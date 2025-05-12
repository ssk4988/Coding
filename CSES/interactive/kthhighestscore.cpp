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
    int k; cin >> k; k--;
    // find last i such that a[i] < b[k-i]
    int ans = -1;
    for(int dif = 1 << 20; dif; dif /= 2) {
        int cur = ans + dif;
        if(cur >= n) continue;
        bool works = true;
        int other = k - cur;
        if(other >= n) {
            // cur too small
            works = true;
        } else if(other < 0) {
            // cur too big
            works = false;
        } else {
            cout << "F " << cur+1 << endl;
            int v; cin >> v;
            cout << "S " << other+1 << endl;
            int w; cin >> w;
            works = v > w;
        }
        if(works) ans = cur;
    }
    int res = 1e9+10;
    if(ans >= 0) {
        cout << "F " << ans+1 << endl;
        int v; cin >> v; 
        res = min(res, v);
    }
    int other = k-(ans+1);
    if(0 <= other && other < n) {
        cout << "S " << other+1 << endl;
        int v; cin >> v;
        res = min(res, v);
    }
    cout << "! " << res << endl;

    
    return 0;
}
