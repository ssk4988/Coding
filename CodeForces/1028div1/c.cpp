#include <bits/stdc++.h>
using namespace std;

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

const int M = 4000;
const int MS = 400;
const int MNS = 4000;
const int N = 20;
double phase1[M+1][MS+1], phase2[M+1][MNS+1], phase3[M+1][MS+1][N+1];

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
        if(maxnotshine > m) {
            cout << fixed << setprecision(8) << double(0) << "\n";
            continue;
        }
        // maxnotshine = min(maxnotshine, m);
        int maxshine = minh - 1;
        // vector phase1(m+1, vector<double>(maxshine+1));
        // vector phase2(m+1, vector<double>(maxnotshine+1));
        // vector phase3(m+1, vector(maxshine+1, vector<double>(n+1)));
        rep(shines, 0, maxshine+1) {
            rep(above, 0, n+1) phase3[m][shines][above] = 0;
        }
        rep(used, 0, m+1) {
            phase3[used][maxshine][0] = 1;
        }
        for(int used = m-1; used >= 0; used--) {
            rep(shines, 0, maxshine+1) {
                rep(above, 0, n+1) {
                    if(shines == maxshine && above == 0) continue;
                    auto &ans = phase3[used][shines][above];
                    ans = 0;
                    {
                        // shine
                        if(shines < maxshine) ans += p * max(phase3[used+1][shines+1][above], phase3[used+1][shines][above]);
                        else ans += p * phase3[used+1][shines][above];
                    }
                    {
                        // not shine
                        int nabove = above > 0 ? above-1 : n-1;
                        int nshines = above > 0 ? shines : shines+1;
                        ans += q * max(phase3[used+1][shines][above], phase3[used+1][nshines][nabove]);
                    }
                }
            }
        }
        rep(notshine, 0, maxnotshine+1) {
            phase2[m][notshine] = 0;
        }
        phase2[m][maxnotshine] = 1;
        for(int used = m-1; used >= 0; used--) {
            phase2[used][maxnotshine] = 1;
            rep(notshine, 0, maxnotshine) {
                phase2[used][notshine] = p * phase2[used+1][notshine] + q * phase2[used+1][notshine+1];
            }
        }
        for(int used = m; used >= 0; used--) {
            rep(shine, 0, maxshine+1) {
                int notshine = used - shine;
                if(notshine < 0) continue;
                if(notshine > maxnotshine) continue;
                auto &ans = phase1[used][shine];
                if(shine == maxshine) {
                    ans = phase2[used][notshine];
                }
                else if(notshine == maxnotshine) {
                    ans = phase3[used][shine][0];
                } else if(used == m) ans = 0;
                else {
                    ans = p * phase1[used+1][shine+1] + q * phase1[used+1][shine];
                }
            }
        }
        cout << fixed << setprecision(8) << phase1[0][0] << "\n";
    }
    
    return 0;
}
