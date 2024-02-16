#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;

#define pb push_back
#define f first
#define s second

vl dmr = {2, -2, -2, 2};
vl dmc = {-2, -2, 2, 2};
vl dr = {-1, 0, 1, 0};
vl dc = {0, 1, 0, -1};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll r, c; cin >> r >> c;
    ll sr, sc; cin >> sr >> sc; sr--, sc--;
    ll ns; cin >> ns;
    ll fr = sr, fc = sc;
    vvl curr(4), curc(4), curs(4);
    // test < 4 moves
    vector<vvl> cands(r, vvl(c));
    int lasti = (ns % 4 - 1 + 4) % 4;
    ll finalr, finalc;
    rep(i, 0, 4){
        ll nt = (i < (ns % 4)) + ns / 4;
        // cout << i << " " << nt << "\n";
        if(nt == 0) continue;
        if(i == lasti){
            finalr = (fr + (dmr[i] % r) * ((nt-1) % r)) % r;
            finalc = (fc + (dmc[i] % c) * ((nt - 1) % c)) % c;
            finalr = ((finalr + dr[i] * ns) % r + r) % r;
            finalc = ((finalc + dc[i] * ns) % c + c) % c;
        }
        ll cr = fr, cc = fc;
        do {
            curr[i].pb(cr), curc[i].pb(cc), curs[i].pb(sz(curs[i]) == 0 ? i + 1 : (4 + curs[i].back()));
            cr = (cr + dmr[i] + r) % r, cc = (cc + dmc[i] + c) % c; 
        } while(cr != fr && cc != fc);
        ll cyclelen = sz(curr[i]);
        vvl t(r, vl(c, -1));
        vector<vvl> rem(r, vvl(c));
        for(ll j = (nt % cyclelen + cyclelen - 1) % cyclelen, cnt = 0; cnt < min(nt, cyclelen); cnt++, j = (j - 1 + cyclelen) % cyclelen){
            // t[curr[i][j]][curc[i][j]] = j;
            t[curr[i][j]][curc[i][j]] = curs[i][j] + (nt - 1 - j) / cyclelen * 4 * cyclelen;

            // cout << curr[i][j] << " " << curc[i][j] << " " << curs[i][j] << "\n";
        }
        if(i%2 == 0){
            for(int c1 = 0; c1 < c; c1++){
                set<ll> ss;
                for(int r1 = 0, cnt = 0; cnt < r; r1 = (r1 + dr[i] + r) % r, cnt++){
                    for(ll v : rem[r1][c1]){
                        ss.erase(v);
                    }
                    if(t[r1][c1] == -1) continue;
                    // ll stp = curs[i][t[r1][c1]];
                    ll stp = t[r1][c1];
                    if(stp < r)
                        rem[(((r1 + dr[i] * stp) % r + r) % r)][c1].pb(stp);
                    ss.insert(stp);
                }
                for(int r1 = 0, cnt = 0; cnt < r; r1 = (r1 + dr[i] + r) % r, cnt++){
                    for(ll v : rem[r1][c1]){
                        ss.erase(v);
                    }
                    // ll stp = curs[i][t[r1][c1]];
                    ll stp = t[r1][c1];
                    if(t[r1][c1] != -1) 
                        ss.insert(stp);
                    if(sz(ss)){
                        cands[r1][c1].pb(*ss.rbegin());
                    }
                }
            }
        }
        else{
            for(int r1 = 0; r1 < r; r1++){
                set<ll> ss;
                for(int c1 = 0, cnt = 0; cnt < c; c1 = (c1 + dc[i] + c) % c, cnt++){
                    for(ll v : rem[r1][c1]){
                        ss.erase(v);
                    }
                    if(t[r1][c1] == -1) continue;
                    // ll stp = curs[i][t[r1][c1]];
                    ll stp = t[r1][c1];
                    if(stp < c)
                        rem[r1][(((c1 + dc[i] * stp) % c + c) % c)].pb(stp);
                    ss.insert(stp);
                }
                for(int c1 = 0, cnt = 0; cnt < c; c1 = (c1 + dc[i] + c) % c, cnt++){
                    for(ll v : rem[r1][c1]){
                        ss.erase(v);
                    }
                    if(t[r1][c1] != -1) 
                        ss.insert(t[r1][c1]);
                    if(sz(ss)){
                        cands[r1][c1].pb(*ss.rbegin());
                    }
                }
            }
        }
        fr += (i + 1) * dr[i], fc += (i + 1) * dc[i];
        fr %= r, fc %= c;
        fr += r, fc += c;
        fr %= r, fc %= c;
    }
    rep(i, 0, r){
        rep(j, 0, c){
            sort(all(cands[i][j]));
            char v = '.';
            if(sz(cands[i][j])){
                ll t = (cands[i][j].back() - 1 + 26) % 26;
                v = 'A' + t;
            }
            if(i == finalr && j == finalc) v = '@';
            cout << v;
        }
        cout << "\n";
    }
    // rep(i, 0, r){
    //     rep(j, 0, c){
    //         for(ll v : cands[i][j]){
    //             cout << i << " " << j << " " << v << "\n";
    //         }
    //     }
    // }
    return 0;
}
/*
5 5 3 3 7
0 2
4 0 5
2 2 1
1 2
4 0 6
1 2 2
2 2
4 1 7
1 4 3
3 1
4 4 4
EEEEE
E@BBE
EEEEE
EEEEE
EDDDD
*/