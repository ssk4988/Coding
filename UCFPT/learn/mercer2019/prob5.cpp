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
    rep(cn, 0, nc) {
        string s; int f, k, d; cin >> s >> f >> k >> d;
        int n = sz(s);
        vi ans;
        vi seen(n);
        vi cnt(max(0, n-k+1));
        vi lim(sz(cnt));
        rep(i, 0, n-k+1) {
            if(i >= lim[i]) {
                cnt[i]++;
                lim[i] = i + k;
            }
            rep(j, i+1, n-k+1) {
                int dist = 0;
                rep(l, 0, k) {
                    dist += s[i+l] != s[j+l];
                }
                if(dist <= d) 
                {
                    if(lim[i] <= j) {
                        cnt[i]++;
                        lim[i] = j + k;
                    }
                    if(lim[j] <= i) {
                        cnt[j]++;
                        lim[j] = i + k;
                    }
                }
                if(dist == 0) seen[j] = true;
            }
            if(!seen[i] && cnt[i] >= f) {
                ans.pb(i);
            }
        }
        if(sz(ans) == 0) {
            cout << "No motif found\n\n";
            continue;
        }
        for(int i : ans) cout << s.substr(i, k) << " ";
        cout << "\n\n";
    }
    
    return 0;
}
