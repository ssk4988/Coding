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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; cin >> n;
        vi shuf(n);
        iota(all(shuf), 0);
        random_shuffle(all(shuf));
        vi rev(n);
        rep(i, 0, n) rev[shuf[i]] = i;
        vi ans(n);
        int x = n;
        int queriesused = 0;
        auto query = [&](int idx) -> int {
            cout << "? " << (shuf[idx] + 1) << endl;
            queriesused++;
            char res; cin >> res;
            if(queriesused > n * 39){
                while(true){}
            }
            if(res == '-'){
                exit(0);
            }
            if(res == '='){
                return 0;
            }
            if(res == '>'){
                x++;
                return 1;
            }
            x--; return -1;
        };
        auto solve = [&](set<int> &rem, auto &&solve) -> void {
            if(sz(rem) == 0) return;
            int first = *rem.begin();
            while(query(first) != 0);
            ans[first] = x;
            rem.erase(first);
            vi found;
            set<int> left, right;
            for(int i : rem){
                int res = query(i);
                if(res < 0){
                    left.insert(i);
                }
                else right.insert(i);
                while(x != ans[first]) query(first);
            }
            solve(left, solve);
            solve(right, solve);
        };
        set<int> init;
        rep(i, 0, n) init.insert(i);
        solve(init, solve);
        int mn = 1e9;
        rep(i, 0, n){
            mn = min(mn, ans[i]);
        }
        rep(i, 0, n){
            ans[i] -= mn;
            ans[i]++;
        }
        cout << "! ";
        rep(i, 0, n){
            cout << ans[rev[i]] << " ";
        }
        cout << endl;

        // while(query(0) != 0);
        // ans[0] = x;
        // set<int> unsolved;
        // vpi bound(n, {0, 2 * n});
        // bound[0] = {x, x};
        // rep(i, 1, n){
        //     int res = query(i);
        //     if(res == 0) bound[i] = {x, x};
        //     else{
        //         if(res == -1) bound[i].s = min(bound[i].s, x);
        //         else bound[i].f = max(bound[i].f, x);
        //         if(bound[i].f != bound[i].s){
        //             unsolved.insert(i);
        //         }
        //     }
        // }
        
    }
    
    return 0;
}
