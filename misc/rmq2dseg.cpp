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

template<class T>
struct RMQ2D {
    static constexpr T idem = numeric_limits<T>::max();
    static T f(T a, T b){ return min(a,b); }
    struct seg{
        vector<T> tr; int n;
        seg(vector<T> &arr){
            tr.resize((n = arr.size())*2);
            for(int i = 0; i < n; i++) tr[n+i] = arr[i];
            for(int i = n-1; i>0; i--) tr[i] = f(tr[i<<1],tr[i<<1|1]);
        }
        T query(int l, int r) { 
            T res = idem;
            for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
                if (l&1) res = f(res,tr[l++]);
                if (r&1) res = f(res,tr[--r]);
            }
            return res;
        }
    };
    typedef vector<seg> vs;
    typedef vector<T> vt;
    vector<vector<vs>> rc;
    RMQ2D(vector<vt> tbl) {
        int r = tbl.size(), c = tbl[0].size(), lg = __lg(min(r,c))+1;
        rc.assign(2,vector<vs>(lg));
        rep(pw,0,lg){
            rep(i,0,r) rc[0][pw].emplace_back(tbl[i]);
            vector<vt> transpose(c,vt(r)); 
            rep(i,0,r) rep(j,0,c) transpose[j][i] = tbl[i][j];
            rep(i,0,c) rc[1][pw].emplace_back(transpose[i]);
            int pow2 = 1<<pw;
            rep(i,0,r-pow2) {
                rep(j,0,c-pow2)
                    tbl[i][j] = f(
                        f(tbl[i][j],tbl[i+pow2][j+pow2]),
                        f(tbl[i][j+pow2],tbl[i+pow2][j])
                    );
                tbl[i].resize(c-pow2);
            }
            tbl.resize(r-pow2);
            r = tbl.size(), c = tbl[0].size();
        }
    }

    T query(int r1, int c1, int r2, int c2){
        int pw = __lg(min(r2-r1,c2-c1)), pow2 = 1<<pw;
        int s = c2-c1<r2-r1;
        if (s) swap(r1, c1), swap(r2, c2);
        return f(rc[s][pw][r1].query(c1,c2-pow2+1), 
                         rc[s][pw][c2-pow2].query(c1,c2-pow2+1));
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    
    return 0;
}
