#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"
#define bitat(x, a) (((x) >> (a)) & 1)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        vvi solve(n, vi(m));
        rep(i, 0, n){
            string str; cin >> str;
            rep(j, 0, m){
                solve[i][j] = str[j] - '0';
            }
        }
        pair<ll, vi> best = {-1, {}};
        // bit on means we exceed
        rep(mask, 0, 1 << n){
            vvi frq(m, vi(2)); // 1 means increases score
            vi order(m);
            rep(i, 0, n){
                rep(j, 0, m){
                    frq[j][solve[i][j] ^ 1 ^ bitat(mask, i)]++;
                }
            }
            iota(all(order), 0);
            sort(all(order), [&](int a, int b) -> bool { return frq[a][1] < frq[b][1]; });
            vl sc(n);
            rep(j, 0, m){
                rep(i, 0, n){
                    sc[i] += solve[i][order[j]] * (1 + j);
                }
            }
            ll score = 0;
            rep(i, 0, n) score += abs(a[i] - sc[i]);
            best = max(best, {score, order});
        }
        vi rev(m);
        rep(i, 0, m){
            rev[best.s[i]] = i;
        }
        // cout << best.f << " ";
        rep(i, 0, m){
            cout << (rev[i] + 1) << " ";
        }
        cout << nL;
    }
    
    return 0;
}
