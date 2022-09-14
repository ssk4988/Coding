
#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

class Node {
    public:
        Node * next;
        lli value;
        Node(lli v) {
            value = v;
            next = NULL;
        }
        ~Node() {
            if (next != NULL)
                delete next;
        }
};

class LinkedList {
    public:
        Node * head, * tail;
        LinkedList() {
            head = NULL;
            tail = NULL;
        }
        ~LinkedList() {
        }
        void add(lli value) {
            if (head == NULL) {
                head = tail = new Node(value);
            } else {
                tail->next = new Node(value);
                tail = tail->next;
            }
        }
        void join(LinkedList & o) {
            if (o.head == NULL) return;
            tail->next = o.head;
            tail = o.tail;
            o.head = NULL;
            o.tail = NULL;
        }
};

class DS {
    private:
        int * p;
    public:
        LinkedList * weights; // Euler tour info (edge weight)
        LinkedList * indices; // Euler tour info (index)
        DS(int n) {
            p = new int[n];
            weights = new LinkedList[n];
            indices = new LinkedList[n];
            for (int i = 0; i < n; i++) {
                p[i] = -1;
                indices[i].add(i);
            }

        }
        ~DS() {
            int root = find(0);
            delete weights[root].head;
            delete indices[root].head;
            delete[] weights;
            delete[] indices;
            delete[] p;
        }
        int find(int x) {
            return (p[x] < 0) ? x : (p[x] = find(p[x]));
        }
        void merge(int a, int b, lli amt) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (p[a] > p[b]) {
                a^=b;
                b^=a;
                a^=b;
            }
            p[a] += p[b];
            p[b] = a;
            weights[a].add(amt);
            weights[a].join(weights[b]);
            indices[a].join(indices[b]);
        }
};

typedef pair<int, int> pii;
typedef pair<lli, lli> pll;
typedef pair<lli, pii> Edge;

#define ii second.first
#define jj second.second

int main() {
    int n, q, index = 0;
    cin >> n;
    vector<Edge> es((n*(n-1))/2);
    vector<pll> pts(n);
    
    for (int i = 0; i < n; i++) {
        cin >> pts[i].first >> pts[i].second;
        for (int j = 0; j < i; j++) {
            lli dx = pts[i].first  - pts[j].first;
            lli dy = pts[i].second - pts[j].second;
            es[index].first = dx*dx+dy*dy;
            es[index].ii = i;
            es[index].jj = j;
            index++;
        }
    }

    sort(es.begin(), es.end());

    DS ds(n);
    for (auto e : es)
        ds.merge(e.ii, e.jj, e.first);
    
    vector<int> inds(n);
    vector<lli> weis(n-1);

    int root = ds.find(0);
    Node * curW = ds.weights[root].head;
    for (int i = 0; i < n - 1; i++) {
        weis[i] = curW->value;
        curW = curW->next;
    }
    assert(curW == NULL);

    Node * curI = ds.indices[root].head;
    for (int i = 0; i < n; i++) {
        inds[(int)curI->value] = i;
        curI = curI->next;
    }
    assert(curI == NULL);

    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        a = inds[a-1];
        b = inds[b-1];
        if (a > b) {
            a^=b;
            b^=a;
            a^=b;
        }
        lli ans = 0;
        for (int i = a; i < b; i++) {
           if (ans < weis[i])
               ans = weis[i];
        }
        cout << setprecision(20) << sqrt(ans) << endl;
    }

    return 0;
}
