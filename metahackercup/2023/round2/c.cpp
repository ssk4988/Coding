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
// PUT ALL OUTSIDE FUNCTION, REMOVE LAMBDAS
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n;
        cin >> n;
        vvi child(n);
        rep(i, 1, n)
        {
            int v;
            cin >> v;
            v--;
            child[v].pb(i);
        }
        map<string, int> rl;
        vector<unordered_set<int>> inall(n);
        vector<unordered_set<int>> inallp(n);
        rep(i, 0, n)
        {
            int m;
            cin >> m;
            rep(j, 0, m)
            {
                string str;
                cin >> str;
                if (!rl.count(str))
                    rl[str] = sz(rl);
                inall[i].insert(rl[str]);
                inallp[i].insert(rl[str]);
            }
        }
        vi numleaves(n);
        auto calc = [&](int cur, auto &&calc) -> void{
            if(sz(child[cur]) == 0) numleaves[cur]++;
            for(int i : child[cur]){
                calc(i, calc);
                numleaves[cur] += numleaves[i];
            }
        };
        calc(0, calc);
        rep(i, 0, n)
        {
            cout << i << " " << sz(inall[i]) << ": ";
            for (int j : inall[i])
                cout << j << " ";
            cout << endl;
            // if(sz(child[i])) cout << child[i][0] << nL;
        }
        auto dfs = [&](int cur, auto &&dfs) -> void
        {
            if (sz(child[cur]) == 0)
                return;
            int heavy = child[cur][0];
            for (int i : child[cur])
            {
                dfs(i, dfs);
                if (sz(inallp[i]) > sz(inallp[heavy]))
                    heavy = i;
            }
            if (sz(child[cur]) == 1)
            {
                // FIX THIS
                if (sz(inall[heavy]) > sz(inall[cur]))
                {
                    swap(inall[heavy], inall[cur]);
                    cout << "swapped " << cur << " " << heavy << endl;
                }
                cout << "parent " << cur << " now has ";
                for (int j : inall[cur])
                    cout << j << " ";
                cout << endl;
                cout << "in heavy child " << heavy << " has ";
                for (int j : inall[heavy])
                {
                    inall[cur].insert(j);
                    cout << j << " ";
                }
                if(sz(inallp[heavy]) > sz(inallp[cur])){
                    swap(inallp[heavy], inall[cur]);
                }
                for (int j : inallp[heavy])
                {
                    inallp[cur].insert(j);
                }
                cout << endl;
                return;
            }
            unordered_map<int, int> freq;
            unordered_map<int, vi> freqp;
            int light = 0;
            // unordered_set<int> childintersect;
            for (int i : child[cur])
            {
                if (i == heavy)
                    continue;
                for (int j : inall[i])
                {
                    freq[j]++;
                }
                for(int j : inallp[i]){
                    if(!inall[i].count(j)) freqp[j].pb(i);
                }
                light++;
            }
            vi add, addp; // parent was necessary
            for (auto [key, val] : freq)
            {
                if (val == light)
                {
                    // paths through heavy
                    bool subchildgood = inallp[heavy].count(key) || numleaves[heavy] == 1;
                    if(subchildgood && (inall[cur].count(key) || inall[heavy].count(key))){
                        add.pb(key);
                    }
                    if(subchildgood){
                        addp.pb(key);
                    }
                }
                if (val == light - 1 && sz(freqp[key]) == 1 && inall[heavy].count(key))
                {
                    // not through heavy
                    // inall[cur].count(key) && inall[heavy].count(key)
                    // add.pb(key);
                    // int pathchild = freqp[key][0];
                    // if()
                    addp.pb(key);
                }
            }
            inall[cur].clear();
            for (int i : add)
                inall[cur].insert(i);
            inallp[cur].clear();
            for (int i : addp)
                inallp[cur].insert(i);
        };
        dfs(0, dfs);
        rep(i, 0, n)
        {
            cout << i << " " << sz(inall[i]) << ": ";
            for (int j : inall[i])
                cout << j << " ";
            cout << "inp: ";
            for (int j : inallp[i])
                cout << j << " ";
            cout << endl;
        }
        cout << "Case #" << (cn + 1) << ": " << sz(inall[0]) << endl;
    }

    return 0;
}
