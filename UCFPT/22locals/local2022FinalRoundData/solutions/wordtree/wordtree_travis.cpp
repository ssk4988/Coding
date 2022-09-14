
#include <bits/stdc++.h>

#define ii second.first
#define jj second.second

using namespace std;

typedef pair<int, pair<int, int>> edge;

class DS {
    int * p;
    public:
        DS(int n) {
            p = new int[n];
            for (int i = 0; i < n; i++)
                p[i] = -1;
        }
        ~DS() {
            delete[] p;
        }
        int find(int x) {
            return (p[x] < 0) ? x : (p[x] = find(p[x]));
        }
        int merge(int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return 0;
            if (p[a] > p[b]) {
                a ^= b;
                b ^= a;
                a ^= b;
            }
            p[a] += p[b];
            p[b] = a;
            return 1;
        }

};

int dist(string a, string b) {
    int res = 0;
    for (int i = 0; i < a.size(); i++) {
        res += abs(a[i]-b[i]);
    }
    return res;
}

int main() {
    int n, k, index = 0;
    cin >> n >> k;
    vector<string> words(n);
    vector<edge> e_list((n*(n-1))/2);

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (int j = 0; j < i; j++) {
            e_list[index].first = dist(words[i], words[j]);
            e_list[index].ii = i;
            e_list[index].jj = j;
            index++;
        }
    }

    sort(e_list.begin(), e_list.end());

    DS ds(n);

    int ans = 0;
    for (auto e : e_list) {
        int i = e.ii, j = e.jj, tans = e.first;
        if (ds.merge(i,j))
            ans = tans;
    }

    cout << ans << endl;

    return 0;
}
