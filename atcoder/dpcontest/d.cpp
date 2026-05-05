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
        string s; cin >> s;
        vi dig;
        while(sz(s)) dig.push_back(s.back() - '0'), s.pop_back();
        dig.resize(21);
        // for(auto d : dig) cout << d << ",";
        // cout << "\n";
        vector dp(sz(dig), vi(2, -1));
        auto go = [&](int place, int carry, auto &&go) -> int {
            if(place == -1) {
                if(carry) return 1e9;
                return 0;
            }
            auto &ans = dp[place][carry];
            if(ans != -1) return ans;
            ans = 1e9;
            rep(d, 0, 10) {
                {
                    // stop carry
                    int over = d + dig[place];
                    if((over >= 10) == carry) {
                        ans = min(ans, over % 10 + d + go(place-1, false, go));
                    }
                }
                if(carry){
                    // continue
                    int over = (d + dig[place] + 1);
                    if(over >= 10) ans = min(ans, over % 10 + d + go(place-1, true, go));
                }
                else if(dig[place] + d < 9) {
                    // start
                    int over = dig[place]+ d + 1;
                    ans = min(ans, over + d + go(place-1, true, go));
                }
            }
            return ans;
        };
        cout << go(sz(dig)-1, false, go) << "\n";
    }
    
    return 0;
}
