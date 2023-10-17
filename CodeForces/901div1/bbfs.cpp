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
vi p5;
int s;
int conv(array<int, 8> &a){
    int v = 0;
    rep(i, 0, 8) v += a[i] * p5[i];
    return v;
}

int getval(int st, int idx){
    return (st / p5[idx]) % 5;
}

tuple<int, int, int> getabm(int v){
    return {v & 1, (v >> 1) & 1, (v >> 2) & 1};
}

int makeabm(int a, int b, int m){
    return a | (b << 1) | (m << 2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    p5 = vi(9);
    p5[0] = 1;
    rep(i, 1, 9) p5[i] = p5[i - 1] * 5;
    s = p5.back();
    const int BAD = 1e9;
    vi dist(s, BAD);
    queue<int> q;
    rep(i, 0, 1 << 8){
        array<int, 8> init = {0, 1, 2, 3, 0, 1, 2, 3};
        rep(j, 0, 8){
            if(i & (1 << j)) init[j] = 4;
        }
        int st = conv(init);
        dist[st] = 0;
        q.push(st);
    }
    vvi adj(s);
    rep(i, 0, s){
        array<int, 8> start;
        rep(j, 0, 8) start[j] = getval(i, j);
        // x & y, y
        {
            array<int, 8> res = {4, 4, 4, 4, 4, 4, 4, 4};
            bool works = true;
            rep(k, 0, 8){
                if(start[k] == 4) continue;
                auto [a, b, m] = getabm(k);
                int idx = makeabm(a & b, b, m);
                if(res[idx] != 4 && res[idx] != start[k]) works = false;
                res[idx] = start[k];
            }
            if(works){
                int st1 = conv(res);
                adj[st1].pb(i);
            }
        }
        // x | y, y
        {
            array<int, 8> res = {4, 4, 4, 4, 4, 4, 4, 4};
            bool works = true;
            rep(k, 0, 8){
                if(start[k] == 4) continue;
                auto [a, b, m] = getabm(k);
                int idx = makeabm(a | b, b, m);
                if(res[idx] != 4 && res[idx] != start[k]) works = false;
                res[idx] = start[k];
            }
            if(works){
                int st1 = conv(res);
                adj[st1].pb(i);
            }
        }
        // x, x ^ y
        {
            array<int, 8> res = {4, 4, 4, 4, 4, 4, 4, 4};
            bool works = true;
            rep(k, 0, 8){
                if(start[k] == 4) continue;
                auto [a, b, m] = getabm(k);
                int idx = makeabm(a, a ^ b, m);
                if(res[idx] != 4 && res[idx] != start[k]) works = false;
                res[idx] = start[k];
            }
            if(works){
                int st1 = conv(res);
                adj[st1].pb(i);
            }
        }
        // x, y ^ m
        {
            array<int, 8> res = {4, 4, 4, 4, 4, 4, 4, 4};
            bool works = true;
            rep(k, 0, 8){
                if(start[k] == 4) continue;
                auto [a, b, m] = getabm(k);
                int idx = makeabm(a, b ^ m, m);
                if(res[idx] != 4 && res[idx] != start[k]) works = false;
                res[idx] = start[k];
            }
            if(works){
                int st1 = conv(res);
                adj[st1].pb(i);
            }
        }
    }
    while(!q.empty()){
        int st = q.front(); q.pop();
        for(int nex : adj[st]){
            if(dist[nex] == BAD){
                dist[nex] = 1 + dist[st];
                q.push(nex);
            }
        }
    }
    rep(i, 0, sz(dist)){
        if(dist[i] == BAD) dist[i] = -1;
    }


    int nc; cin >> nc;
    rep(cn, 0, nc){
        int a, b, c, d, m; cin >> a >> b >> c >> d >> m;
        array<int, 8> mask = {4, 4, 4, 4, 4, 4, 4, 4};
        bool works = true;
        rep(i, 0, 30){
            int idx = makeabm((a >> i) & 1, (b >> i) & 1, (m >> i) & 1);
            if(mask[idx] != 4 && mask[idx] != makeabm((c >> i) & 1, (d >> i) & 1, 0)) works = false;
            mask[idx] = makeabm((c >> i) & 1, (d >> i) & 1, 0);
        }
        if(!works){
            cout << "-1\n";
            continue;
        }
        int st = conv(mask);
        // cout << st << nL;
        cout << dist[st] << nL;
    }
    
    return 0;
}
