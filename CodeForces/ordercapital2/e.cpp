#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

/*
commuting?
identity commutes with anything
commutes with self
commutes with inverse

let x = a[b[i]] = b[a[i]]
then inv_b[x] = a[i], inv_a[x] = b[i]

2 3 1


2 - x
3 x -
2 3 1
3 1 2

2 - 4 -
3 4 - -

2 1 4 3
-
3 4 2 1
3 4 1 2
// 4 3 1 2

2 3 4 1
3 4 1 2

map a cycle to another cycle of the same size. also any cycle can be rotated

impossibilities:
indexes which are in same cycle in a have b[i] point to different cycles
cycle pointed to is different size

alg:
find which cycles are being mapped first
now for any unmapped cycle, find unused cycle of same size which has smallest index. now map first of it to other

*/

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) cin >> a[i], a[i]--;
        vi b(n);
        rep(i, 0, n) {
            cin >> b[i];
            if(b[i] != -1) b[i]--;
        }
        vi id(n, -1), cycsize(n, -1);
        vector<set<int>> used(n+1);
        rep(i, 0, n) {
            if(id[i] != -1) continue;
            id[i] = i;
            int u = a[i];
            int s = 1;
            while(u != i) {
                id[u] = i;
                u = a[u];
                s++;
            }
            cycsize[u] = s;
            used[s].insert(u);
        }
        vi mapto(n, -1);
        bool works = true;
        rep(i, 0, n) {
            if(b[i] == -1) continue;
            int c = id[i];
            if(mapto[c] != -1) continue;
            mapto[c] = id[b[i]];
            if(cycsize[mapto[c]] != cycsize[c] || !used[cycsize[c]].count(mapto[c])) {
                works = false;
                break;
            }
            used[cycsize[c]].erase(mapto[c]);
            int u = i;
            int image = b[u];
            do {
                if(b[u] != -1 && b[u] != image) {
                    works = false;
                    break;
                }
                b[u] = image;
                u = a[u];
                image = a[image];
            } while(u != i);
            if(!works) break;
        }
        rep(i, 0, n) {
            if(id[i] != i) continue;
            if(mapto[i] != -1) continue;
            mapto[i] = *begin(used[cycsize[i]]);
            used[cycsize[i]].erase(mapto[i]);
            b[i] = mapto[i];
            int u = i;
            int image = b[u];
            do {
                if(b[u] != -1 && b[u] != image) {
                    works = false;
                    break;
                }
                b[u] = image;
                u = a[u];
                image = a[image];
            } while(u != i);
            if(!works) break;
        }
        if(works) {
            cout << "YES\n";
            rep(i, 0, n) {
                assert(b[i] != -1);
                cout << b[i]+1 << " ";
            }
            cout << "\n";
        } else cout << "NO\n";
    }
    
    return 0;
}
