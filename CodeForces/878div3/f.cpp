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

const int maxv = 500000000;

bitset<maxv> b;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        int maxt = (n + 1) * (m + 1) + 250;
        // vector<vector<vector<bool>>> inq(maxt);
        vi dims = {(n + 1) * (m + 1), (m + 1), 1};
        auto getind = [&](int i, int j, int k)->int{
            int v = dims[0] * i + dims[1] * j + dims[2] * k;
            assert(v < maxv);
            return v;
        };
        rep(i, 0, maxt){
            rep(j, 0, n + 1){
                rep(k, 0, m + 1){
                    b[getind(i, j, k)] = 0;
                }
            }
        }
        vector<vector<bool>> rowok(maxt, vector<bool>(n + 1, true)), colok(maxt, vector<bool>(m + 1, true));
        int r; cin >> r;
        rep(i, 0, r){
            int t, d, coord; cin >> t >> d >> coord;
            if(t > maxt) continue;
            if(d == 1){
                rowok[t][coord] = false;
            }
            else colok[t][coord] = false;
        }
        // inq[0] = vector<vector<bool>>(n + 1, vector<bool>(m + 1));
        // inq[0][0][0] = true;
        b[0] = true;
        queue<array<int, 3>> q;
        q.push({0, 0, 0});
        bool works = false;
        while(q.size()){
            auto [t, r1, c1] = q.front(); q.pop();
            // if(inq[t + 1].size() == 0){
            //     inq[t + 1] = vector<vector<bool>>(n + 1, vector<bool>(m + 1));
            // }
            if(r1 == n && c1 == m){
                works = true;
                cout << t << nL;
                break;
            }
            if(t + 1 == maxt) continue;
            if(rowok[t + 1][r1] && colok[t + 1][c1] && !b[getind(t + 1, r1, c1)]){
                // inq[t + 1][r1][c1] = true;
                b[getind(t + 1, r1, c1)] = true;
                q.push({t + 1, r1, c1});
            }
            if(r1 + 1 <= n && rowok[t + 1][r1 + 1] && colok[t + 1][c1] && !b[getind(t + 1, r1 + 1, c1)]){
                // inq[t + 1][r1 + 1][c1] = true;
                b[getind(t + 1, r1 + 1, c1)] = true;
                q.push({t + 1, r1 + 1, c1});
            }
            if(c1 + 1 <= m && rowok[t + 1][r1] && colok[t + 1][c1 + 1] && !b[getind(t + 1, r1, c1 + 1)]){
                // inq[t + 1][r1][c1 + 1] = true;
                b[getind(t + 1, r1, c1 + 1)] = true;
                q.push({t + 1, r1, c1 + 1});
            }
        }
        if(works) continue;
        cout << "-1" << nL;
    }
    
    return 0;
}
