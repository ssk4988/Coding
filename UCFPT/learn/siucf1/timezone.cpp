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
    int nc; cin >> nc;
    map<string, int> zone = {
        {"DE", 0},
        {"FL",0},{"NJ",0},{"ON",0},{"VA",0},
        {"MO",1},{"TX",1},{"WI",1},
        {"CO",2},
        {"CA",3}
    };
    rep(cn, 0, nc) {
        int h; string b, s, t; cin >> h >> b >> s >> t;
        if(h == 12) h = 0;
        if(b[0] == 'P') h += 12;
        h += zone[s];
        h -= zone[t];
        (h += 24) %= 24;
        cout << (h % 12 == 0 ? 12 : h%12) << " " << (h >= 12 ? "PM" : "AM") << "\n";
    }
    
    return 0;
}
