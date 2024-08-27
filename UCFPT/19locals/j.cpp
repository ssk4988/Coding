#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

// using ld = long double;
using ld = double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int N;
// using mat = array<array<ld, N>, N>;
using mat = vector<ld>;

vi use;

inline int idx(int i, int j)
{
    return i * N + j;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    N = 2 * n;
    mat base(N * N);
    vector<vector<pair<int, ld>>> adj(n);
    vi lolly(n);
    vi out(n);
    rep(i, 0, n)
    {
        cin >> lolly[i];
        int k;
        cin >> k;
        rep(j, 0, k)
        {
            int to;
            ld w;
            cin >> to >> w;
            to--;
            if (to < n)
            {
                base[idx(i, to)] += w;
            }
            else
            {
                adj[i].push_back({to, w});
                base[idx(i, N / 2 + i)] += w;
                out[i] = true;
            }
        }
    }
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            rep(k, 0, n)
            {
                if (out[k])
                    out[j] = 1;
            }
        }
    }
    rep(i, 0, n) if (out[i]) use.push_back(i);
    rep(i, N / 2, N) base[idx(i, i)] = 1;
    rep(i, 0, 25)
    {
        mat res(N * N);
        for (int i : use)
        {
            rep(j, 0, N)
            {
                for (int k : use)
                {
                    // rep(k, 0, N/2){
                    // if(k == i && j != i) continue;
                    res[idx(i, j)] += base[idx(i, k)] * base[idx(k, j)];
                    // res[i][j] += a[i][k] * b[k][j];
                }
            }
            rep(j, N / 2, N)
            {
                res[idx(i, j)] += base[idx(i, j)] * base[idx(j, j)];
                // res[i][j] += a[i][j] * b[j][j];
            }
        }
        rep(i, N / 2, N)
        {
            res[idx(i, i)] += base[idx(i, i)] * base[idx(i, i)];
            // res[i][i] += a[i][i] * b[i][i];
        }
        swap(base, res);
    }
    vector<ld> res(m);
    vector<ld> stay(m);
    rep(i, 0, n)
    {
        rep(j, 0, n)
        {
            stay[j] += lolly[i] * base[idx(i, j + N / 2)];
        }
    }
    rep(i, 0, n)
    {
        if (sz(adj[i]) == 0)
            continue;
        ld sum = 0;
        for (auto [to, w] : adj[i])
        {
            sum += w;
        }
        for (auto [to, w] : adj[i])
        {
            stay[to] += w / sum * stay[i];
        }
    }
    cout << fixed << setprecision(8);
    rep(i, 0, m)
    {
        if (i < n)
            cout << 0 << "\n";
        else
            cout << stay[i] << "\n";
    }

    return 0;
}
