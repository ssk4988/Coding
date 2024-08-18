#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

const int N = 10005;
const int MAXN = 10000;
const int S = N * N * 4;
using bs = bitset<S>;

#define f first
#define s second

vii ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

inline int idx(int r, int c, int dir){
    return r * N * 4 + c * 4 + dir;
}

inline bool inbounds(int r, int c){
    return r >= 0 && r <= MAXN && c >= 0 && c <= MAXN;
}

using a3 = array<int, 3>;
bs block, halt, vis;

pii operator-(pii a, pii b){
    pii c = {a.f - b.f, a.s - b.s};
    if(c.f != 0) c.f /= abs(c.f);
    if(c.s != 0) c.s /= abs(c.s);
    return c;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    pii start, finish;
    cin >> start.s >> start.f;
    cin >> finish.s >> finish.f;

    int numobst; cin >> numobst;
    rep(i, 0, numobst){
        int n; cin >> n;
        vii pts(n);
        rep(j, 0, n){
            cin >> pts[j].s >> pts[j].f;
        }
        rep(j, 0, n){
            // int dr = pts[(j+1)%n].f - pts[j].f, dc = pts[(j+1)%n].s - pts[j].s;
            auto [dr, dc] = pts[(j+1)%n] - pts[j];
            int r = pts[j].f + dr, c = pts[j].s + dc;
            auto dirit = find(all(ds), pii{dr, dc});
            assert(dirit != ds.end());
            int blockdir = ((dirit - ds.begin()) + 1) % 4;
            while(pii{r, c} != pts[(j+1)%n]){
                halt[idx(r, c, blockdir)] = block[idx(r, c, blockdir)] = true;
                r += dr;
                c += dc;
            }
        }
        rep(j, 0, n){
            auto [r, c] = pts[j];
            pii nexside = pts[(j+1)%n] - pts[j];
            pii preside = pts[j] - pts[(j-1+n)%n];
            auto nexit = find(all(ds), nexside);
            auto preit = find(all(ds), preside);
            assert(nexit != ds.end());
            assert(preit != ds.end());
            int nexidx = nexit - ds.begin();
            int preidx = preit - ds.begin();
            // cout << "at " << pts
            if((preidx-1+4)%4 == nexidx){
                halt[idx(r, c, preidx)] = block[idx(r, c, preidx)] = true;
                halt[idx(r, c, (nexidx + 2) % 4)] = block[idx(r, c, (nexidx + 2) % 4)] = true;
                // cout << "halt/block " << r << " " << c << " " << nexidx << " " << (preidx+2)%4 << "\n";
            }
            else if((preidx+1)%4 == nexidx){
                halt[idx(r, c, nexidx)] = true;
                halt[idx(r, c, (preidx+2)%4)] = true;
                // cout << "halt " << r << " " << c << " " << nexidx << " " << (preidx+2)%4 << "\n";
            }
        }
    }
    deque<pair<a3, int>> dq;
    rep(i, 0, sz(ds)){
        auto [dr, dc] = ds[i];
        int r = start.f, c = start.s;
        if(block[idx(r, c, i)]) continue;
        vis[idx(r, c, i)] = true;
        r += dr;
        c += dc;
        if(!inbounds(r, c)) continue;
        vis[idx(r, c, i)] = false;
        dq.push_back({a3{r, c, i}, 1});
    }
    int ans = -1;
    while(!dq.empty()){
        auto [df, dist] = dq.front();
        auto [r, c, dir] = df;
        dq.pop_front();
        if(vis[idx(r, c, dir)]) continue;
        vis[idx(r, c, dir)] = true;
        if(r <= 60 && c <= 60){
            // cout << r << "," << c << "," << dir << " " << dist << "\n";
        }
        if(pii{r, c} == finish){
            ans = dist;
            break;
        }
        if(!halt[idx(r, c, dir)]){
            auto [dr, dc] = ds[dir];
            r += dr, c += dc;
            if(inbounds(r, c)){
                dq.push_front({a3{r, c, dir}, dist});
            }
        }
        else{
            // cout << r << "," << c << "," << dir << "halted\n";
            rep(i, 0, sz(ds)){
                if(block[idx(r, c, i)]) continue;
                // cout << "notblock " << i << "\n";
                auto [dr, dc] = ds[i];
                // r += dr, c += dc;
                if(!inbounds(r+dr, c+dc)) continue;
                dq.push_back({a3{r+dr, c+dc, i}, dist+1});
            }
        }
    }
    if(ans == -1){
        cout << "NIE\n";
    }
    else{
        cout << ans << "\n";
    }


    return 0;
}

