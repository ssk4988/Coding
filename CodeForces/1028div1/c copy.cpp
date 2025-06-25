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
        int n, m, intprob; cin >> n >> m >> intprob;
        double p = intprob / 100.0;
        double q = 1 - p;
        vi h(n);
        int minh = 500;
        rep(i, 0, n) {
            cin >> h[i];
            minh = min(minh, h[i]);
        }
        int maxnotshine = 0;
        rep(i, 0, n) maxnotshine += h[i] - minh;
        maxnotshine = min(maxnotshine, m);
        int maxshine = minh - 1;
        vector phase1(m+1, vector<double>(maxshine+1, -1));
        vector phase2(m+1, vector<double>(maxnotshine+1, -1));
        vector phase3(m+1, vector(maxshine+1, vector<double>(n+1, -1)));
        auto go3 = [&](int used, int shines, int above, auto &&go3) -> double {
            if(shines == maxshine && above == 0) return 1;
            if(used >= m) return 0;
            auto &ans = phase3[used][shines][above];
            if(ans != -1) return ans;
            ans = 0;
            {
                // shine
                if(shines < maxshine) ans += p * max(go3(used+1, shines+1, above, go3), go3(used+1, shines, above, go3));
                else ans += p * go3(used+1, shines, above, go3);
            }
            {
                // not shine
                int nabove = above > 0 ? above-1 : n-1;
                int nshines = above > 0 ? shines : shines+1;
                ans += q * max(go3(used+1, shines, above, go3), go3(used+1, nshines, nabove, go3));
            }
            return ans;
        };
        auto go2 = [&](int used, int notshine, auto &&go2) -> double {
            if(notshine == maxnotshine) return 1;
            if(used >= m) return 0;
            auto &ans = phase2[used][notshine];
            if(ans != -1) return ans;
            ans = p * go2(used+1, notshine, go2) + q * go2(used+1, notshine+1, go2);
            return ans;
        };
        auto go1 = [&](int used, int shine, auto &&go1) -> double {
            int notshine = used - shine;
            if(shine == maxshine) {
                return go2(used, notshine, go2);
            }
            if(notshine == maxnotshine) {
                return go3(used, shine, 0, go3);
            }
            if(used >= m) return 0;
            auto& ans = phase1[used][shine];
            if(ans != -1) return ans;
            ans = p * go1(used+1, shine+1, go1) + q * (go1(used+1, shine, go1));
            return ans;
        };
        cout << fixed << setprecision(8) << go1(0, 0, go1) << "\n";
    }
    
    return 0;
}
