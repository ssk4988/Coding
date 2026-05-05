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

const int lim = 2e6+1;
using bs = bitset<2*lim+1>;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    vi freq(lim);

    // set<int> cur;
    // cur.insert(0);
    bs cur;
    cur[lim] = 1;
    rep(i, 0, n) {
        cin >> a[i];
        freq[a[i]]++;
        // set<int> nxt;
        // for(int x : cur) {
        //     nxt.insert(x);
        //     nxt.insert(abs(x-a[i]));
        //     nxt.insert(x+a[i]);
        // }
        // cur = nxt;
    }
    rep(i, 0, lim) {
        int amt = (freq[i]-1)/2;
        freq[i] -= 2 * amt;
        if(amt) freq[2*i] += amt;
        while(freq[i]) {
            cur = cur | (cur << i) | (cur >> i);
            freq[i]--;
        }
    }
    cur >>= lim;
    cout << cur.count() << "\n";

    // for(int x : cur) cout << x << ",";
    // cout << "\n";
    
    return 0;
}
