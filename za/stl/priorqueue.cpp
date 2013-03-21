#include <queue>
#include <string>
#include <iostream>
using namespace std;

//结构体
struct Node
{
	char szName[20];
	int  priority;
	Node(int nri, char *pszName)
	{
		strcpy(szName, pszName);
		priority = nri;
	}
};
//结构体的比较方法 改写operator()
struct NodeCmp
{
	bool operator()(const Node &na, const Node &nb)
	{
		if (na.priority != nb.priority)
			return na.priority <= nb.priority;
		else
			return strcmp(na.szName, nb.szName) > 0;
	}
};
void PrintfNode(const Node &na)
{
	printf("%s %d\n", na.szName, na.priority);
}
int main()
{
	//优先级队列默认是使用vector作容器，底层数据结构为堆。
	priority_queue<Node, vector<Node>, NodeCmp> a;

	//有5个人进入队列
	a.push(Node(5, "小谭"));
	a.push(Node(3, "小刘"));
	a.push(Node(1, "小涛"));
	a.push(Node(5, "小王"));

	//队头的2个人出队
	PrintfNode(a.top());
	a.pop();
	PrintfNode(a.top());
	a.pop();
	printf("--------------------\n");

	//再进入3个人
	a.push(Node(2, "小白"));
	a.push(Node(2, "小强"));
	a.push(Node(3, "小新"));

	//所有人都依次出队
	while (!a.empty())
	{
		PrintfNode(a.top());
		a.pop();
	}

	return 0;
}
