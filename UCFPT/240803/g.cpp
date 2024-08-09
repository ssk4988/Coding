#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for (int i = a; i < (b); i++)

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using vl = vector<ll>;

void solve()
{
    string line;
    rep(i, 0, 6)
        getline(cin, line);
    cin >> line >> line >> line >> line;
    int b = 0;
    if (line == "one")
        b = 1;
    else if (line == "two")
        b = 2;
    else if (line == "three")
        b = 3;
    else if (line == "four")
        b = 4;
    else if (line == "five")
        b = 5;
    cin >> line >> line >> line >> line >> line >> line >> line;
    getline(cin, line);
    istringstream is(line);
    vector<string> ops;
    while (is >> line)
    {
        if (line == "and")
            continue;
        ops.push_back(line.substr(0, line.length() - 1));
        // cout << line << " >" << ops.back() << "\n";
    }
    getline(cin, line);
    getline(cin, line);
    // cout << b << "\n";
    vector<vvi> arglist(sz(ops));
    vvi vallist(sz(ops));
    rep(o, 0, sz(ops))
    {
        vector<string> lines;
        getline(cin, line);
        is = istringstream(line);
        int len = 0;
        {
            string bruh;
            while (is >> bruh)
            {
                len++;
            }
        }
        int numargs = len - 1;
        lines.push_back(line);
        int expectedlines = 1;
        rep(i, 0, numargs) expectedlines *= b;
        // cout << expectedlines << endl;
        while (sz(lines) < expectedlines)
        {
            getline(cin, line);
            lines.push_back(line);
        }
        rep(i, 0, sz(lines))
        {
            // cout << ops[o] << ": " << lines[i] << endl;
            is = istringstream(lines[i]);
            arglist[o].push_back({});
            int arg;
            rep(j, 0, numargs)
            {
                is >> arg;
                arglist[o].back().push_back(arg);
            }
            is >> arg;
            vallist[o].push_back(arg);
            // cout << arg << "\n";
        }
    }
    getline(cin, line);
    getline(cin, line);
    map<string, int> widx;
    vi state;
    vi vals;
    while (true)
    {
        getline(cin, line);
        is = istringstream(line);
        is >> line;
        if (line == "And")
            break;
        if (!widx.count(line))
        {
            widx[line] = sz(widx);
            int val;
            is >> line >> val;
            vals.push_back(val);
            state.push_back(2);
        }
    }
    vvi deps;
    vi opeq;
    opeq.resize(sz(vals));
    deps.resize(sz(vals));
    auto createword = [&]()
    {
        vals.push_back(-1);
        opeq.push_back(-1);
        deps.push_back({});
        state.push_back(0);
    };
    while (true)
    {
        getline(cin, line);
        is = istringstream(line);
        is >> line;
        if (line == "Is")
            break;
        string word(line);
        if (!widx.count(line))
        {
            widx[line] = sz(widx);
            createword();
        }
        string op;
        is >> line >> op;
        int opidx = find(all(ops), op) - ops.begin();
        int numargs = sz(arglist[opidx][0]);
        opeq[widx[word]] = opidx;
        rep(i, 0, numargs)
        {
            is >> line;
            if (!widx.count(line))
            {
                widx[line] = sz(widx);
                createword();
            }
            deps[widx[word]].push_back(widx[line]);
        }
    }
    auto calc = [&](int idx, auto &&calc) -> pair<bool, int>
    {
        if (state[idx] != 0)
        {
            if (state[idx] == 1)
                return {true, -1};
            return {false, vals[idx]};
        }
        state[idx] = 1;
        rep(i, 0, sz(deps[idx]))
        {
            auto [cycle, res] = calc(deps[idx][i], calc);
            if (cycle)
                return {true, -1};
            deps[idx][i] = res;
        }
        state[idx] = 2;
        int lineidx = -1;
        int op = opeq[idx];
        rep(i, 0, sz(arglist[op]))
        {
            if (arglist[op][i] == deps[idx])
            {
                lineidx = i;
            }
        }
        assert(lineidx != -1);
        vals[idx] = vallist[op][lineidx];
        return {false, vals[idx]};
    };
    // rep(i, 0, sz(ops))
    // {
    //     rep(j, 0, sz(arglist[i]))
    //     {
    //         cout << "line for op " << i << ": ";
    //         for (int k : arglist[i][j])
    //         {
    //             cout << k << " ";
    //         }
    //         cout << " = ";
    //         cout << vallist[i][j];
    //         cout << endl;
    //     }
    // }
    // rep(i, 0, sz(vals))
    // {
    //     cout << i << ": ";
    //     for (int dep : deps[i])
    //     {
    //         cout << dep << " ";
    //     }
    //     cout << endl;
    // }
    int q;
    cin >> q;
    rep(i, 0, q)
    {
        string word;
        cin >> word;
        if (!widx.count(word))
        {
            cout << 0 << "\n";
            continue;
        }
        auto [cycle, res] = calc(widx[word], calc);
        if (cycle)
        {
            cout << 0 << "\n";
        }
        else
        {
            cout << res << "\n";
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    // int t;
    // cin >> t;
    // while (t--)
    solve();

    return 0;
}
