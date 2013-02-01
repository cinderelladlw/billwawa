#include "iostream"
#include "vector"
#include "queue"

using namespace std;
int c[100];
struct cmp1
{
     bool operator ()(int x, int y)
    {
        return x > y;//小的优先级高
    }
};

struct cmp2
{
    bool operator ()(const int x, const int y)
    {
        return c[x] > c[y]; 
       // c[x]小的优先级高，由于可以在对外改变队内的值，
        //所以使用此方法达不到真正的优先。建议用结构体类型。
    }
};

struct node
{
    int x, y;
    friend bool operator < (node a, node b)
    {
        return a.x > b.x;//结构体中，x小的优先级高
    }
};

priority_queue<int>q1;
priority_queue<int, vector<int>, cmp1>q2;
priority_queue<int, vector<int>, cmp2>q3;
priority_queue<node>q4;

queue<int>qq1;
queue<node>qq2;

int main()
{
    int i, j, k, m, n;
    int x, y;
    node a;
    while (cin >> n)
    {
        for (i = 0; i < n; i++)
        {
            cin >> a.y >> a.x;
            q4.push(a);
        }
        cout << endl;
        while (!q4.empty())
        {
            cout << q4.top().y << " " << q4.top().x << endl;
            q4.pop();
        }
    //    cout << endl;
    }
    return 0;
}
