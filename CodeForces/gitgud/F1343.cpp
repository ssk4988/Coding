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
        // CHECK n=2
        int n; cin >> n;
        vvi occ(n);
        vvi a(n-1);
        rep(i, 0, n-1){
            int k; cin >> k;
            rep(j, 0, k){
                int v; cin >> v; v--;
                occ[v].pb(i);
                a[i].pb(v);
            }
        }
        bool found = false;
        rep(start, 0, n){
            vi curfreq(n);
            vi open(n-1);
            auto cmp = [&](int a, int b) -> bool {
                return pi{curfreq[a], a} > pi{curfreq[b], b};
            };
            vi perm;
            perm.pb(start);
            set<int, decltype(cmp)> ss(cmp);
            rep(i, 0, n){
                if(i == start) continue;
                ss.insert(i);
            }
            int numopen = 0;
            vi left(n-1);
            rep(i, 0, n-1){
                left[i] = sz(a[i]);
            }
            bool works = true;
            for(int i : occ[start]){
                open[i] = true;
                // cout << "opened init " << i << "\n";
                numopen++;
                left[i]--;
                for(int j : a[i]){
                    if(j != start){
                        ss.erase(j);
                        curfreq[j]++;
                        ss.insert(j);
                    }
                }
            }
            rep(_, 0, n-1){
                int best = *ss.begin();
                ss.erase(best);
                if(curfreq[best] != numopen){
                    works = false;
                    break;
                }
                curfreq[best] = 0;
                perm.pb(best);
                // cout << "added " << best << "\n";
                int closecnt = 0;
                for(int i : occ[best]){
                    left[i]--;
                    if(!open[i]){
                        // cout << "opened segment " << i << "\n";
                        open[i] = true;
                        numopen++;
                        for(int j : a[i]){
                            if(j != best){
                                ss.erase(j);
                                curfreq[j]++;
                                ss.insert(j);
                            }
                        }
                    }
                    if(left[i] == 0) {
                        // cout << "closed segment " << i << "\n";
                        numopen--;
                        closecnt++;
                    }
                }
                if(closecnt != 1){
                    works = false;
                    break;
                }
            }
            if(works){
                for(int i : perm) cout << (i+1) << " ";
                cout << "\n";
                found = true;
                break;
            }
        }
        if(!found){
            assert(false);
            // cout << "NOT FOUND\n";
        }
    }
    
    return 0;
}
