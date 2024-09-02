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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi grade(n), letter(n), ps(n);
    rep(i, 0, n){
        cin >> grade[i];
        string l; cin >> l;
        letter[i] = l[0] - 'A';
        if(l[0] == 'F') letter[i] = 4;
        cin >> ps[i];
    }
    vi plist(ps);
    sort(all(plist));
    plist.erase(unique(all(plist)), plist.end());
    reverse(all(plist));
    vector<vvi> students(5, vvi(101)), dp(5, vvi(101));
    rep(i, 0, n) {
        ps[i] = find(all(plist), ps[i]) - plist.begin();
        students[letter[i]][grade[i]].pb(ps[i]);
    }
    // dp[i][j] = {scores, A, B, C, D};
    // i = grade, j = grade boundary
    // dp[i][j] = add students[i][j] + max(dp[i][j-1], dp[i+1][j-1])
    auto go = [&](int l, int g, auto &&go) -> vi {
        if(sz(dp[l][g])) return dp[l][g];
        dp[l][g] = vi(sz(plist)+4);
        for(int i : students[l][g]) dp[l][g][i]++;
        if(l < 4) dp[l][g][sz(plist)+l] = g;
        if(l < 4 && g > 0){
            // next letter grade
            vi cur = go(l+1, g-1, go);
            for(int i : students[l][g]) cur[i]++;
            cur[sz(plist)+l] = g;
            dp[l][g] = max(dp[l][g], cur);
        }
        if(l + g > 4) {
            // move boundary down
            vi cur = go(l, g-1, go);
            for(int i : students[l][g]) cur[i]++;
            dp[l][g] = max(dp[l][g], cur);
        }
        return dp[l][g];
    };
    auto res = go(0, 100, go);
    rep(i, sz(plist), sz(res)){
        cout << res[i] << " \n"[i+1 == sz(res)];
    }
    
    return 0;
}
