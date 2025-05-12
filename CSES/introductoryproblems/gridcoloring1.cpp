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
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi grid(n, vi(m));
    vvi res(n, vi(m));
    rep(i, 0, n) {
        string s; cin >> s;
        rep(j, 0, m) {
            grid[i][j] = s[j] - 'A';
            vi bad(4);
            if(i) bad[res[i-1][j]] = 1;
            if(j) bad[res[i][j-1]] = 1;
            bad[grid[i][j]] = 1;
            rep(k, 0, 4) {
                if(!bad[k]) res[i][j] = k;
            }
            cout << char('A' + res[i][j]);
        }
        cout << "\n";
    }
    
    return 0;
}
