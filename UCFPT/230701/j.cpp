#pragma GCC optimize("Ofast, unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using ld = long double;

int pref[12][12][12][12][12];
int coords[5], coords2[5], los[5], his[5];

int main()
{
    freopen("gift.in", "r", stdin);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, q;
        cin >> n >> q;
        vvi cs(n, vi(5));
        vector<set<int>> co(5);
        vvi co1(5, vi(1, -1));
        rep(i, 0, n)
        {
            vector<ld> d(5);
            rep(j, 0, 5) cin >> d[j];
            rep(j, 0, 5) cs[i][j] = int(0.1 + 1000 * d[j]);
            rep(j, 0, 5) co[j].insert(cs[i][j]);
        }
        vector<map<int, int>> rl(5);
        vi cnt(5, 1);
        rep(j, 0, 5)
        {
            for (int i : co[j])
            {
                rl[j][i] = cnt[j]++;
                co1[j].pb(i);
            }
        }
        memset(pref, 0, sizeof pref);
        // vector<vector<vector<vvi>>> pref(cnt[0], vector<vector<vvi>>(cnt[1], vector<vvi>(cnt[2], vvi(cnt[3], vi(cnt[4])))));
        rep(i, 0, n)
        {
            rep(j, 0, 5) cs[i][j] = rl[j][cs[i][j]];
            pref[cs[i][0]][cs[i][1]][cs[i][2]][cs[i][3]][cs[i][4]]++;
        }
        // vi coords(5), coords2(5);
        rep(j, 0, 5)
        {
            rep(i0, 1, 12)
            {
                // coords[0] = i0;
                // coords2[0] = i0 - (j == 0);
                rep(i1, 1, 12)
                {
                    // coords[1] = i1;
                    // coords2[1] = i1 - (j == 1);
                    rep(i2, 1, 12)
                    {
                        // coords[2] = i2;
                        // coords2[2] = i2 - (j == 2);
                        rep(i3, 1, 12)
                        {
                            // coords[3] = i3;
                            // coords2[3] = i3 - (j == 3);
                            rep(i4, 1, 12)
                            {
                                // coords[4] = i4;
                                // coords2[4] = i4 - (j == 4);
                                pref[i0][i1][i2][i3][i4] += pref[i0-(j==0)][i1-(j==1)][i2-(j==2)][i3-(j==3)][i4-(j==4)];
                                // rep(b, 0, (1 << 5) - 1){
                                //     int par = __builtin_popcount(b) % 2;
                                //     rep(j, 0, 5){
                                //         coords2[j] = coords[j] - ((b & (1 << j)) ? 0 : 1);
                                //     }
                                //     pref[coords[0]][coords[1]][coords[2]][coords[3]][coords[4]] += (par ? -1 : 1) * pref[coords2[0]][coords2[1]][coords2[2]][coords2[3]][coords2[4]];
                                // }
                            }
                        }
                    }
                }
            }
        }
        cout << "Case " << (cn + 1) << ":\n";
        rep(i, 0, q)
        {
            vector<ld> qd(10);
            rep(j, 0, 10)
            {
                cin >> qd[j];
            }
            vi qs(10);
            rep(j, 0, 10) qs[j] = int(0.1 + 1000 * qd[j]);
            // vi los(5, -1), his(5, -1);
            bool validq = true;
            rep(j, 0, 5)
            {
                los[j] = -1, his[j] = sz(co1[j]);
                while (los[j] + 1 < sz(co1[j]) && co1[j][los[j] + 1] < qs[j])
                {
                    los[j]++;
                }
                // his[j] = sz(co1[j]);
                while (his[j] > 0 && co1[j][his[j] - 1] >= qs[j + 5])
                {
                    his[j]--;
                }
                if (his[j] == sz(co1[j]))
                {
                    his[j] = -2;
                }
                if (his[j] <= los[j])
                    validq = false;
            }
            if (!validq)
            {
                cout << "0\n";
                continue;
            }
            rep(j, 0, 5) coords[j] = his[j];
            ll ans = 0;
            rep(b, 0, (1 << 5))
            {
                int par = __builtin_popcount(b) % 2;
                rep(j, 0, 5)
                {
                    coords2[j] = (b & (1 << j)) ? his[j] : los[j];
                }
                ans += (par ? 1 : -1) * pref[coords2[0]][coords2[1]][coords2[2]][coords2[3]][coords2[4]];
            }
            cout << ans << "\n";
        }
    }
}
