#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int kMax1 = 1000010;
const int kMax2 = 10010;
char g_pattern[kMax2];
char g_s[kMax1];
int g_next[kMax2];

void GetNext(int n)
{
    memset(g_next, -1, sizeof(g_next));
    g_next[0] = -1;
    g_next[1] = 0;
    int k = 0;
    int i = 1;
    while(i<(n-1))
    {
        //printf("i=%d, k=%d\n", i, k);
        if(k == -1 || g_pattern[k] == g_pattern[i])
        {
            ++i; ++k;
            g_next[i] = k;
        }
        else
            k = g_next[k];
    }
}

int KMP(int n)
{
    int ans = -1;
    int i = 0;
    int j = 0;
    int pattern_len = strlen(g_pattern);
    while(i < n)
    {
        if(j == -1 || g_s[i] == g_pattern[j])
        {
            ++i; ++j;
        }
        else
            j = g_next[j];
        if(j == pattern_len)
        {
            ans = i - pattern_len;
        }
    }
    return ans;
}
