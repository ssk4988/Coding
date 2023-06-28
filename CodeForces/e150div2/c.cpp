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
using vvl = vector<vl>;

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

ll score(vl &a){
    ll best = 0, score = 0;
    rep(i, 0, sz(a)){
        if(a[i] >= best){
            score += a[i];
            best = a[i];
        }
        else score -= a[i];
    }
    return score;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        // int n; cin >> n;
        string str; cin >> str;
        int n = str.length();
        vl a(n);
        vl v(n);
        vl vals = {1, 10, 100, 1000, 10000};
        rep(i, 0, n){
            a[i] = vals[str[i] - 'A'];
            v[i] = str[i] - 'A';
        }
        reverse(all(a));
        reverse(all(v));
        vl scoreprefs(n);
        ll best = 0;
        rep(i, 0, sz(a)){
            if(a[i] >= best){
                scoreprefs[i] += a[i];
                best = a[i];
            }
            else scoreprefs[i] -= a[i];
            if(i) scoreprefs[i] += scoreprefs[i - 1];
        }
        vvl scoresuffs(n + 1, vl(5));
        vector<vpl> nextbig(n, vpl(5, {-1, -1}));
        vl suffbig(5, n);
        for(int i = n - 1; i >= 0; i--){
            ll curbig = n, bigval = 5;
            nextbig[i][4] = {n, 5};
            for(int j = 4; j >= 0; j--){
                if(suffbig[j] < curbig){
                    curbig = suffbig[j];
                    bigval = j;
                }
                if(j-1>=0){
                    nextbig[i][j-1] = {curbig, bigval};
                }
            }
            suffbig[v[i]] = i;
        }
        rep(j, 0, 5){
            for(int i = n - 1; i >= 0; i--){
                if(v[i] >= j){
                    scoresuffs[i][j] += vals[v[i]];
                }
                else{
                    scoresuffs[i][j] -= vals[v[i]];
                }
                if(i + 1 < n){
                    scoresuffs[i][j] += scoresuffs[i + 1][j];
                }
            }
        }
        
        ll cscore = score(a);
        best = 0;
        rep(i, 0, n){
            ll pval = a[i];
            if(a[i] > best){
                for(ll j : vals){
                    a[i] = j;
                    cscore = max(cscore, score(a));
                }
                a[i] = pval;
                best = a[i];
            }
            else{
                // i > 0
                ll sp = scoreprefs[i - 1];
                rep(j, 0, 5){
                    if(vals[j] < best) continue;
                    ll cs = sp;
                    cs += vals[j] + scoresuffs[i + 1][j];
                    pl curr = {i, j};
                    while(curr.f < n && nextbig[curr.f][curr.s].f < n){
                        pl curr2 = nextbig[curr.f][curr.s];
                        cs -= scoresuffs[curr2.f][curr.s];
                        cs += vals[curr2.s] + scoresuffs[curr2.f + 1][curr2.s];
                        curr = curr2;
                    }
                    cscore = max(cscore, cs);
                }
                // a[i] = vals.back();
                // cscore = max(cscore, score(a));
                // a[i] = pval;
            }
            // else if(a[i] < best){
            //     if(best == vals.back()){

            //     }
            //     else{

            //     }
            // }
        }
        cout << cscore << nL;
    }
    
    return 0;
}
