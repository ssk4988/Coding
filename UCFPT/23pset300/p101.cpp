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

ll MOD = 1e9 + 7;
ll mod(ll k){
    return k % MOD;
}
ll adp[301][301][19][19][3], bdp[301][301][19][19][3];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll a, b; cin >> n >> a >> b;
    a--;
    auto vectorize = [](ll v)->vi{
        ll v1 = v;
        vi res(18);
        rep(i, 0, 18){
            res[i] = v % 10;
            v /= 10;
        }
        while(res.back() == 0 && sz(res) > 1) res.pop_back();
        reverse(all(res));
        return res;
    };
    vi av = vectorize(a), bv = vectorize(b);
    vi ds(n);
    rep(i, 0, n) cin >> ds[i];
    auto addfront = [](vi d)->vi{
        vi res(1);
        for(int i : d) res.pb(i);
        return res;
    };
    ds = addfront(ds);
    av = addfront(av), bv = addfront(bv);

    // [start range][end range][left endpoint][right endpoint][less, equal, greater]


    rep(i, 1, sz(ds)){
        adp[i][i - 1][0][0][1] = 1;
        bdp[i][i - 1][0][0][1] = 1;
    }
    auto cmp = [](int v1, int v2)->int{
        if(v1 == v2) return 1;
        if(v1 > v2) return 2;
        return 0;
    };
    rep(i, 1, sz(ds)){
        rep(j, 0, sz(ds)){
            rep(len, 0, 19){
                rep(l, 0, sz(av)){
                    int r = l + len - 1;
                    if(r >= sz(av)) continue;
                    rep(t, 0, 3){
                        if(adp[i][j][l][r][t] == 0) continue;
                        if(l == 0 && r == 0){
                            if(t == 1){
                                // cout << "first digit of " << (j + 1)<< " starting from " << i << nL;
                                // add first digit in
                                rep(start, 1, sz(av)){
                                    // to front
                                    adp[i][j + 1][start][start][cmp(ds[j + 1], av[start])] = mod(adp[i][j + 1][start][start][cmp(ds[j + 1], av[start])] + adp[i][j][l][r][t]);
                                    // to back
                                    adp[i][j + 1][start][start][cmp(ds[j + 1], av[start])] = mod(adp[i][j + 1][start][start][cmp(ds[j + 1], av[start])] + adp[i][j][l][r][t]);
                                }
                                // ignore
                                adp[i][j + 1][0][0][1] = mod(adp[i][j + 1][0][0][1] + adp[i][j][l][r][t]);
                            }
                        }
                        else{
                            // to front
                            if(l > 1){
                                int nt, c = cmp(ds[j + 1], av[l - 1]);
                                if(t == 1){
                                    nt = c;
                                }
                                else if(t == 0){
                                    nt = c == 2 ? 2 : 0;
                                }
                                else{
                                    nt = c == 0 ? 0 : 2;
                                }
                                adp[i][j + 1][l - 1][r][nt] = mod(adp[i][j + 1][l - 1][r][nt] + adp[i][j][l][r][t]);
                            }
                            // to back
                            if(r + 1 < sz(av)){
                                int nt, c = cmp(ds[j + 1], av[r + 1]);
                                if(t == 1) nt = c;
                                else nt = t;
                                adp[i][j + 1][l][r + 1][nt] = mod(adp[i][j + 1][l][r + 1][nt] + adp[i][j][l][r][t]);
                            }
                            // ignore
                            adp[i][j + 1][l][r][t] = mod(adp[i][j + 1][l][r][t] + adp[i][j][l][r][t]);
                            // if(i == 1 && j == 1 && l == 1 && r == 1){
                            //     cout << "bruh moment";
                            // }
                        }
                    }
                }
            }
        }
    }
    rep(i, 1, sz(ds)){
        rep(j, 0, sz(ds)){
            rep(len, 0, 19){
                rep(l, 0, sz(bv)){
                    int r = l + len - 1;
                    if(r >= sz(bv)) continue;
                    rep(t, 0, 3){
                        if(bdp[i][j][l][r][t] == 0) continue;
                        // cout << i << " " << j << " " << l << " " << r << " " << t << " " << bdp[i][j][l][r][t] << nL;
                        
                        if(l == 0 && r == 0){
                            if(t == 1){
                                // add first digit in
                                rep(start, 1, sz(bv)){
                                    // to front
                                    bdp[i][j + 1][start][start][cmp(ds[j + 1], bv[start])] = mod(bdp[i][j + 1][start][start][cmp(ds[j + 1], bv[start])] + bdp[i][j][l][r][t]);
                                    // to back
                                    bdp[i][j + 1][start][start][cmp(ds[j + 1], bv[start])] = mod(bdp[i][j + 1][start][start][cmp(ds[j + 1], bv[start])] + bdp[i][j][l][r][t]);
                                }
                                // ignore
                                bdp[i][j + 1][0][0][1] = mod(bdp[i][j + 1][0][0][1] + bdp[i][j][l][r][t]);
                            }
                        }
                        else{
                            assert(l != 0 && r != 0);
                            // to front
                            if(l > 1){
                                int nt, c = cmp(ds[j + 1], bv[l - 1]);
                                if(t == 1){
                                    nt = c;
                                }
                                else if(t == 0){
                                    nt = c == 2 ? 2 : 0;
                                }
                                else{
                                    nt = c == 0 ? 0 : 2;
                                }
                                bdp[i][j + 1][l - 1][r][nt] = mod(bdp[i][j + 1][l - 1][r][nt] + bdp[i][j][l][r][t]);
                            }
                            // to back
                            if(r + 1 < sz(bv)){
                                int nt, c = cmp(ds[j + 1], bv[r + 1]);
                                if(t == 1) nt = c;
                                else nt = t;
                                bdp[i][j + 1][l][r + 1][nt] = mod(bdp[i][j + 1][l][r + 1][nt] + bdp[i][j][l][r][t]);
                            }
                            // ignore
                            bdp[i][j + 1][l][r][t] = mod(bdp[i][j + 1][l][r][t] + bdp[i][j][l][r][t]);
                        }
                    }
                }
            }
        }
    }
    auto getansa = [&](int l, int r)->ll{
        ll res = 0;
        rep(i, 1, sz(av)){
            rep(j, 0, 3 - (i == 1)){
                if(adp[l][r][i][sz(av) - 1][j] > 0){
                    // cout << "adp: " << l << " " << r << " " << i << " " << sz(av) - 1 << " " << j << " " << adp[l][r][i][sz(av) - 1][j] << nL;
                }
                res = mod(adp[l][r][i][sz(av) - 1][j] + res);
            }
        }
        return res;
    };
    auto getansb = [&](int l, int r)->ll{
        ll res = 0;
        rep(i, 1, sz(bv)){
            rep(j, 0, 3 - (i == 1)){
                if(bdp[l][r][i][sz(bv) - 1][j] > 0){
                    // cout << "bdp: " << l << " " << r << " " << i << " " << sz(bv) - 1 << " " << j << " " << bdp[l][r][i][sz(bv) - 1][j] << nL;
                }
                res = mod(bdp[l][r][i][sz(bv) - 1][j] + res);
            }
        }
        return res;
    };


    int q; cin >> q;
    rep(i, 0, q){
        int l, r; cin >> l >> r;
        // l--, r--;
        ll ansa = getansa(l, r), ansb = getansb(l, r);
        ll ans = ((ansb - ansa) % MOD + MOD) % MOD;


        // cout << ansa << " " <<  ansb << " " << ans << nL;
        cout << ans << nL;
        // rep(j, 0, 20){
        //     rep(k, 0, 20){
        //         rep(t, 0, 3){
        //             if(bdp[l][r][])
        //         }
        //     }
        // }
    }
    // rep(i, 0, n){
    //     rep(j, 0, 18){
    //         if(av[j] == ds[i]){

    //         }
    //     }
    // }


    return 0;
}