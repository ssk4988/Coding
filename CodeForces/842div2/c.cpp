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
        vvi rev(n);
        rep(i, 0, n){
            cin >> a[i];
            a[i]--;
            rev[a[i]].pb(i);
        }
        vvi arr(2, vi(n, -1));
        bool works = true;
        vector<priority_queue<pi>> em(2);
        for(int i = n - 1; i >= 0; i--){
            if(rev[i].size() > 2){
                works = false;
                break;
            }
            else if(rev[i].size() == 2){
                rep(j, 0, 2){
                    arr[j][rev[i][j]] = i;
                    em[1 - j].push({i, rev[i][j]});
                }
            }
            else if(rev[i].size() == 1){
                arr[0][rev[i][0]] = arr[1][rev[i][0]] = i;
            }
            else{
                if(em[0].empty() || em[1].empty()){
                    works = false;
                    break;
                }
                else{
                    rep(j, 0, 2){
                        pi p = em[j].top(); em[j].pop();
                        arr[j][p.s] = i;
                    }
                }
            }
        }
        vvi freq(2, vi(n));
        rep(i, 0, 2){
            rep(j, 0, n){
                if(arr[i][j] < 0){
                    works = false;
                    continue;
                }
                freq[i][arr[i][j]]++;
            }
            rep(j, 0, n){
                if(freq[i][j] != 1){
                    works = false;
                    break;
                }
            }
        }
        if(works){
            cout << "YES" << nL;
            rep(i, 0, 2){
                rep(j, 0, n - 1){
                    cout << (arr[i][j] + 1) << " ";
                }
                cout << (arr[i][n - 1] + 1) << nL;
            }
        }
        else{
            cout << "NO" << nL;
        }
    }
    
    return 0;
}