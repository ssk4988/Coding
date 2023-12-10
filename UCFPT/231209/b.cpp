#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define pb push_back

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vvi grid(n, vi(m)); // 1 if empty
        rep(i, 0, n){
            string str; cin >> str;
            rep(j, 0, m){
                grid[i][j] = str[j] == '.';
            }
        }
        vector<vvi> bel(2, vvi(n, vi(m, -1))); // 0 horizontal 1 vertical
        int numlines = 0;
        vi t; // type
        vi d1, d2, d3; // d1 is start, d2 is end, d3 is other coord
        rep(i, 0, n){
            int curl = -1;
            rep(j, 0, m){
                if(grid[i][j]){
                    if(curl == -1){
                        curl = numlines++;
                        t.pb(0);
                        d3.pb(i);
                        d1.pb(j);
                        d2.pb(j);
                    }
                    d2.back() = j;
                    bel[0][i][j] = curl;
                }
                else curl = -1;
            }
        }
        rep(j, 0, m){
            int curl = -1;
            rep(i, 0, n){
                if(grid[i][j]){
                    if(curl == -1){
                        curl = numlines++;
                        t.pb(1);
                        d3.pb(j);
                        d1.pb(i);
                        d2.pb(i);
                    }
                    d2.back() = i;
                    bel[1][i][j] = curl;
                }
                else curl = -1;
            }
        }
        int ans = 0;
        vi order(numlines);
        iota(all(order), 0);
        sort(all(order), [&](int a, int b) -> bool { return d2[a] - d1[a] > d2[b] - d1[b]; });
        rep(curl, 0, numlines){
            set<int> inter;
            inter.insert(curl);
            int len = d2[curl] - d1[curl] + 1;
            int len2 = 0;
            rep(d, d1[curl], d2[curl] + 1){
                int i = t[curl] ? d : d3[curl];
                int j = t[curl] ? d3[curl] : d;
                if(bel[1 - t[curl]][i][j] != -1){
                    int o = bel[1 - t[curl]][i][j];
                    inter.insert(o);
                    len2 = max({len2, abs(d2[o] - d3[curl]), abs(d1[o] - d3[curl])});
                }
            }
            rep(i, 0, sz(order)){
                if(!inter.count(order[i])){
                    len2 = max(len2, d2[order[i]] - d1[order[i]] + 1);
                    break;
                }
            }
            // cout << curl << " " << len << " " << len2 << "\n";
            ans = max(ans, len + len2);
        }
        // for(int i : order){
        //     cout << i << " " << t[i] << " " << d1[i] << " " << d2[i] << " " << d3[i] << "\n";
        // }
        cout << ans << "\n";
    }
    return 0;
}
