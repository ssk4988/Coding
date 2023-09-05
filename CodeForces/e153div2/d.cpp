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

int main()
{
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    int n = sz(s);
    vi a(n), cnt(2);
    rep(i, 0, n){
        a[i] = s[i] - '0';
        cnt[a[i]]++;
    }
    const int BAD = INT_MAX;
    const int d = 2 * 100 * 100 + 100;
    int start = 100 * 100 + 50;
    vector<vvi> dp(cnt[0] + 1, vvi(cnt[1] + 1, vi(d, BAD)));
    dp[0][0][start] = 0;
    rep(i, 0, n){
        rep(j, 0, i + 1){
            int i0 = j, i1 = i - j;
            if(i0 > cnt[0] || i1 > cnt[1]) continue;
            rep(k, 0, d){
                // if(i0 == 1 && i1 == 1 && k >= 20099) 
                //     cout << "seen " << i0 << " " << i1 << " " << (k - start) << " " << k << nL;
                if(dp[i0][i1][k] == BAD) continue;

                if(i0 < cnt[0]){
                    dp[i0 + 1][i1][k + i1] = min(dp[i0][i1][k] + (a[i0 + i1] != 0), dp[i0 + 1][i1][k + i1]);
                }
                if(i1 < cnt[1]){
                    dp[i0][i1 + 1][k - i0] = min(dp[i0][i1][k] + (a[i0 + i1] != 1), dp[i0][i1 + 1][k - i0]);
                }
            }
        }
    }
    int ans = dp[cnt[0]][cnt[1]][start] / 2;
    cout << ans << nL;

    
    return 0;
}
