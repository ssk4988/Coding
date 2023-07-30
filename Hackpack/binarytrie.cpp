#include <bits/stdc++.h>
using namespace std;

struct Node
{
    Node *nex[2] = {};
    int bitnum;
    Node(int b) : bitnum(b) {}
    void add(int val)
    {
        if (bitnum == 0)
            return;
        int idx = 1 & (val >> (bitnum - 1));
        if (nex[idx] == NULL)
        {
            nex[idx] = new Node(bitnum - 1);
        }
        nex[idx]->add(val);
    }
    int closest(int val)
    {
        int ans = 0;
        if (bitnum == 0)
            return ans;
        int idx = 1 & (val >> (bitnum - 1));
        if (nex[idx] != NULL)
        {
            ans |= idx << (bitnum - 1);
            ans |= nex[idx]->closest(val);
        }
        else if (nex[1 - idx] != NULL)
        {
            ans |= (1 - idx) << (bitnum - 1);
            ans |= nex[1 - idx]->closest(val);
        }
        return ans;
    }
};