#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ld = long double;

vi Z(vi &S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while(i + z[i] < sz(S) && S[i + z[i]] == S[z[i]])
            z[i]++;
        if(i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}
const int SCALE = 10000;
const int ANGLES = 360 * SCALE;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<vii> pts(2, vii(n));
    vi cnt(ANGLES);
    rep(t, 0, 2){
        rep(i, 0, n){
            ld x, y;
            string a, b; cin >> a >> b;
            x = stold(a), y = stold(b);
            x *= SCALE, y *= SCALE;
            pts[t][i] = {int(roundl(x)), int(roundl(y))};
        }
        sort(all(pts[t]));
    }
    {
        bool works = true;
        rep(i, 0, n){
            if(pts[0][i].first != pts[1][i].first) works = false;
        }
        if(!works){
            cout << "Different\n";
            return 0;
        }
    }
    int l = 0, r = 0;
    int difftypes = 0;
    while(l < n){
        difftypes++;
        while(r < n && pts[0][r].first == pts[0][l].first) r++;
        vvi diffs(2);
        rep(t, 0, 2){
            rep(i, l, r-1) {
                diffs[t].push_back(pts[t][i+1].second - pts[t][i].second);
            }
            diffs[t].push_back(pts[t][l].second - pts[t][r-1].second + ANGLES);
        }
        diffs[0].push_back(INT_MAX);
        int ref = sz(diffs[0]);
        diffs[0].insert(diffs[0].end(), all(diffs[1]));
        diffs[0].insert(diffs[0].end(), all(diffs[1]));
        vi z = Z(diffs[0]);
        set<int> angles;
        rep(i, 0, r-l){
            // cout << diffs[0][i] << " " << diffs[1][i] << "\n";
            if(z[ref + i] >= r-l){
                int angle = pts[1][i + l].second - pts[0][l].second;
                while(angle < 0) angle += ANGLES;
                // cnt[angle]++;
                angles.insert(angle);
                // cout << angle << "\n";
            }
        }
        for(int angle : angles) cnt[angle]++;

        l = r;
    }
    bool works = false;
    rep(i, 0, ANGLES){
        if(cnt[i] == difftypes){
            works = true;
        }
    }
    cout << (works ? "Same" : "Different") << "\n";


    return 0;
}
