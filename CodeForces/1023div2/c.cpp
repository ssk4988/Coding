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
    const ll inf = 1e12+100;
    rep(cn, 0, nc) {
        ll n, k; cin >> n >> k;
        vl a(n);
        vi s(n);
        {
            string str; cin >> str;
            rep(i, 0, n) s[i] = str[i] == '1';
        }
        rep(i, 0, n) {
            cin >> a[i];
            if(s[i] == 0) a[i] = -inf;
        }
        vl bestleft(n), bestright(n);
        ll best = 0, cur = 0;
        rep(i, 0, n) {
            bestleft[i] = cur;
            cur = max(0LL, cur + a[i]);
            best = max(best, cur);
        }
        if(best > k) {
            cout << "No\n";
            continue;
        }
        if(best == k) {
            cout << "Yes\n";
            for(auto &v : a) cout << v << " ";
            cout << "\n";
            continue;
        }
        cur = 0;
        for(int i = n-1; i >= 0; i--) {
            bestright[i] = cur;
            cur = max(0LL, cur + a[i]);
        }
        bool found = 0;
        rep(i, 0, n) {
            if(s[i] == 0) {
                if(abs(k-(bestleft[i]+bestright[i])) > 1e18) continue;
                a[i] = k - (bestleft[i] + bestright[i]);
                found = 1;
                break;
            }
        }
        if(found) {
            cout << "Yes\n";
            for(auto &v : a) cout << v << " ";
            cout << "\n";
        } else cout << "No\n";
    }
    
    return 0;
}
