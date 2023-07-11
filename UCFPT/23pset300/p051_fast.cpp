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
using vvl = vector<vl>;

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
    ll l, r, q; cin >> l >> r >> q;
    // l--,r--;
    ll maxv = 1e18 + 1e17;
    vector<vvi> childs(q + 1, vvi(26));
    vector<vvl> pref(q + 1, vvl(26));
    vector<vpi> skip(q + 1, vpi(26));

    rep(i, 0, q){
        char c; string str; cin >> c >> str;
        rep(j, 0, sz(str)){
            childs[i][c - 'a'].pb(str[j] - 'a');
        }
        rep(j, 0, 26){
            if(sz(childs[i][j])) continue;
            childs[i][j].pb(j);
        }
    }
    rep(i, 0, 26){
        pref[q][i].pb(1);
        rep(j, 0, q + 1){
            skip[j][i] = {j, i};
        }
    }
    for(int i = q - 1; i >= 0; i--){
        rep(j, 0, 26){
            for(int k : childs[i][j]){
                pref[i][j].pb(min(maxv,(sz(pref[i][j]) == 0 ? 0 : pref[i][j].back()) + pref[i + 1][k].back()));
            }
            if(sz(childs[i][j]) == 1){
                skip[i][j] = skip[i + 1][childs[i][j][0]];
            }
        }
    }
    auto dfs = [&](int level, int c, ll l, ll r, auto &&dfs)->void{
        if(level == q){
            cout << char('a' + c);
            return;
        }
        if(sz(childs[level][c]) == 1){
            auto [level1, c1] = skip[level][c];
            dfs(level1, c1, l, r, dfs);
            return;
        }
        int lo = -1, hi = sz(childs[level][c]) - 1;
        while(lo < hi){
            int mid = lo + (hi - lo + 1) / 2;
            if(pref[level][c][mid] < l){
                lo = mid;
            }
            else hi = mid - 1;
        }
        ll pre = lo == -1 ? 0 : pref[level][c][lo];
        rep(i, lo + 1, sz(childs[level][c])){
            if(pre < r){
                dfs(level + 1, childs[level][c][i], l - pre, r - pre, dfs);
                pre = pref[level][c][i];
            }
            else break;
        }
    };
    dfs(0, 0, l, r, dfs);
    // vi trav;
    // vi c;
    // c.pb(0);
    // ll lef = l;
    // for(ll i = l; i <= r; i++){
    //     if(i > l){
    //         lef++;
    //         while(lef > pref[sz(trav)][c.back()].back()){
    //             c.pop_back();
    //             if(trav.back() > 0){
    //                 lef += pref[sz(trav) - 1][c.back()][trav.back() - 1];
    //             }
    //             trav.pop_back();
    //         }
    //     }
    //     while(size(trav) < q){
    //         int lo = 0, hi = sz(pref[sz(trav)][c.back()]) - 1;
    //         while(lo < hi){
    //             int mid = lo + (hi - lo) / 2;
    //             if(pref[sz(trav)][c.back()][mid] >= lef){
    //                 hi = mid;
    //             }else lo = mid + 1;
    //         }
    //         if(lo > 0){
    //             lef -= pref[sz(trav)][c.back()][lo - 1];
    //         }
    //         c.pb(childs[sz(trav)][c.back()][lo]);
    //         trav.pb(lo);
    //     }
    //     cout << char('a' + c.back());
    // }
    cout << nL;

    
    return 0;
}