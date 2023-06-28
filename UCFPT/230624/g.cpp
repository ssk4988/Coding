#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll mx; cin >> mx;
    string str; cin >> str;
    int n = sz(str);
    vvi pref(n, vi(26));
    rep(i, 0, n){
        pref[i][str[i] - 'A']++;
    }
    rep(i, 1, n){
        rep(j, 0, 26) pref[i][j] += pref[i - 1][j];
    }
    int k; cin >> k;
    rep(i, 0, k){
        ll row; cin >> row;
        char c; cin >> c;
        ll offset = 1;
        // row == 1?
        if(row % 2 == 1){
            offset = (row - 1) / 2;
            offset %= n;
            offset = (offset * (row % n)) % n;
        }
        else{
            offset = row / 2;
            offset %= n;
            offset = (offset * ((row - 1) % n)) % n;
        }
        ll occ = row / n;
        ll ans = occ * pref.back()[c - 'A'];
        ll len = row % n;
        if(len){
            ll r = (offset + len - 1) % n, l = offset;
            ll rem = pref[r][c - 'A'];
            if(l > 0) rem -= pref[l - 1][c - 'A'];
            if(l <= r){
            }
            else{
                rem += pref.back()[c - 'A'];
            }

            ans += rem;
        }
        cout << ans << "\n";
    }
}
