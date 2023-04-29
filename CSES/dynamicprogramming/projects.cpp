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
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi proj;
    set< int> freq;
    rep(i, 0, n){
        int a, b, p;
        cin >> a >> b >> p;
        proj.pb({a, b, p});
        freq.insert(a);
        freq.insert(b);
    }
    sort(all(proj));
    int cnt = 5;
    map<int, int> label;
    for(int i : freq){
        label[i] = cnt++;
    }
    rep(i, 0, n){
        proj[i][0] = label[proj[i][0]];
        proj[i][1] = label[proj[i][1]];
        proj[i][1]++;
    }
    vl dp(cnt + 10);
    int pnter = 0;
    rep(i, 0, sz(dp)){
        if(i > 0){
            dp[i] = max(dp[i], dp[i - 1]);
        }
        while(pnter < n && proj[pnter][0] == i){
            dp[proj[pnter][1]] = max(dp[proj[pnter][1]], dp[i] + proj[pnter][2]);
            pnter++;
        }
    }
    cout << dp.back() << nL;


    return 0;
}