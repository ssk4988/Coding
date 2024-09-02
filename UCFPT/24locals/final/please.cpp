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
    vi priorset;
    rep(i, 0, n){
        cin >> grade[i];
        string l; cin >> l;
        letter[i] = l[0] - 'A';
        if(l[0] == 'F') letter[i] = 4;
        cin >> ps[i];
        priorset.pb(ps[i]);
    }
    sort(all(priorset));
    reverse(all(priorset));
    map<int, int> priormp;
    for(int p : priorset){
        if(!priormp.count(p)) priormp[p] = sz(priormp);
    }
    vector<vvi> students(5, vvi(101));
    rep(i, 0, n) {
        ps[i] = priormp[ps[i]];
        students[letter[i]][grade[i]].pb(ps[i]);
    }
    vector dp(5, vvi(101));
    // dp[i][j] = {scores, A, B, C, D};
    // i = grade, j = grade boundary
    // dp[i][j] = add students[i][j] + max(dp[i][j-1], dp[i+1][j-1])
    auto go = [&](int l, int g, auto &&go) -> vi {
        if(sz(dp[l][g])) return dp[l][g];
        dp[l][g] = vi(sz(priormp)+4);
        for(int i : students[l][g]) dp[l][g][i]++;
        // if(l == 4) return dp[l][g];
        // if(g == 0) {
        //     assert(false);
        // }
        if(l < 4) dp[l][g][sz(priormp)+l] = g;
        if(l < 4 && g > 0){
            // next letter grade
            vi cur = go(l+1, g-1, go);
            for(int i : students[l][g]) cur[i]++;
            cur[sz(priormp)+l] = g;
            dp[l][g] = max(dp[l][g], cur);
        }
        if(l + g > 4) {
            vi cur = go(l, g-1, go);
            for(int i : students[l][g]) cur[i]++;
            dp[l][g] = max(dp[l][g], cur);
        }
        return dp[l][g];
    };
    auto res = go(0, 100, go);
    rep(i, sz(priormp), sz(res)){
        cout << res[i];
        if(i + 1 < sz(res)) cout << " ";
    }
    cout << "\n";


    
    return 0;
}
