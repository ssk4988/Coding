#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using ll = long long;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

// r1, c1, d1, r2, c2, d2
const int dims[] = {51, 50, 51, 50, 1};
const int dims1[] = {
    dims[1] * dims[2] * dims[3] * dims[4],
    dims[2] * dims[3] * dims[4], 
    dims[3] * dims[4],
    dims[4]
};
const int numstates = dims[0] * dims[1] * dims[2] * dims[3] + 100;
// bitset<numstates> seen; 
pii seen[numstates];
using a4 = array<int, 4>;
a4 extract(int s){
    a4 res;
    for(int i = 3; i >= 0; i--){
        res[i] = s % dims[i];
        s /= dims[i];
    }
    return res;
}
int conv(int a0, int a1, int a2, int a3){
    // int res = 0;
    // for(int i = 0; i < 6; i++){
    //     res += a[i];
    //     res *= dims[i + 1];
    // }
    return a0 * dims1[0] + a1 * dims1[1] + a2 * dims1[2] + a3 * dims1[3];
}

vi dr{1, 0, -1, 0};
vi dc{0, 1, 0, -1};

bool better(int a, int b){
    return b == -1 || a < b;
}

int main(){
    // cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int c, r, e; cin >> c >> r >> e;
    // dec all columns by 1
    e--;
    r++;
    vector<vvi> canTake(r, vvi(c, vi(4, 1)));
    rep(i, 0, c){
        canTake[1][i][2] = false;
        canTake[r - 1][i][0] = false;
        rep(j, 0, 4) canTake[0][i][j] = false;
    }
    canTake[1][e][2] = true;
    rep(i, 0, numstates){
        seen[i] = {INT_MAX, INT_MAX};
    }

    rep(i, 0, r){
        canTake[i][0][3] = false;
        canTake[i][c - 1][1] = false;
    }
    map<char, int> m;
    m['S'] = 2;
    m['N'] = 0;
    m['E'] = 1;
    m['W'] = 3;
    int c1, r1, c2, r2; char dd1, dd2; cin >> c1 >> r1 >> dd1 >> c2 >> r2 >> dd2;
    c1--; c2--;
    int n; cin >> n;
    rep(i, 0, n){
        int ci, ri; cin >> ci >> ri;
        ci--;
        canTake[ri][ci][0] = false;
        canTake[ri + 1][ci][2] = false;
    }
    cin >> n;
    rep(i, 0, n){
        int ci, ri; cin >> ci >> ri;
        ci--;
        canTake[ri][ci][1] = false;
        canTake[ri][ci + 1][3] = false;
    }
    vi visited(numstates);
    int d1 = m[dd1], d2 = m[dd2];
    using a3 = array<int, 3>;
    int dif = (4 + d2 - d1) % 4;
    using t3 = tuple<int, int, int>;
    priority_queue<t3, vector<t3>, greater<t3>> pq;
    pq.push({0, 0, conv(r1, c1, r2, c2)});
    seen[conv(r1, c1, r2, c2)] = {0, 0};
    rep(i, 0, r){
        rep(j, 0, c){
            rep(k, 0, 4){
                // if(canTake[i][j][k]){
                //     cout << i << " " << (j+1) << " can move to " << (i + dr[k]) << " " << (j + dc[k]+1) << "\n";
                // }
            }
        }
    }
    bool solved = false;
    pii ans = {INT_MAX, INT_MAX};

    while(!pq.empty()){
        auto [forward, bump, state] = pq.top(); pq.pop();
        if(visited[state]) continue;
        visited[state] = true;
        auto [r11, c11, r22, c22] = extract(state);
        r1 = r11, c1 = c11, r2 = r22, c2 = c22;
        if(r1 == 0 && c1 == e && r2 == 0 && c2 == e){
            ans = min(ans, {forward, bump});
            break;
        }
        rep(k, 0, 4){
            int sr1 = 0, sc1 = 0, sr2 = 0, sc2 = 0, sb = 0;
            if(canTake[r1][c1][k]){
                r1 += dr[k];
                c1 += dc[k];
                sr1 += dr[k];
                sc1 += dc[k];
            }
            else sb += !(r1 == 0 && c1 == e);


            if(canTake[r2][c2][(k+dif)%4]){
                r2 += dr[(k+dif)%4];
                c2 += dc[(k+dif)%4];
                sr2 += dr[(k+dif)%4];
                sc2 += dc[(k+dif)%4];
            }
            else sb += !(r2 == 0 && c2 == e);
            bump += sb;
            forward++;
            int newstate = conv(r1, c1, r2, c2);
            // cout << r1 << " "<< c1 << " " << r2 << " " << c2 << " " << newstate << " " << numstates << "\n";
            if(!visited[newstate] && pii{forward, bump} < seen[newstate]){
                bool p = true;
                if(r1 == r2 && c1 == c2){
                    if(r1 == 0 && c1 == e){
                        p = true;
                    }
                    else p = false;
                }
                if(p){
                    seen[newstate] = {forward, bump};
                    pq.emplace(forward, bump, newstate);
                }
            }
            // cout << "after check\n";
            bump -= sb;
            r1 -= sr1;
            c1 -= sc1;
            r2 -= sr2;
            c2 -= sc2;
            forward--;
        }
    }
    cout << ans.first << " " << ans.second << "\n";
    return 0;
}
