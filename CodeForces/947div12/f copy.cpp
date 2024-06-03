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
    vi mask(1 << n);
    rep(i, 1, sz(mask)){
        cin >> mask[i];
    }
    vector<vvi> works(n+1, vvi(n));
    vector<vvi> subs(n+1, vvi(n));
    rep(mask, 1, 1 << n){
        int h = __lg(mask);
        int l = __lg(mask & -mask);
        subs[h - l + 1][l].pb(mask);
        // cout << mask << " " << l << " " << h << "\n";
    }
    // length, starting of lsb, mask used
    rep(i, 0, n){
        works[1][i].resize(2);
        works[1][i][0] = (mask[1 << i]) & 1;
        works[1][i][1] = (mask[1 << i]) & 2;
    }

    rep(len, 2, n+1){
        int submask = (1 << len) - 1;
        rep(start, 0, n){
            if(start + len > n) break;
            works[len][start].resize(1 << len);
            rep(bits, 0, sz(works[len][start])){
                bool b1 = works[len-1][start][bits & ((1 << (len-1))-1)];
                bool b2 = works[len-1][start+1][bits >> 1];
                int cnt = __builtin_popcount(bits);
                bool b3 = true;
                for(int sub : subs[len][start]){
                    b3 = b3 && (mask[sub] & (1 << __builtin_popcount(sub & bits)));
                }
                works[len][start][bits] = b1 && b2 && b3;
            }
            submask <<= 1;
        }
    }
    vi ans;
    rep(bits, 0, sz(works[n][0])){
        if(works[n][0][bits]){
            ans.pb(bits);
        }
    }
    cout << sz(ans) << "\n";
    for(int i : ans){
        cout << i << "\n";
    }

    return 0;
}
