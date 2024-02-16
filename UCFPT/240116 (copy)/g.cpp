#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string str; cin >> str;
    vvi pref(3, vi(n));
    vi cnt(3);
    rep(i, 0, n){
        pref[str[i] - 'A'][i]++;
        cnt[str[i] - 'A']++;
    }
    rep(i, 0, 3){
        rep(j, 1, n){
            pref[i][j] += pref[i][j-1];
        }
    }
    // [l,r]
    auto rangesum = [&](int i, int l, int r) -> int {
        if(l > r){
            return pref[i].back() - pref[i][l-1] + pref[i][r];
        }
        return pref[i][r] - (l > 0 ? pref[i][l-1] : 0);
    };
    vi perm = {0, 1, 2};
    int res = 1e9;
    rep(i, 0, n){
        do {
            int start = i;
            int ans = 0;
            rep(j, 0, 3){
                ans += cnt[perm[j]] - rangesum(perm[j], start, (start + cnt[perm[j]] - 1) % n);
                start = (start + cnt[perm[j]]) % n;
            }
            res = min(res, ans);
        }
        while(next_permutation(all(perm)));
    }
    cout << res << "\n";

    return 0;
}