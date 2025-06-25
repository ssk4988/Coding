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
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    const int LIM = 3e5+10;
    vi mobius(LIM);
    mobius[1] = 1;
    vvi mobdivs(LIM), divs(LIM);
    rep(i, 1, LIM) {
        if(mobius[i] == 0) continue;
        mobdivs[i].push_back(i);
        for(int j = 2 * i; j < LIM; j += i){
            mobius[j] -= mobius[i];
            mobdivs[j].push_back(i);
        }
    }
    rep(i, 1, LIM) {
        for(int j = i; j < LIM; j += i) divs[j].push_back(i);
    }
    vi q(a);
    sort(all(q));
    q.erase(unique(all(q)), end(q));
    vi ans(sz(q), 0);
    for(int dif = 1 << 18; dif; dif /= 2) {
        vvi buckets(LIM);
        rep(i, 0, sz(q)) {
            if(ans[i] + dif < LIM)
            buckets[ans[i] + dif].push_back(i);
        }
        vi cnt(LIM);
        int p = sz(q)-1;
        for(int i = LIM-1; i >= 0; i--) {
            if(p >= 0 && q[p] == i) {
                // cerr << "add " << i << endl;
                for(int d : mobdivs[i]) {
                    cnt[d]++;
                }
                p--;
            }
            for(int j : buckets[i]) {
                int cur = 0;
                for(int d : mobdivs[q[j]]) {
                    cur += cnt[d] * mobius[d];
                }
                // cerr << "process " << j << " is " << q[j] << " at " << i << " cnt is " << cur << endl;
                if(cur != 0) {
                    ans[j] += dif;
                }
            }
            // if(sz(buckets[i])) rep(k, 0, 10) cerr << "k=" << k << " " << cnt[k] << endl;
        }
    }
    rep(i, 0, n) {
        int idx = lower_bound(all(q), a[i]) - begin(q);
        cout << ans[idx] << " ";
    }
    cout << "\n";
    
    
    return 0;
}
