#include "iostream"
#include "vector"
#include "queue"

using namespace std;
int c[100];
struct cmp1
{
     bool operator ()(int x, int y)
    {
        return x > y;//С�����ȼ���
    }
};

struct cmp2
{
    bool operator ()(const int x, const int y)
    {
        return c[x] > c[y]; 
       // c[x]С�����ȼ��ߣ����ڿ����ڶ���ı���ڵ�ֵ��
        //����ʹ�ô˷����ﲻ�����������ȡ������ýṹ�����͡�
    }
};

struct node
{
    int x, y;
    friend bool operator < (node a, node b)
    {
        return a.x > b.x;//�ṹ���У�xС�����ȼ���
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
