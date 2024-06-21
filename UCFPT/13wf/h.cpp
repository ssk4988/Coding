#include <bits/stdc++.h>
using namespace std;


using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;


#define rep(i,a,b) for(int i =a; i < (b); i++)
#define sz(x)(int)x.size()
#define all(x) begin(x), end(x)

const int N = 505;
int cost[N][N][N];
int pref[N];


int main(){
    cin.tie(0)->sync_with_stdio(0);
    int n;
    while(cin >> n){
        vi a(n);
        // COORD COMPRESS
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
        }
        vi b(a);
        sort(all(b));
        b.erase(unique(all(b)), b.end());
        rep(i, 0, n){
            a[i] = lower_bound(all(b), a[i]) - b.begin();
        }
        rep(i, 0, n){
            rep(j, i, n){
                int cmn = INT_MAX;
                rep(k, 0, n+1) pref[k] = 0;
                rep(k, i, j+1) {
                    pref[a[k]]++;
                    cmn = min(cmn, a[k]);
                }
                rep(k, 1, n+1) pref[k] += pref[k-1];
                {
                    int mn = INT_MAX;
                    rep(k, j+1, n){
                        mn = min(mn, a[k]);
                        if(mn < cmn) break;
                        cost[i][j][k] = k - i + 1 - pref[mn];
                        // cout << i << "," << j << "," << k << " is " << cost[i][j][k] << "\n";
                    }
                }
                {
                    int mn = INT_MAX;
                    for(int k = i-1; k >= 0; k--){
                        mn = min(mn, a[k]);
                        if(mn < cmn) break;
                        cost[k][i-1][j] = j - k + 1 - pref[mn];
                    }
                }
            }
        }
        vvi dp(n, vi(n));
        for(int l = n-1; l >= 0; l--){
            for(int r = l; r < n; r++){
                if(l == r) {dp[l][r] = 0; continue;}
                dp[l][r] = INT_MAX;
                rep(l1, l+1, r+1){
                    dp[l][r] = min(dp[l][r], dp[l][l1-1] + dp[l1][r] + cost[l][l1-1][r]);
                }
            }
        }
        const ll oo = 1e18;
        vl part(n+1, 1e18);
        part[0] = 0;
        rep(i, 0, n){
            int mx = INT_MIN;
            set<int> ss;
            rep(j, i, n){
                mx = max(mx, a[j]);
                ss.insert(a[j]);
                if(j - i == mx && sz(ss) == j - i + 1){
                    // cout << i << " to " << j << " is a permutation: " << dp[i][j] << "\n";

                    part[j+1] = min(part[j+1], part[i] + dp[i][j]);
                }
            }
        }
        if(part[n] == oo){
            cout << "impossible\n";
        } else cout << part[n] << "\n";
    }


    return 0;
}
