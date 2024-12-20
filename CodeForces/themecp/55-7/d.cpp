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

const int B = 300;
const int N = 1e5 + 10;
const int blocks = N / B + 5;
int blockcnt[blocks];
vi at[blocks * B + 10];
const int inf = 1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi a(n);
        vi div(n, k);
        auto ins = [&](int i) -> void {
            blockcnt[(a[i] / div[i]) / B]++;
            at[(a[i] / div[i])].pb(i);
        };
        rep(i, 0, n){
            cin >> a[i];
            ins(i);
        }
        auto getmx = [&]() {
            for(int i = blocks-1; i >= 0; i--){
                if(blockcnt[i]) {
                    for(int j = B-1; j >= 0; j--) {
                        if(sz(at[i * B + j])) return i * B + j;
                    }
                }
            }
            return -1;
        };
        auto getmn = [&]() {
            rep(i, 0, blocks) {
                if(blockcnt[i]) {
                    rep(j, 0, B) if(sz(at[i * B + j])) return i * B + j;
                }
            }
            return inf;
        };
        int ans = inf;
        int tot = n;
        while(tot == n){
            int mn = getmn();
            int mx = getmx();
            // if(mn > mx) break;
            ans = min(ans, mx - mn);
            for(int i : at[mn]){
                tot--;
                blockcnt[mn / B]--;
                div[i] = a[i] / ((a[i] / div[i]) + 1);
                if(div[i] > 0) {
                    tot++;
                    assert(a[i] / div[i] != mn);
                    ins(i);
                }
            }
            at[mn] = vi();
        }
        cout << ans << "\n";
        rep(i, 0, n){
            if(div[i]) at[a[i] / div[i]].clear();
        }
        rep(i, 0, blocks) blockcnt[i] = 0;
    }
    
    return 0;
}
