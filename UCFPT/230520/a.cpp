#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
using ll = long long;
using pi = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector<pi>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using ld = long double;

vvi ds = {{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int m; cin >> m;
        int n = m * m;
        auto val = [&](int i, int j)->int{
            return i * m + j;
        };
        auto inbounds = [&](int i, int j)->bool{
            return i >= 0 && i < m && j >= 0 && j < m;
        };
        vvl mat(n, vl(n));
        rep(i, 0, m){
            rep(j, 0, m){
                rep(k, 0, 8){
                    int i1 = i + ds[k][0], j1 = j + ds[k][1];
                    if(inbounds(i1, j1)){
                        mat[val(i, j)][val(i1, j1)] = -1;
                    }
                }
            }
        }
        rep(i, 0, n){
            int sum = 0;
            rep(j, 0, n){
                sum += mat[i][j];
            }
            mat[i][i] = -sum;
        }
        auto scale = [&](vl &a, ll b)->void{
            rep(i, 0, sz(a)){
                a[i] *= b;
            }
        };
        auto add = [&](vl &a, vl &b)->void{
            rep(i, 0, sz(b)){
                a[i] += b[i];
            }
        };
        auto exc = [&](int i, int j)->vvl{
            vvl a;
            rep(i1, 0, n){
                if(i1 == i) continue;
                a.push_back({});
                rep(j1, 0, n){
                    if(j1 == j) continue;
                    a.back().push_back(mat[i1][j1]);
                }
            }
            return a;
        };
        auto det = [&](vector<vector<ld>> &a)->ld{
            int n = sz(a); ld res = 1;
            rep(i, 0, n){
                int b = i;
                rep(j,i+1,n) if(fabs(a[j][i]) > fabs(a[b][i])) b = j;
                if(i != b) swap(a[i], a[b]), res*=-1;
                res *= a[i][i];
                if(res == 0)return 0;
                rep(j,i+1,n){
                    ld v = a[j][i] / a[i][i];
                    if(v != 0) rep(k,i+1,n) a[j][k] -= v * a[i][k];
                }
            }
            return res;
        };
        // auto det = [&](vvl &mat)->ll{
        //     int n = sz(mat);
        //     ll prod = 1;
        //     rep(i, 0, n){
        //         rep(j, i + 1, n){
        //             if(mat[j][i] != 0){
        //                 ll g = __gcd(abs(mat[i][i]), abs(mat[j][i]));
        //                 scale(mat[i], abs(mat[j][i]/g));
        //                 scale(mat[j], abs(mat[i][i] / g));
        //                 if(mat[i][i] == mat[j][j]){
        //                     scale(mat[j], -1);
        //                 }
        //                 add(mat[j], mat[i]);
        //             }
        //         }
        //         prod *= mat[i][i];
        //     }
        //     return prod;
        // };
        ll ans = 0;
        vvl a1 = exc(0, 0);
        vector<vector<ld>> a2(sz(a1), vector<ld>(sz(a1)));
        rep(i1, 0, sz(a1)){
            rep(j1, 0, sz(a1)){
                a2[i1][j1] = a1[i1][j1];
            }
        }
        ll d = roundl(det(a2));
        ans += ((0 + 0) % 2 == 0 ? 1 : -1) * d;
        cout << ans << "\n";
    }
}