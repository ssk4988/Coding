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
    int n;
    cin >> n;
    int a[2][n];
    int rev[2][n];
    vector<pair<vi, vvi>> trans;
    bool solved[n];
    memset(solved, false, sizeof solved);
    rep(i, 0, 2)
    {
        rep(j, 0, n)
        {
            cin >> a[i][j];
            a[i][j]--;
            rev[i][a[i][j]] = j;
        }
    }
    rep(i, 0, n)
    {
        trans.pb(mp(vi(), vvi(2, vi(2, -1))));
    }
    rep(i, 0, n)
    {
        if (solved[i])
            continue;
        int cur = i;
        trans[i].f.pb(i);
        solved[i] = true;
        rep(j, 0, 2)
        {
            trans[i].s[j][0] = a[j][(rev[j][i] + n - 1) % n];
            trans[i].s[j][1] = a[j][(rev[j][i] + 1) % n];
        }
        bool cond = true;
        while (cond)
        {
            cond = false;
            vi b;
            rep(j, 0, trans[i].s[0].size())
            {
                rep(k, 0, trans[i].s[1].size())
                {
                    if (trans[i].s[0][j] != -1 && trans[i].s[0][j] == trans[i].s[1][k])
                    {
                        b.pb(j);
                        b.pb(k);
                        break;
                    }
                }
                if (b.size() > 0)
                    break;
            }
            cond = b.size() > 0;
            if (cond)
            {
                int nex = trans[i].s[0][b[0]];
                if (solved[nex])
                {
                    for(auto &c : trans[nex].f){
                        trans[i].f.pb(c);
                    }
                    rep(j, 0, 2){
                        for(auto &c : trans[nex].s[j]){
                            if(count(all(trans[i].f), c) == 0){
                                trans[i].s[j][b[j]] = c;
                                break;
                            }
                        }
                        // trans[i].s[j].erase(trans[i].s[j].begin() + b[j]);
                    }
                }
                else
                {
                    trans[i].f.pb(nex);
                    solved[nex] = true;
                    rep(j, 0, 2)
                    {
                        int target = b[j] ? a[j][(rev[j][trans[i].s[j][b[j]]] + 1) % n] : 
                        a[j][(rev[j][trans[i].s[j][b[j]]] + n - 1) % n];
                        if(count(all(trans[i].s[j]), target) > 0){
                            // trans[i].s[j].erase(trans[i].s[j].begin() + b[j]);
                            trans[i].s[j][b[j]] = -1;
                        }
                        else{
                            trans[i].s[j][b[j]] = target;
                        }
                    }
                }
            }
        }
        if(trans[i].f.size() == n) break;
    }
    bool works = false;
    rep(i, 0, n){
        if(trans[i].f.size() == n){
            works = true;
            for(auto &c : trans[i].f){
                cout << c+1 << " ";
            }
            cout << nL;
            break;
        }
    }
    if(!works) cout << "-1\n";

    return 0;
}