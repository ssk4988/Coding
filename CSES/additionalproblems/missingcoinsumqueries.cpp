#include <bits/stdc++.h>
using namespace std; 
 
#define ll long long
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define arr array<int, 30>
 
const int mx = 2e5 + 5;
 
// STOLEN TO NOT TLE

int n, q, A[mx]; ll sm[mx][30]; arr seg[mx * 2];
 
arr comb(arr &A, arr &B){
	arr ret;
    FOR(i, 0, 30) ret[i] = min(A[i], B[i]);
    return ret;
}
arr qry(int l, int r){
    arr ret; fill(ret.begin(), ret.end(), 2e9);
    for (l += mx, r += mx; l <= r; r /= 2, l /= 2){
        if (l % 2 == 1) ret = comb(ret, seg[l++]);
        if (r % 2 == 0) ret = comb(seg[r--], ret);
    }
    return ret;
}
 
int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q; memset(seg, 0x3f, sizeof(seg));
    FOR(i, 1, n + 1){
        int x; cin >> x;
        int g = log2(x);
        seg[i + mx][g] = x; sm[i][g] = x;
    }
    FOR(i, 1, n + 1) FOR(j, 0, 30) sm[i][j] += sm[i - 1][j];
    
    for (int i = mx - 1; i; i--) seg[i] = comb(seg[i * 2], seg[i * 2 + 1]);
    
    while (q--){
        int l, r; cin >> l >> r;
 
        arr bst = qry(l, r); ll tot = 0, ans = -1;
        FOR(i, 0, 30){
            if (tot + 1 < (1 << (i + 1)) and bst[i] > tot + 1){ 
                ans = tot + 1;
                break;
            }
            tot += sm[r][i] - sm[l - 1][i];
        }
        cout<<(ans == -1 ? tot + 1 : ans)<<"\n";
    }
}
