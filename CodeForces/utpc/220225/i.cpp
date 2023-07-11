#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int h, w; cin >> h >> w;
    int oh = h, ow = w;
    bool sw = false;
    if(h < w) {
        swap(h, w);
        sw = true;
    }
    int t; cin >> t;
    vi a(t);
    rep(i, 0, t) cin >> a[i];
    sort(all(a));
    reverse(all(a));
    vector<vector<vector<vector<vector<vector<vector<int>>>>>>> dp(t + 1, vector<vector<vector<vector<vector<vector<int>>>>>>(h + 1, vector<vector<vector<vector<vector<int>>>>>(h + 1, vector<vector<vector<vector<int>>>>(h + 1, vector<vector<vector<int>>>(h + 1, vector<vector<int>>(h + 1, vector<int>(h + 1, -1)))))));
    vi bounds(7);
    rep(i, 0, 6){
        bounds[i + 1] = (i + 1 <= w ? h + 1 : 1);
    }
    dp[0][0][0][0][0][0][0] = 0;
    vi idxs(7), idxs2(7);
    auto getidx = [](int h, vi &id)->int{
        int val = 0;
        int pw = 1;
        for(int i = 6; i >= 0; i--){
            val += pw * id[i];
            pw *= h + 1;
        }
        return val;
    };
    auto getvidx = [](int h, int v)->vi{
        int pw = 1;
        for(int i = 6; i > 0; i--) pw *= h + 1;
        vi ans;
        rep(i, 0, 7){
            ans.push_back(v / pw);
            v %= pw;
            pw /= h + 1;
        }
        return ans;
    };
    rep(i, 0, t){
        idxs[0] = i;
        rep(d1, 0, bounds[1]){
            idxs[1] = d1;
            rep(d2, 0, bounds[2]){
                idxs[2] = d2;
                rep(d3, 0, bounds[3]){
                    idxs[3] = d3;
                    rep(d4, 0, bounds[4]){
                        idxs[4] = d4;
                        rep(d5, 0, bounds[5]){
                            idxs[5] = d5;
                            rep(d6, 0, bounds[6]){
                                idxs[6] = d6;
                                if(dp[i][d1][d2][d3][d4][d5][d6] == -1) continue;
                                rep(l, 1, 7){
                                    if(l + a[i] - 1 > w) break;
                                    int tp = 0;
                                    rep(j, l, l + a[i]){
                                        tp = max(tp, idxs[j]);
                                    }
                                    if(tp + a[i] > h) continue;
                                    rep(j, 0, 7) idxs2[j] = idxs[j];
                                    rep(j, l, l + a[i]){
                                        idxs2[j] = tp + a[i];
                                    }
                                    dp[i + 1][idxs2[1]][idxs2[2]][idxs2[3]][idxs2[4]][idxs2[5]][idxs2[6]] = getidx(h, idxs);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int works = -1;
    rep(d1, 0, bounds[1]){
        rep(d2, 0, bounds[2]){
            rep(d3, 0, bounds[3]){
                rep(d4, 0, bounds[4]){
                    rep(d5, 0, bounds[5]){
                        rep(d6, 0, bounds[6]){
                            if(dp[t][d1][d2][d3][d4][d5][d6] != -1) {
                                vi idxs = {t, d1, d2, d3, d4, d5, d6};
                                works = getidx(h, idxs);
                            }
                        }
                    }
                }
            }
        }
    }
    if(works == -1){
        cout << "IMPOSSIBLE\n";
        return 0;
    }
    
    vector<vi> bb;
    vector<vi> ans(h, vi(w));
    while(works != 0){
        bb.push_back(getvidx(h, works));
        works = dp[bb.back()[0]][bb.back()[1]][bb.back()[2]][bb.back()[3]][bb.back()[4]][bb.back()[5]][bb.back()[6]];
        // rep(i, 0, 7){
        //     cout << bb.back()[i] << " ";
        // }
        // cout << "\n";
    }
    bb.push_back(vi(7, 0));
    reverse(all(bb));
    rep(i, 1, sz(bb)){
        rep(j, 1, w + 1){
            if(bb[i - 1][j] != bb[i][j]){
                rep(j1, j, j + a[i - 1]){
                    rep(k, bb[i][j] - a[i - 1] + 1, bb[i][j] + 1){
                        ans[k - 1][j1 - 1] = i;
                    }
                }
                break;
            }
            // rep(k, 1, h + 1){
            //     if(bb[i - 1][j] < k && k <= bb[i][j] && bb[i][j] - a[i - 1] + 1 >= k){
            //         ans[k - 1][j - 1] = i;
            //     }
            // }
            // rep(k, bb[i][j] - a[i - 1], bb[i][j]){
            //     ans[k][j - 1] = i;
            // }
        }
    }
    // rep(i, 0, sz(ans)){
    //     rep(j, 0, sz(ans[i])){
    //         cout << ans[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    vector<vi> tpd;
    if(!sw){
        tpd = ans;
    }
    else{
        tpd = vector<vi>(oh, vi(ow));
        rep(i, 0, oh){
            rep(j, 0, ow){
                tpd[i][j] = ans[j][i];
            }
        }
    }
    rep(i, 0, oh){
        rep(j, 0, ow){
            if(tpd[i][j] == 0) cout << ". ";
            else cout << char('A' - 1 + tpd[i][j]) << " ";
        }
        cout << "\n";
    }


    // cout << (works ? "YES" : "NO") << "\n";
}