#include <iostream>
using namespace std;
 
// 输出当前堆的排序状况
void PrintArray(int data[], int size)
{
    for (int i=1; i<=size; ++i)
        cout <<data[i]<<"  ";
    cout<<endl;
}
 
// 堆化，保持堆的性质
// MaxHeapify让a[i]在最大堆中"下降"，
// 使以i为根的子树成为最大堆
void MaxHeapify(int *a, int i, int size)
{
	int lt = 2*i, rt = 2*i+1;
	int largest;
	if(lt <= size && a[lt] > a[i])
		largest = lt;
	else
		largest = i;
	if(rt <= size && a[rt] > a[largest])
		largest = rt;
	if(largest != i)
	{
		int temp = a[i];
		a[i] = a[largest];
		a[largest] = temp;
		MaxHeapify(a, largest, size);
	}
}
 
// 建堆
// 自底而上地调用MaxHeapify来将一个数组a[1..size]变成一个最大堆
//
void BuildMaxHeap(int *a, int size)
{
	for(int i=size/2; i>=1; --i)
		MaxHeapify(a, i, size);
}
 
// 堆排序
// 初始调用BuildMaxHeap将a[1..size]变成最大堆
// 因为数组最大元素在a[1]，则可以通过将a[1]与a[size]互换达到正确位置
// 现在新的根元素破坏了最大堆的性质，所以调用MaxHeapify调整，
// 使a[1..size-1]成为最大堆，a[1]又是a[1..size-1]中的最大元素，
// 将a[1]与a[size-1]互换达到正确位置。
// 反复调用Heapify，使整个数组成从小到大排序。
// 注意： 交换只是破坏了以a[1]为根的二叉树最大堆性质，它的左右子二叉树还是具备最大堆性质。
//        这也是为何在BuildMaxHeap时需要遍历size/2到1的结点才能构成最大堆，而这里只需要堆化a[1]即可。
void HeapSort(int *a, int size)
{
	BuildMaxHeap(a, size);
	PrintArray(a, size);
 
	int len = size;
	for(int i=size; i>=2; --i)
	{
		int temp = a[1];
		a[1] = a[i];
		a[i] = temp;
		len--;
		MaxHeapify(a, 1, len);
		cout << "中间过程:";
		PrintArray(a, size);
	}
 
}
 
int main()
{
	int size;
	int arr[100];
	cout << "Input the num of elements:\n";
	cin >> size;
	cout << "Input the elements:\n";
	for(int i=1; i<=size; ++i)
		cin >> arr[i];
	cout << endl;
    HeapSort(arr, size);
	cout << "最后结果:";
    PrintArray(arr, size);
}
