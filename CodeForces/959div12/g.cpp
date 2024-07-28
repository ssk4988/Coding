#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

vi read() {
    string str; cin >> str;
    vi a(sz(str));
    rep(i, 0, sz(a)) a[i] = str[i] - '0';
    reverse(all(a));
    return a;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vi target(read());
        vi cnt(m);
        vi res(m);
        rep(i, 0, n){
            vi x = read();
            rep(j, 0, m) if(x[j]) cnt[j]++;
        }
        vvi dp(m, vi(n * 3, -2));
        auto go = [&](int place, int sum, auto &&go) -> int {
            if(place == m) return sum == 0 ? 0 : -1;
            if(dp[place][sum] != -2) return dp[place][sum];
            if((cnt[place] + sum) % 2 == target[place]) {
                if(go(place+1, (cnt[place] + sum)/2, go) != -1) return dp[place][sum] = 0;
            }
            if((n - cnt[place] + sum) % 2 == target[place]) {
                if(go(place+1, (n - cnt[place] + sum)/2, go) != -1) return dp[place][sum] = 1;
            }
            return dp[place][sum] = -1;
        };
        pi v{0, 0};
        auto &[place, sum] = v;
        int t = go(place, sum, go);
        if(t == -1){
            cout << -1 << "\n";
            continue;
        }
        rep(i, 0, m){
            t = go(place, sum, go);
            res[i] = t;
            if(res[i]) sum = (sum + n - cnt[i]) / 2;
            else sum = (sum + cnt[i]) / 2;
            place++;
        }
        reverse(all(res));
        rep(i,0,m) cout << res[i];
        cout << "\n";
    }
    
    return 0;
}
