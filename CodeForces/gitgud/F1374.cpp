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
        vi a(n);
        vpi order(n);
        ll inv = 0;
        rep(i, 0, n){
            cin >> a[i]; a[i]--;
            order[i] = {a[i], i};
            rep(j, 0, i){
                if(a[j] > a[i]) inv++;
            }
        }
        bool works = true;
        sort(all(order));
        if(inv % 2 == 1){
            // fix it
            bool fix = false;
            rep(i, 0, n-1){
                if(order[i].f != order[i+1].f) continue;
                swap(order[i].s, order[i+1].s);
                fix = true;
                break;
            }
            if(!fix){
                cout << "-1\n";
                continue;
            }
        }
        rep(i, 0, n){
            a[order[i].s] = i;
        }
        vi ans;
        rep(i, 0, n){
            int p = find(all(a), i) - a.begin();
            // cout << i << " at " << p << endl;
            while(p != i){
                if(p - 2 >= i){
                    rotate(a.begin() + p - 2, a.begin() + p, a.begin() + p + 1);
                    ans.pb(p-2);
                    p -= 2;
                }
                else{
                    rotate(a.begin() + p - 1, a.begin() + p, a.begin() + p + 2);
                    ans.pb(p-1);
                    ans.pb(p-1);
                    p -= 1;
                }
            }
        }
        vi target(n);
        iota(all(target), 0);
        if(a != target){
            assert(false);
            cout << "-1\n";
            continue;
        }
        cout << sz(ans) << "\n";
        for(int i : ans){
            cout << (i+1) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
