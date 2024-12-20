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

ll solve2(vi &a) {
    int n = sz(a);
    map<vi, ll> dp;
    ll ans = 0;
    rep(t, 0, n){
        map<vi, ll> new_dp;
        for(auto &[key, val] : dp) {
            bool done = false;
            vi seq(key);
            rep(i, 0, sz(seq)){
                if(seq[i] & a[t]){
                    seq[i] = a[t];
                    done = true;
                    break;
                }
            }
            if(!done && a[t] != 0) seq.pb(a[t]);
            new_dp[seq] += val;
        }
        if(a[t] == 0){
            new_dp[vi{}] += 1;
        } else 
            new_dp[vi{a[t]}] += 1;
        swap(dp, new_dp);
        for(auto &[key, val] : dp) ans += val * sz(key);
    }
    rep(i, 0, n){
        if(a[i] == 0) ans += ll(i+1) * (n-i);
    }
    return ans;
}

ll solve(vi &a) {
    int n = sz(a);
    ll ans = 0;
    int p0 = -1;
    vector<array<int, 3>> rng;
    const int inf = 1e9;
    vvi s2(2, vi(n, inf)), s3(2, vi(n, inf)); // 0 -> 1, 1 -> 2
    rep(i, 0, n){
        if(a[i] == 0){
            ans += ll(i+1) * (n - i); // contribution of 0
        } else {
            p0 = i;
            if(sz(rng) == 0 || rng.back()[0] != a[i]){
                rng.push_back({a[i], i, i});
            } else rng.back()[2] = i;
            if(sz(rng) >= 2) {
                auto [t0, l0, r0] = rng[sz(rng)-2];
                auto [t1, l1, r1] = rng[sz(rng)-1];
                if(t0 == 2 && t1 == 1){
                    s2[1][r0] = min(s2[1][r0], l1);
                } else if(t0 == 1 && t1 == 2) {
                    s2[0][r0] = min(s2[0][r0], l1);
                }
            }
            if(sz(rng) >= 3) {
                auto [t0, l0, r0] = rng[sz(rng)-3];
                auto [t1, l1, r1] = rng[sz(rng)-2];
                auto [t2, l2, r2] = rng[sz(rng)-1];
                if(t0 == 3 && t1 == 2 && t2 == 1) {
                    s3[1][r0] = min(s3[1][r0], l2);
                }
                if(t0 == 3 && t1 == 1 && t2 == 2) {
                    s3[0][r0] = min(s3[0][r0], l2);
                }
            }
        }
        ans += p0+1; // 1+ non0 elems
    }
    for(int i = n-2; i >= 0; i--){
        rep(t, 0, 2){
            s2[t][i] = min(s2[t][i], s2[t][i+1]);
            s3[t][i] = min(s3[t][i], s3[t][i+1]);
        }
    }
    rep(i, 0, n){
        int min2 = n, min3 = n;
        rep(t, 0, 2){
            int end2 = s2[t][i];
            min2 = min(min2, end2);
        }
        rep(t, 0, 2){
            int end2 = s2[t][i];
            if(end2 != inf && end2 == min2 && end2 + 1 < n){
                int end3 = s3[1-t][end2+1];
                min3 = min(min3, end3);
            }
        }
        ans += n - min2;
        ans += n - min3;
        // cout << i << " " << min2 << " " << min3 << endl;
    }
    return ans;
}

ll bf(vi &a) {
    int n = sz(a);
    ll ans = 0;
    rep(start, 0, n){
        vi seqs;
        rep(j, 0, start){
            // cout << 0 << " ";
        }
        rep(j, start, n){
            // if(a[j] != 0) {
            bool done = false;
            rep(i, 0, sz(seqs)){
                if(seqs[i] & a[j]){
                    seqs[i] = a[j];
                    done = true;
                    break;
                }
            }
            if(!done) seqs.pb(a[j]);
            // }
            // cout << sz(seqs) << " ";
            ans += sz(seqs);
        }
        // cout << endl;
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    srand(time(NULL));
    // while(true){
    //     rep(i, 0, n){
    //         a[i] = rand() % 4;
    //     }
    //     ll res = solve(a);
    //     ll res2 = solve2(a);
    //     if(res != res2){
    //         rep(i, 0, n) cout << a[i] << " ";
    //         cout << endl;
    //         break;
    //     }
    // }
    rep(i, 0, n) {
        cin >> a[i];
    }
    
    ll res = solve2(a);
    cout << res << "\n";
    // ll res2 = bf(a);
    // cout << res2 << "\n";
    
    return 0;
}
