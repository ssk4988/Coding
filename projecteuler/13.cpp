#include <bits/stdc++.h>
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
    vi res(80);
    vector<string> s(100);
    rep(i, 0, 100) cin >> s[i];
    rep(i, 0, 100) reverse(all(s[i]));
    rep(i, 0, 100){
        rep(j, 0, 50){
            res[j] += s[i][j] - '0';
        }
    }
    rep(i, 0, sz(res) - 1){
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    reverse(all(res));
    bool valid = false;
    int cnt = 0;
    rep(i, 0, sz(res)){
        if(res[i] != 0) valid = true;
        if(valid){
            cout << res[i];
            cnt++;
            if(cnt == 10) break;
        }
    }
    cout << nL;
    
    return 0;
}
