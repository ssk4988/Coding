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
    int nt;
    cin >> nt;
    unordered_map<string, int> label;
    vector<vpi> ts(nt);
    rep(i, 0, nt)
    {
        int n;
        cin >> n;
        rep(j, 0, n)
        {
            string str;
            cin >> str;
            rep(k, 0, sz(str))
            {
                if (str[k] == '=')
                {
                    string num = str.substr(k + 1), var = str.substr(0, k);
                    if (label.count(var) == 0)
                        label[var] = sz(label);
                    int varnum = label[var];
                    ts[i].pb({varnum, stoi(num)});
                    break;
                }
            }
        }
    }
    int k;
    cin >> k;
    vpi resp;
    vi res(k);
    rep(i, 0, k)
    {
        string str;
        int val;
        cin >> str >> val;
        if (label.count(str) == 0){
            label[str] = sz(label);
        }
        resp.pb({label[str], val});
        res[label[str]] = val;
    }
    vi used(k), idx(nt);
    vector<queue<int>> blocked(k); // for each variable, threads blocked on it
    queue<int> easy;
    rep(i, 0, nt){
        idx[i] = sz(ts[i]) - 1;
        if(res[ts[i][idx[i]].f] == ts[i][idx[i]].s)easy.push(i);
        else blocked[ts[i][idx[i]].f].push(i);
    }
    int numfinished = 0;
    vi ans;
    while(easy.size()){
        // check if anything can be done
        int t = easy.front(); easy.pop();
        int var = ts[t][idx[t]].f;
        if(!used[var]){
            used[var] = true;
            while(blocked[var].size()){
                int i = blocked[var].front(); blocked[var].pop();
                easy.push(i);
            }
        }
        ans.pb(t + 1);
        idx[t]--;
        if(idx[t] == -1) numfinished++;
        else{
            var = ts[t][idx[t]].f;
            if(used[var] || res[var] == ts[t][idx[t]].s)easy.push(t);
            else blocked[var].push(t);
        }
    }
    reverse(all(ans));
    if(numfinished == nt){
        cout << "Yes\n";
        for(int i : ans) cout << i << " ";
        cout << nL;
    } else cout << "No\n";

    return 0;
}
