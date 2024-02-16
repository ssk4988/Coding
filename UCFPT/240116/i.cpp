#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int conv(char c){
    if('a' <= c && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

char rconv(int c){
    if(c < 26) return 'a' + c;
    return 'A' + c - 26;
}

#define f first
#define s second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n = cn + 1; 
        cin >> n;

        map<int, int> freq, sfreq, freqb, sfreqb;
        // map<int, vi> freq2, sfreq2;
        map<pii, vi> freq3, sfreq3;
        map<pii, int> flb;
        int n2 = n * n;
        vi dist(n2);
        rep(i, 0, n){
            freq[i] = 0;
            sfreq[i] = 0;
            freqb[i] = 0;
            sfreqb[i] = 0;
        }
        rep(i, 0, n){
            rep(j, 0, n){
                if(i * j / n > 0) freq[i * j / n]++;
                freqb[i * j % n]++;
                dist[i * j]++;
            }
        }
        // cout << "=========" << n << "=========\n";
        // if(n - sz(freq) > 1){
        //     cout << (n - sz(freq)) << "\n";
        // }
        rep(i, 0, n){
            freq3[{freq[i], freqb[i]}].push_back(i);
        }
        // for(auto [key, val] : freq){
        //     // cout << key << "x: " << val << "\n";
        //     freq2[val].push_back(key);
        // }
        // for(auto [key, val] : freq2){
        //     if(sz(val) > 1) {
        //         cout << n << " " << key << " ";
        //         for(int i : val) cout << i << " ";
        //         cout << "\n";
        //     }
        // }
        int seen = 0;
        vector<vi> poss(sz(freq3)), sposs(sz(freq3));
        for(auto [key, val] : freq3){
            flb[key] = seen++;
            poss[flb[key]] = val;
            // cout << (seen - 1) << " maps to " << key.f << " " << key.s << "\n";
            // if(sz(val) > 1) {
            //     cout << n << " pair: <" << key.f << " " << key.s << "> ";
            //     for(int i : val) cout << i << " ";
            //     cout << "\n";
            // }
        }
        // continue;
        vi used(n);
        vi rl(n, -1);
        vector<pii> strs(n2, {-1, -1});
        rep(i, 0, n2){
            string str; cin >> str;
            if(sz(str) == 1) strs[i].second = conv(str[0]);
            else strs[i] = {conv(str[0]), conv(str[1])};
            if(strs[i].f != -1) {
                sfreq[strs[i].f]++;
            }
            sfreqb[strs[i].s]++;
        }
        rep(i, 0, n){
            sfreq3[{sfreq[i], sfreqb[i]}].push_back(i);
        }
        assert(sz(sfreq3) == sz(freq3));
        for(auto [key, val] : sfreq3){
            sposs[flb[key]] = val;
        }
        auto bt = [&](int grp, int idx, auto &&bt) -> bool {
            if(grp == sz(poss)){
                vi dist2(n2);
                for(auto [i, j] : strs){
                    int val = (i == -1 ? 0 : rl[i]) * n + rl[j];
                    dist2[val]++;
                }
                return dist == dist2;
            }
            int nextidx = (idx + 1) % sz(poss[grp]), nextgrp = grp + (nextidx == 0);
            for(int re : poss[grp]){
                if(used[re]) continue;
                used[re] = true;
                rl[sposs[grp][idx]] = re;
                if(bt(nextgrp, nextidx, bt)) return true;
                rl[sposs[grp][idx]] = re;
                used[re] = false;
            }
            return false;
        };
        bool works = bt(0, 0, bt);
        // cout << "it works? " << works << "\n";
        assert(works);
        // rep(i, 0, sz(poss)){
        //     cout << i << " poss: ";
        //     for(int j : poss[i]) cout << j << " ";
        //     cout << "sposs: ";
        //     for(int j : sposs[i]) cout << j << " ";
        //     cout << "\n";
        // }
        if(works){
            vi rev(n);
            rep(i, 0, n) rev[rl[i]] = i;
            rep(i, 0, n){
                cout << rconv(rev[i]);
            }    
            cout << "\n";
        }
    }
    // rep(b, 1, 53){
    // }

    return 0;
}