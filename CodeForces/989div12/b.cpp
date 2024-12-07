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

void solve(int cn) {
    int n, m, k; cin >> n >> m >> k;
    string s; cin >> s;
    int ans = 0;
    int window = 0;
    rep(i, 0, n){
        window += s[i] == '0';
        if(i >= m) {
            window -= s[i - m] == '0';
        }
        if(window >= m) {
            window -= s[i] == '0';
            rep(j, 0, k){
                if(i + j < n) s[i + j] = '1';
            }
            window += s[i] == '0';
            ans++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve(cn);
    }
    
    return 0;
}
