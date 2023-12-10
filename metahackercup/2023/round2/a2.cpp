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
#pragma comment(linker, "/STACK:1073741824")
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

vi dr{1, 0, -1, 0};
vi dc{0, 1, 0, -1};

void main_()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int r, c;
        cin >> r >> c;
        vvi grid(r, vi(c));
        rep(i, 0, r)
        {
            string str;
            cin >> str;
            rep(j, 0, c)
            {
                if (str[j] == 'B')
                    grid[i][j] = 1;
                if (str[j] == 'W')
                    grid[i][j] = 2;
            }
        }
        vvi comp(r, vi(c, -1));
        int numcomps = 0;
        vector<set<pi>> compnext;
        vi compcnt;
        auto dfs = [&](int row, int col, auto &&dfs) -> void
        {
            comp[row][col] = numcomps;
            compcnt.back()++;
            rep(k, 0, 4)
            {
                if (row + dr[k] < 0 || row + dr[k] >= r || col + dc[k] < 0 || col + dc[k] >= c)
                    continue;
                if (grid[row + dr[k]][col + dc[k]] == 0)
                {
                    compnext.back().insert({row + dr[k], col + dc[k]});
                    // cout << "empty next" << endl;
                }
                if (grid[row + dr[k]][col + dc[k]] == 2 && comp[row + dr[k]][col + dc[k]] == -1)
                    dfs(row + dr[k], col + dc[k], dfs);
            }
        };
        rep(i, 0, r)
        {
            rep(j, 0, c)
            {
                if (grid[i][j] == 2 && comp[i][j] == -1)
                {
                    compnext.pb({});
                    compcnt.pb(0);
                    dfs(i, j, dfs);
                    numcomps++;
                }
            }
        }
        int maxrem = 0;
        map<pi, int> best;
        rep(i, 0, numcomps)
        {
            if (sz(compnext[i]) == 1)
            {
                best[*compnext[i].begin()] += compcnt[i];
            }
        }
        for (auto [key, val] : best) maxrem = max(maxrem, val);
        cout << "Case #" << (cn + 1) << ": " << maxrem << endl;
    }
}


static void run_with_stack_size(void (*func)(void), size_t stsize) {
    char *stack, *send;
    stack = (char *)malloc(stsize);
    send = stack + stsize - 16;
    send = (char *)((uintptr_t)send / 16 * 16);
    asm volatile(
        "mov %%rsp, (%0)\n"
        "mov %0, %%rsp\n"
        :
        : "r"(send));
    func();
    asm volatile("mov (%0), %%rsp\n" : : "r"(send));
    free(stack);
}

int main() {
    run_with_stack_size(main_, 1024 * 1024 * 1024); // run with a 1 GiB stack
    return 0;
}
