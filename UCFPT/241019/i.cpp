#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i,a,b) for(int i = a; i < (b); i++)

vvi combs;
void gencomb(vi &cur, int lim, int left, int idx) {
    if(left == 0){
        combs.push_back(cur);
        return;
    }
    rep(i, idx, lim){
        cur.push_back(i);
        gencomb(cur, lim, left-1, i+1);
        cur.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; ll L;
    cin >> n >> L;
    vector<vl> d(n, vl(n));
    vi p;
    gencomb(p, n, n/2, 0);
    // cerr << sz(combs) << endl;
    rep(i, 0, n){
        rep(j, 0, n){
            cin >> d[i][j];
        }
    }
    // rep(i, 0, n){
        // rep(j, 0, n) cerr << d[i][j] << " ";
        // cerr << endl;
    // }
    vector<vector<vl>> precompr(n, vector<vl>(n));
    vector<vector<vl>> precompl(n, vector<vl>(n));
    bool works = false;
    for(auto &comb : combs) {
        vi left(comb), right;
        int p = 0;
        rep(i, 0, n){
            while(p < sz(left) && left[p] < i) p++;
            if(p == sz(left) || left[p] != i){
                right.push_back(i);
            }
        }
        // cerr << "left ";
        // for(int x : left) cerr << x << " ";
        // cerr << " right ";
        // for(int x : right) cerr << x << " ";
        // cerr << "\n";
        rep(i, 0, n) rep(j, 0, n) precompr[i][j].clear();
        {
            vi perm(right);
            do {
                ll rightdist = 0;
                rep(i, 0, sz(perm)-1) rightdist += d[perm[i]][perm[i+1]];
                precompr[perm[0]][perm.back()].push_back(rightdist);
                // cerr << "perm ";
                // for(int x : perm) cerr << x << " ";
                // cerr << "\n";
            } while(next_permutation(all(perm)));
            rep(i, 0, n){
                rep(j, 0, n){
                    sort(all(precompr[i][j]));
                    precompr[i][j].erase(unique(all(precompr[i][j])), end(precompr[i][j]));
                    reverse(all(precompr[i][j]));
                }
            }
        }
        rep(i, 0, n) rep(j, 0, n) precompl[i][j].clear();
        {
            vi perm(left);
            do {
                ll leftdist = 0;
                rep(i, 0, sz(perm)-1) leftdist += d[perm[i]][perm[i+1]];
                precompl[perm[0]][perm.back()].push_back(leftdist);
                // cerr << "perm ";
                // for(int x : perm) cerr << x << " ";
                // cerr << "\n";
            } while(next_permutation(all(perm)));
            rep(i, 0, n){
                rep(j, 0, n){
                    sort(all(precompl[i][j]));
                    precompl[i][j].erase(unique(all(precompl[i][j])), end(precompl[i][j]));
                }
            }
        }
        int a = left[0];
        for(int b : left) {
            for(int i : right){
                for(int j : right){
                    // if(i == j) continue;
                    ll target = L - (d[b][i] + d[j][a]);
                    int p1 = 0, p2 = 0;
                    while(p1 < sz(precompl[a][b]) && p2 < sz(precompr[i][j])) {
                        ll w = precompl[a][b][p1] + precompr[i][j][p2];
                        if(w < target){
                            p1++;
                        } else if(w == target) {
                            works = true;
                            goto fnd;
                        } else{
                            p2++;
                        }
                    }
                }
            }
        }
        
    }
    fnd:
    cout << (works ? "possible" : "impossible") << "\n";
    return 0;
}
