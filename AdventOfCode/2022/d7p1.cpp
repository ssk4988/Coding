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

struct dir
{
    map<string, dir *> dirs;
    map<string, ll> files;
    ll sum = -1;
    dir *back;
    string name;
    dir(string name){
        this->name = name;
    }
};

ll solve(dir *p)
{
    if (p->sum != -1)
        return p->sum;
    p->sum = 0;
    for (auto &p1 : p->dirs)
    {
        p->sum += solve(p1.s);
    }
    for (auto &p1 : p->files)
    {
        p->sum += p1.s;
    }
    return p->sum;
}

ll dfs(dir *cur){
    ll ans = 0;
    if(cur->sum <= 100000){
        ans += cur->sum;
    }
    for(auto p : cur->dirs){
        ans += dfs(p.s);
    }
    return ans;
}

ll find(dir *cur, int val){
    ll ans = 100000000;
    if(cur->sum >= val && cur->sum < ans){
        ans = cur->sum;
    }
    for(auto p : cur->dirs){
        ans = min(ans, find(p.s, val));
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    string str1;
    getline(cin, str1);
    dir *cur = new dir("/");
    dir *root = cur;
    
    rep(i, 0, n)
    {
        string str;
        getline(cin, str);
        stringstream o(str);
        vector<string> args;
        while ((o >> str))
        {
            args.pb(str);
        }
        if (args[0] == "$")
        {
            if (args.size() == 3)
            {

                if (args[2] == "..")
                {
                    cur = cur->back;
                }
                else if (args[2] == "/")
                {
                    cur = root;
                }
                else
                {
                    if (cur->dirs.find(args[2]) != cur->dirs.end())
                    {
                        cur = cur->dirs[args[2]];
                    }
                    else
                    {
                        cur->dirs[args[2]] = new dir(args[2]);
                        cur->dirs[args[2]]->back = cur;
                    }
                }
            }
        }

        else
        {
            if (args[0] == "dir")
            {
                if (cur->dirs.find(args[1]) == cur->dirs.end())
                {
                    cur->dirs[args[1]] = new dir(args[1]);
                    cur->dirs[args[1]]->back = cur;
                }
            }
            else
            {
                if (cur->files.find(args[1]) == cur->files.end())
                {
                    int b = stoi(args[0]);
                    cur->files[args[1]] = b;
                }
            }
        }
    }
    ll remaining = 70000000 - solve(root);
    ll target = 30000000 - remaining;
    cout << dfs(root) << nL;
    cout << find(root, target) << nL;
    return 0;
}