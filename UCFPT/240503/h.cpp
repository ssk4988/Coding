#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

vi Z(string S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while(i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string s; cin >> s;
    int n = sz(s);
    string s2 = s + s;
    vi z = Z(s2);
    int per = n;
    rep(i, 1, n + 1){
        if(z[i] >= n) {
            per = i;
            break;
        }
    }
    int revind0 = -1;
    string r = s;
    reverse(all(r));
    string r2 = s + '$' + r + r;
    z = Z(r2);
    rep(i, 0, n){
        if(z[n + 1 + i] >= n){
            revind0 = i;
            break;
        }

    }
    // cout << per << " " << revind0 << "\n";
    // return 0;
    int flips = 1; // 1 for not reversed
    int ind0 = 0;
    ll ans = 0;
    vvi cnt(3, vi(per));
    cnt[flips + 1][ind0]++;
    int k; cin >> k;
    rep(i, 0, k){
        char c; cin >> c;
        if(c == 'I'){
            flips *= -1;
            if(revind0 != -1) swap(revind0, ind0);
            else ind0 = per - 1 - ind0;
        }
        else{
            int d; cin >> d;
            d %= per;
            if(c == 'L') d = (-d + per) % per;
            ind0 = (d + ind0) % per;
            if(revind0 != -1) revind0 = (-d + per + revind0) % per;
        }
        ans += cnt[flips + 1][ind0];
        if(revind0 != -1) ans += cnt[-flips + 1][revind0];
        // cout << flips << " " << ind0 << " " << revind0 << "\n";
        cnt[flips + 1][ind0]++;

    }
    cout << ans << "\n";


    return 0;
}
