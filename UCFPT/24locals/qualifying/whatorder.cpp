#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using ld = long double;
using ll = long long;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, c; cin >> n >> c;
    vi perm(n);
    iota(all(perm), 0);
    vector<array<int, 3>> r(c);
    rep(i, 0, c){
        cin >> r[i][0];
        string a, b; cin >> a >> b;
        r[i][1] = a[0] - 'A', r[i][2] = b[0] - 'A';
    }
    int cnt = 0;
    do {
        vi inv(n);
        rep(i, 0, n) inv[perm[i]] = i;
        bool works = true;
        for(auto [t, a, b] : r){
            if(t == 1) works = works && inv[a] < inv[b];
            if(t == 2) works = works && inv[a] > inv[b];
            if(t == 3) works = works && abs(inv[a] - inv[b]) > 1;
        }
        cnt += works;
    } while(next_permutation(all(perm)));
    cout << cnt << "\n";

    return 0;
}
