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

/*
1 - 1
11 - 0
111 - 01, 10
1111 - 1
11111 - 0
111111 - 10, 01
1111111 - 1

pattern is same, other, two repeating for length 3
11 - 0
110 - 1
1100 - 10
11000 - 0
110000 - 1


10 - 10
100 - 0
1000 - 1
1110 - 0
111

freq0 - freq 1 must not be 0 mod 3

only things that correctly reduce are 

111110


 01001
020212


101010101
011010101
00010101
0110101
000101
01101
0001
011
00
1

remove cases that are full alternating and odd length
*/

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        string s; cin >> s;
        vl cnt(3);
        int p = 0;
        cnt[p]++;
        ll ans = ll(n+1) * (n+2) / 2;
        int alter = 0;
        rep(i, 0, n) {
            if(s[i] == '0') p++;
            else p--;
            p += 3;
            p %= 3;
            cnt[p]++;
            if(i > 0 && s[i] == s[i-1]) alter = 0;
            alter++;
            ans -= (alter-1)/2;
        }
        rep(i, 0, 3) ans -= cnt[i] * (cnt[i]+1) / 2;
        cout << ans << "\n";
    }
    
    return 0;
}
