#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vi days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vi pref(days);
    rep(i, 1, sz(pref)) pref[i] += pref[i - 1];
    int n; cin >> n;
    vi used(365);
    auto tonum = [&](string dte) -> int {
        int month = stoi(dte.substr(0, 2));
        int day = stoi(dte.substr(3, 2))-1;
        month -= 2;
        if(month >= 0) day += pref[month];
        return day;
    };
    auto encode = [&](int num) -> string {
        if(num < 10){
            string res = "0" + to_string(num);
            return res;
        }
        return to_string(num);
    };
    auto todate = [&](int day) -> string {
        string res;
        rep(i, 0, sz(pref)){
            if(day < days[i]){
                res = encode(i + 1) + "-" + encode(day+1);
                break;
            }
            day -= days[i];
        }
        return res;
    };
    rep(i, 0, n){
        string str, dte; cin >> str >> dte;
        int day = tonum(dte);
        used[day] = true;
    }
    int last = -1;
    rep(i, 0, sz(used)){
        if(used[i]) last = i;
    }
    last = last - 365;
    int ref = tonum("10-27");
    auto fromday = [&](int day) -> int {
        if(day > ref) return day - ref;
        return 365 + day - ref;
    };
    pair<int, int> best = {-1, 0};
    rep(i, 0, sz(used)){
        if(used[i]){
            last = i;
            continue;
        }
        int dur = i - last;
        int f = fromday(i);
        if(dur > best.first || (dur == best.first && f < fromday(best.second))){
            best = {dur, i};
        }
    }
    // cout << fromday(tonum("10-27")) << "\n";
    // cout << fromday(tonum("10-26")) << "\n";
    // cout << fromday(tonum("10-28")) << "\n";
    // cout << best.second << "\n";
    cout << todate(best.second) << "\n";

    return 0;
}