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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    int MOD;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k >> MOD;
        vector<vl> heap(n+1, vl(k+1)), tree(n+1, vl(k+1));
        heap[0] = vl(k+1, 1);
        tree[0] = vl(k+1, 1);
        rep(i, 1, n+1){
            vl heapconv(k+1), treeconv(k+1);
            rep(j, 0, k+1){
                rep(l, 0, k+1){
                    if(j + l > k) break;
                    if(j > l) heapconv[j + l] += heap[i-1][j] * tree[i-1][l];
                    heapconv[j+l] %= MOD;
                    treeconv[j + l] += tree[i-1][j] * tree[i-1][l];
                    treeconv[j + l] %= MOD;
                }
            }
            rep(j, 0, k+1){
                rep(p, 0, j+1) {
                    heap[i][j] += 2 * heapconv[j - p];
                    heap[i][j] %= MOD;
                    tree[i][j] += treeconv[j - p];
                    tree[i][j] %= MOD;
                }
            }
        }
        cout << heap[n-1][k] << "\n";
    }
    
    return 0;
}
