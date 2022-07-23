#include <bits/stdc++.h>
using namespace std;

int main(void) 
{
  ios::sync_with_stdio(0); cin.tie(0);

  int NUM_CASES; cin >> NUM_CASES;
  for(int T = 1;T <= NUM_CASES;T++) 
  {
    char c; cin >> c;
    bool server = c - 'A';
    int s; cin >> s;

    //             A  B
    int score[] = {0, 0};

    for (int i = 0; i < s; i++)
    {
      int k; cin >> k;

      if (k % 2)
        // server scores, server stays
        score[server]++;
      else
        // server does not score, server switches
        server = !server;
    }

    cout << score[0] << "-" << score[1] << endl;
  }

  return 0;
}