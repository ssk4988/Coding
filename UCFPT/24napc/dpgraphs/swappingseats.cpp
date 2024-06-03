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
    string str; cin >> str;
    int n = sz(str);
    vvi pref(3, vi(n+1));
    rep(i, 0, 3){
        rep(j, 0, n)
        pref[i][j+1] = pref[i][j] + (str[j] == 'A' + i);
    }
    int a = pref[0][n], b = pref[1][n], c = pref[2][n];
    auto sum = [&](int l, int r, int c) -> int {
        if(l <= r) return pref[c][r] - pref[c][l];
        return pref[c][n] - pref[c][l] + pref[c][r];
    };
    int best = 1e9;
    rep(t, 0, 2){
        rep(i, 0, n){
            vvi trans(3, vi(3));
            int start = i;
            rep(j, 0, 3){
                int nex = (start + pref[j][n]) % n;
                rep(k, 0, 3) trans[j][k] = sum(start, nex, k);
                start = nex;
            }
            int ans = 0;
            rep(j, 0, 3){
                rep(k, 0, j){
                    int rem = min(trans[j][k], trans[k][j]);
                    trans[j][k] -= rem, trans[k][j] -= rem;
                    ans += rem;
                }
            }
            ans += 2 * (trans[0][1] + trans[1][0]);
            best = min(ans, best);
        }
        swap(pref[1], pref[2]);
    }
    cout << best << "\n";
    
    return 0;
}
