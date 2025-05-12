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

void solve() {
    int n; cin >> n;
    int LIM = n+1;
    vi dp(LIM, -1);
    for(int i = 0; i * i < LIM; i++) {
        for(int j = 0; i*i+j * j < LIM; j++) {
            dp[i*i+j*j] = i;
        }
    }
    int c = 0;
    vii make;
    rep(i, 0, LIM) {
        if(dp[i] != -1) make.pb({i, dp[i]});
    }
    int p = sz(make)-1;
    rep(i, 0, sz(make)) {
        while(p >= 0 && make[i].f + make[p].f > n) p--;
        if(p >= 0 && make[i].f + make[p].f == n) {
            int a = make[i].s, b = make[p].s;
            cout << a << " " << int(sqrt(make[i].f-a*a)) << " " << b << " " <<  int(sqrt(make[p].f-b*b)) << "\n";
            return;
        }
    }
    assert(false);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();

    
    return 0;
}
